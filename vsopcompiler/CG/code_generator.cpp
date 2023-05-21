#include "code_generator.hpp"
#include <vector>

void CodeGeneratorVisitor::visit(BaseNode &expr) {}

void CodeGeneratorVisitor::visit(ProgramNode &expr) {}

void CodeGeneratorVisitor::visit(ClassNode &expr) {
    std::string className = expr.getName();
    StructType *classType = StructType::create(m_context.get(), className);

    if(m_pass_count == 0) {
        // Create the class type
        FunctionType *funcType = FunctionType::get(classType->getPointerTo(), {}, false);
        // Create LLVM function
        Function *new_function = Function::Create(funcType, GlobalValue::ExternalLinkage, currentClass.getName() + "__new", m_module.get());
    }

    expr.getBody()->accept(*this);
}

void CodeGeneratorVisitor::visit(ClassBodyNode &expr) {
    for (auto &child : expr.getMethods()) {
        child->accept(*this);
    }

    for (auto &child : expr.getFields()) {
        child->accept(*this);
    }
    
}

void CodeGeneratorVisitor::visit(FieldNode &expr) {}

void CodeGeneratorVisitor::visit(MethodNode &expr) {
    m_scopeInfo->setCurrentMethod(expr.getName());
    // Create LLVM function type
    std::vector<Type *> paramTypes;
    for (const auto &formal : expr.getFormals()) {
        std::string formalType = formal->getType();
        Type *llvmFormalType = getLLVMType(formalType);
        paramTypes.push_back(llvmFormalType);
    }

    Type *llvmReturnType = getLLVMType(expr.getRetType());
    StructType *classType = nullptr;
    if(llvmReturnType == nullptr)
        classType = m_module->getTypeByName(expr.getRetType());

    if(classType == nullptr && llvmReturnType == nullptr)
        throw std::runtime_error("Unknown return type");

    FunctionType *funcType = (llvmReturnType == nullptr) ? FunctionType::get(classType->getPointerTo(), paramTypes, false) : FunctionType::get(llvmReturnType, paramTypes, false);

    // Create LLVM function
    Function *function = Function::Create(funcType, Function::ExternalLinkage, expr.getName(), m_module.get());

    // Create entry block
    BasicBlock *entryBlock = BasicBlock::Create(m_context.get(), "entry", function);
    m_builder.SetInsertPoint(entryBlock);

    // Set up function arguments
    auto formalArg = function->arg_begin();
    for (const auto &formal : expr.getFormals()) {
        std::string formalName = formal->getName();
        formalArg->setName(formalName);
        formalArg++;
    }

    // Visit the block node
    expr.getBlock()->accept(*this);
}

void CodeGeneratorVisitor::visit(FormalNode &expr) {
    // Do nothing here, because formal nodes are handled in the method node
}


// Expressions
void CodeGeneratorVisitor::visit(IfNode &expr) {
    // Translate the condition expression
    expr.get_condExpr()->accept(*this)
    llvm::Value* condValue = m_returnValue;

    // Create basic blocks for the then and else branches
    llvm::Function* function = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(m_context, "then", function);
    llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(m_context, "else");
    llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(m_context, "ifcont");

    // Branch based on the condition
    builder.CreateCondBr(condValue, thenBlock, elseBlock);

    // Set "then" branch
    builder.SetInsertPoint(thenBlock);
    expr.get_thenExpr()->accept(*this);
    llvm::Value* thenValue = m_returnValue;
    builder.CreateBr(mergeBlock);

    // Set "else" branch
    function->getBasicBlockList().push_back(elseBlock);
    builder.SetInsertPoint(elseBlock);
    llvm::Value* elseValue = nullptr;
    if (expr.get_elseExpr()) {
        expr.get_elseExpr()->accept(*this);
        elseValue = m_returnValue;
    }
    builder.CreateBr(mergeBlock);

    // Set merge block
    function->getBasicBlockList().push_back(mergeBlock);
    builder.SetInsertPoint(mergeBlock);
    llvm::PHINode* phiNode = builder.CreatePHI(getLLVMType(expr.get_ret_type()), 2);
    phiNode->addIncoming(thenValue, thenBlock);
    if (elseValue) {
        phiNode->addIncoming(elseValue, elseBlock);
    }

    // Return the resulting value
    m_returnValue = phiNode;
}

