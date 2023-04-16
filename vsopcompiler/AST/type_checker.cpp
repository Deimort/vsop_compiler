#include "type_checker.hpp"
#include <algorithm>
#include <iostream>

void TypeCheckerVisitor::visit(IfNode& expr) {
    // Check condition is of bool type
    auto condExpr = expr.get_condExpr();
    condExpr->accept(*this);
    if (condExpr->get_ret_type() != "bool") {
        throw std::runtime_error("Condition expression of if statement must be of boolean type.");
    }

    // Check branch expressions
    auto thenExpr = expr.get_thenExpr();
    auto elseExpr = expr.get_elseExpr();
    
    thenExpr->accept(*this);
    if (elseExpr) {
        elseExpr->accept(*this);
        
        auto thenType = thenExpr->get_ret_type();
        auto elseType = elseExpr->get_ret_type();

        if (thenType == elseType) { // Check if types of both branches are the same
            expr.set_ret_type(thenType);
        } else if (!isPrimitive(thenType) && !isPrimitive(elseType)) {
            // Check common ancestor if both branches have class type
            expr.set_ret_type(commonAncestor(thenType, elseType));
        } else if (thenType == "unit" || elseType == "unit") { // One branch has type unit, the types agree
            expr.set_ret_type("unit");
        } else { // e type of both branches don’t agree
            throw std::runtime_error("types of branch then and else does not correspond");
        }
    } else {
        expr.set_ret_type("unit"); // Resulting type is unit if there is no else expression
    }
}

void TypeCheckerVisitor::visit(WhileNode& expr) {
    // Check condition is of bool type
    auto condExpr = expr.get_condExpr();
    condExpr->accept(*this);
    if (condExpr->get_ret_type() != "bool") {
        throw std::runtime_error("Condition expression of while loop must be of boolean type.");
    }

    // Evaluate loop body expression (can be any type)
    expr.get_bodyExpr()->accept(*this);

    // Resulting type of loop is always unit
    expr.set_ret_type("unit");
}

void TypeCheckerVisitor::visit(LetNode& expr) {
    /*
    if (expr.get_initExpr()) {
        // Evaluate initializer expression
        expr.get_initExpr()->accept(*this);
        std::string initType = expr.get_initExpr()->get_ret_type();
        
        // Check if initializer type conforms to declared type
        if (!conformsTo(initType, expr.get_type())) {
            throw std::runtime_error("Initializer expression of let statement does not conform to declared type.");
        }

        // Bind variable name to initializer value in symbol table
        bindVariable(expr.get_name(), initType);
    } else {
        // Bind variable name to default initializer value in symbol table
        std::string defaultInitType = getDefaultInitializerType(expr.get_type());
        bindVariable(expr.get_name(), defaultInitType);
    }

    // Evaluate scoped expression with bound variable name in symbol table
    std::string bodyType;
    bindScope();
    bindVariable(expr.get_name(), expr.get_type());
    expr.get_scopedExpr()->accept(*this);
    bodyType = expr.get_scopedExpr()->get_ret_type();
    unbindScope();

    // Set type of let expression to type of body expression
    expr.set_ret_type(bodyType);
    */
}

void TypeCheckerVisitor::visit(AssignNode& expr) {}
void TypeCheckerVisitor::visit(UnOpNode& expr) {}
void TypeCheckerVisitor::visit(NotUnOpNode& expr) {}
void TypeCheckerVisitor::visit(MinusUnOpNode& expr) {}
void TypeCheckerVisitor::visit(IsnullUnOpNode& expr) {}
void TypeCheckerVisitor::visit(BinOpNode& expr) {}
void TypeCheckerVisitor::visit(AddBinOpNode& expr) {}
void TypeCheckerVisitor::visit(MinusBinOpNode& expr) {}
void TypeCheckerVisitor::visit(MulBinOpNode& expr) {}
void TypeCheckerVisitor::visit(DivBinOpNode& expr) {}
void TypeCheckerVisitor::visit(LowerBinOpNode& expr) {}
void TypeCheckerVisitor::visit(LowerOrEqualBinOpNode& expr) {}
void TypeCheckerVisitor::visit(EqualBinOpNode& expr) {}
void TypeCheckerVisitor::visit(AndBinOpNode& expr) {}
void TypeCheckerVisitor::visit(PowBinOpNode& expr) {}
void TypeCheckerVisitor::visit(SelfNode& expr) {}
void TypeCheckerVisitor::visit(IdentifierNode& expr) {}
void TypeCheckerVisitor::visit(UnitNode& expr) {}
void TypeCheckerVisitor::visit(CallNode& expr) {}
void TypeCheckerVisitor::visit(BlockNode& expr) {}

void TypeCheckerVisitor::visit(LiteralNode& expr) {
    std::string type = expr.get_type();
    if (type == "int32") {
        try {
            int value = std::stoi(expr.get_value());
            if (value < INT32_MIN || value > INT32_MAX) {
                throw std::runtime_error("Expression : " + expr.get_value() + " is out of the bounds of int32");
            }
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("Expression : " + expr.get_value() + " is not of type int32");
        } catch (const std::out_of_range& e) {
            throw std::runtime_error("Expression : " + expr.get_value() + " is not of type int32");
        }
    }

    expr.set_ret_type(type);
}

void TypeCheckerVisitor::visit(NewNode& expr) {}

bool TypeCheckerVisitor::isPrimitive(const std::string type) const {
    auto it = std::find(m_primitive_types.begin(), m_primitive_types.end(), type);
    return it != m_primitive_types.end();
}

std::string TypeCheckerVisitor::parentTypeOf(const std::string type) const {
    for (const auto& classNode : m_ast.getClasses()) {
        if (classNode->getName() == type) {
            return classNode->getParent();
        }
    }

    // If the type is not found in any class, return an empty string
    return "";
}

std::vector<std::string> TypeCheckerVisitor::ancestorsOf(const std::string type) const {
    std::vector<std::string> ancestors;

    // Find the parent classes of the given type
    std::string parent = parentTypeOf(type);
    while (!parent.empty()) {
        ancestors.push_back(parent);
        parent = parentTypeOf(parent);
    }

    return ancestors;
}

std::string TypeCheckerVisitor::commonAncestor(const std::string typeA, const std::string typeB) const {
    auto ancestorsA = ancestorsOf(typeA);
    
    std::string parent = parentTypeOf(typeB);
    while (!parent.empty()) {
        if(std::find(ancestorsA.begin(), ancestorsA.end(), parent) != ancestorsA.end()) {
            return parent;
        }
        parent = parentTypeOf(parent);
    }

    return "";
}

bool TypeCheckerVisitor::conformsTo(const std::string typeA, const std::string typeB) const {
    if (typeA == typeB) {
        return true;
    }
    
    std::string parent = parentTypeOf(typeA);
    while (!parent.empty()) {
        if(parent == typeB) {
            return true;
        }
        parent = parentTypeOf(parent);
    }

    return false;
}