void CodeGeneratorVisitor::visit(WhileNode &expr) {
    // Create basic blocks for the loop
    llvm::Function* function = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock* loopCondBlock = llvm::BasicBlock::Create(m_context, "loopcond", function);
    llvm::BasicBlock* loopBodyBlock = llvm::BasicBlock::Create(m_context, "loopbody");
    llvm::BasicBlock* loopExitBlock = llvm::BasicBlock::Create(m_context, "loopexit");

    // Jump to the loop condition block
    builder.CreateBr(loopCondBlock);

    // Set loop condition block
    builder.SetInsertPoint(loopCondBlock);

    // Evaluate the loop condition expression
    expr.get_condExpr()->accept(*this);
    llvm::Value* condValue = m_returnValue;

    // Branch based on the condition
    builder.CreateCondBr(condValue, loopBodyBlock, loopExitBlock);

    // Set the "loop body" block
    function->getBasicBlockList().push_back(loopBodyBlock);
    builder.SetInsertPoint(loopBodyBlock);
    expr.get_bodyExpr()->accept(*this);

    // Branch back to the loop condition block
    builder.CreateBr(loopCondBlock);

    // Set the "loop exit" block
    function->getBasicBlockList().push_back(loopExitBlock);
    builder.SetInsertPoint(loopExitBlock);

    m_returnValue = nullptr;
}

void CodeGeneratorVisitor::visit(LetNode &expr) {
    std::string name = expr.get_name();
    std::string type = expr.get_type();
    std::shared_ptr<ExprNode> initExpr = expr.get_initExpr();

    // Evaluate the initialization expression
    llvm::Value* initValue = nullptr;
    if (initExpr) {
        initExpr->accept(*this);
        initValue = m_returnValue;
    }

    // Store the initialized value
    llvm::AllocaInst* allocaInst = builder.CreateAlloca(getLLVMType(type), nullptr, name);
    if (initValue) {
        builder.CreateStore(initValue, allocaInst);
    }

    // Save the alloca instruction as a variable in the symbol table
    symbolTable[name] = allocaInst;
    // Visit the scoped expression
    expr.get_scopedExpr()->accept(*this);
}

void CodeGeneratorVisitor::visit(AssignNode &expr) {}

void CodeGeneratorVisitor::visit(UnOpNode &expr) {}

void CodeGeneratorVisitor::visit(NotUnOpNode &exp) {}

void CodeGeneratorVisitor::visit(MinusUnOpNode &expr) {}

void CodeGeneratorVisitor::visit(IsnullUnOpNode &expr) {}

void CodeGeneratorVisitor::visit(BinOpNode &expr) {}

void CodeGeneratorVisitor::visit(AddBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(MinusBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(MulBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(DivBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(LowerBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(LowerOrEqualBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(EqualBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(AndBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(PowBinOpNode &expr) {}

void CodeGeneratorVisitor::visit(SelfNode &expr) {}

void CodeGeneratorVisitor::visit(IdentifierNode &expr) {}

void CodeGeneratorVisitor::visit(UnitNode &expr) {}

void CodeGeneratorVisitor::visit(CallNode &expr) {}

void CodeGeneratorVisitor::visit(BlockNode &expr) {}

void CodeGeneratorVisitor::visit(LiteralNode &expr) {}

void CodeGeneratorVisitor::visit(NewNode &expr) {}


static *Type CodeGeneratorVisitor::getLLVMType(const std::string &type) const {
    if (vsopType == "int32") {
        return Type::getInt32Ty(m_context.get());
    } else if (vsopType == "bool") {
        return Type::getInt1Ty(m_context.get());
    } else if (vsopType == "string") {
        return Type::getInt8PtrTy(m_context.get());
    } else if (vsopType == "unit") {
        return Type::getVoidTy(m_context.get());
    }
    // TODO : Handle class types
    // Return a default type (e.g., void) if the VSOP type is not recognized
    return nullptr;
}