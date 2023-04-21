#include "type_checker.hpp"

#include <algorithm>
#include <iostream>

void TypeCheckerVisitor::visit(BaseNode &expr) {}

void TypeCheckerVisitor::visit(ProgramNode &expr)
{
    m_fTable.enter_scope();

    // Add all functions to symbol table
    for (auto &classNode : expr.getClasses())
    {
        for (auto &methodNode : classNode->getBody()->getMethods())
        {
            std::vector<std::string> parameters_types;
            for (auto &parameter : methodNode->getFormals())
            {
                parameters_types.push_back(parameter->getType());
            }
            FunctionType type(methodNode->getRetType(), parameters_types);
            m_fTable.insert(classNode->getName() + "." + methodNode->getName(), type);
        }
    }

    // Check if main function exists
    if (!m_fTable.exists("Main.main"))
    {
        throw SemanticException("Main function does not exist");
    }

    // Check if main function has correct signature
    auto main_type = m_fTable.lookup("Main.main");
    if (main_type.return_type() != "int32" || main_type.parameter_types().size() != 0)
    {
        throw SemanticException("Main function has incorrect signature, should be () -> int32");
    }

    // Visit all classes in the program
    for (auto &classNode : expr.getClasses())
    {
        classNode->accept(*this);
    }
    
    m_fTable.exit_scope();
}

void TypeCheckerVisitor::visit(ClassNode &expr)
{
    checkCycle(expr.getName());

    m_vTable.enter_scope();
    expr.getBody()->accept(*this);
    m_vTable.exit_scope();
}

void TypeCheckerVisitor::visit(ClassBodyNode &expr)
{
    // Visit all fields and methods in the class body
    for (auto &node : expr.getFields())
    {
        node->accept(*this);
    }
    for (auto &node : expr.getMethods())
    {
        node->accept(*this);
    }
}

void TypeCheckerVisitor::visit(FieldNode &expr)
{
    // Check if field type is valid
    if (!isValidType(expr.getType()))
    {
        throw SemanticException("Invalid type for field " + expr.getName());
    }

    // Bind field name to type in symbol table
    m_vTable.insert(expr.getName(), expr.getType());

    // Check if field has initializer expression
    if (expr.getInitExpr())
    {
        // Check if field initializer expression is of correct type
        m_vTable.deactive();
        m_fTable.deactive();
        expr.getInitExpr()->accept(*this);
        m_vTable.active();
        m_fTable.active();
        if (conformsTo(expr.getInitExpr()->get_ret_type(), expr.getType()))
        {
            throw SemanticException("Field initializer expression does not conform to declared type");
        }
    }
}

void TypeCheckerVisitor::visit(MethodNode &expr)
{
    m_vTable.enter_scope();

    // Check if method return type is valid
    if (!isValidType(expr.getRetType()))
    {
        throw SemanticException("Invalid return type for method " + expr.getName());
    }

    // Add formal parameters to symbol table
    for (auto &formal : expr.getFormals())
    {
        formal->accept(*this);
    }

    // Visit method body
    expr.getBlock()->accept(*this);

    // Check if method body conforms to declared return type
    if (expr.getBlock()->get_ret_type() != expr.getRetType())
    {
        throw SemanticException("Method body does not conform to declared return type");
    }

    m_vTable.exit_scope();
}

void TypeCheckerVisitor::visit(FormalNode &expr)
{
    // Check if formal type is valid
    if (!isValidType(expr.getType()))
    {
        throw SemanticException("Invalid type for formal " + expr.getName());
    }

    // Bind formal name to type in symbol table
    m_vTable.insert(expr.getName(), expr.getType());
}

// ==================== Expressions ====================

void TypeCheckerVisitor::visit(IfNode &expr)
{
    // Check condition is of bool type
    auto condExpr = expr.get_condExpr();
    condExpr->accept(*this);
    if (condExpr->get_ret_type() != "bool")
    {
        throw SemanticException("Condition expression of if statement must be of boolean type.");
    }

    // Check branch expressions
    auto thenExpr = expr.get_thenExpr();
    auto elseExpr = expr.get_elseExpr();

    thenExpr->accept(*this);
    if (elseExpr)
    {
        elseExpr->accept(*this);

        auto thenType = thenExpr->get_ret_type();
        auto elseType = elseExpr->get_ret_type();

        if (thenType == elseType)
        { // Check if types of both branches are the same
            expr.set_ret_type(thenType);
        }
        else if (!isPrimitive(thenType) && !isPrimitive(elseType))
        {
            // Check common ancestor if both branches have class type
            expr.set_ret_type(commonAncestor(thenType, elseType));
        }
        else if (thenType == "unit" || elseType == "unit")
        { // One branch has type unit, the types agree
            expr.set_ret_type("unit");
        }
        else
        { // e type of both branches don’t agree
            throw SemanticException("types of branch then and else does not correspond");
        }
    }
    else
    {
        expr.set_ret_type("unit"); // Resulting type is unit if there is no else expression
    }
}

void TypeCheckerVisitor::visit(WhileNode &expr)
{
    // Check condition is of bool type
    auto condExpr = expr.get_condExpr();
    condExpr->accept(*this);
    if (condExpr->get_ret_type() != "bool")
    {
        throw SemanticException("Condition expression of while loop must be of boolean type.");
    }

    // Evaluate loop body expression (can be any type)
    expr.get_bodyExpr()->accept(*this);

    // Resulting type of loop is always unit
    expr.set_ret_type("unit");
}

void TypeCheckerVisitor::visit(LetNode &expr)
{
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

void TypeCheckerVisitor::visit(AssignNode &expr) {}
void TypeCheckerVisitor::visit(UnOpNode &expr) {}
void TypeCheckerVisitor::visit(NotUnOpNode &expr) {}
void TypeCheckerVisitor::visit(MinusUnOpNode &expr) {}
void TypeCheckerVisitor::visit(IsnullUnOpNode &expr) {}
void TypeCheckerVisitor::visit(BinOpNode &expr) {}
void TypeCheckerVisitor::visit(AddBinOpNode &expr) {}
void TypeCheckerVisitor::visit(MinusBinOpNode &expr) {}
void TypeCheckerVisitor::visit(MulBinOpNode &expr) {}
void TypeCheckerVisitor::visit(DivBinOpNode &expr) {}
void TypeCheckerVisitor::visit(LowerBinOpNode &expr) {}
void TypeCheckerVisitor::visit(LowerOrEqualBinOpNode &expr) {}
void TypeCheckerVisitor::visit(EqualBinOpNode &expr) {}
void TypeCheckerVisitor::visit(AndBinOpNode &expr) {}
void TypeCheckerVisitor::visit(PowBinOpNode &expr) {}
void TypeCheckerVisitor::visit(SelfNode &expr) {}

void TypeCheckerVisitor::visit(IdentifierNode &expr)
{
}

void TypeCheckerVisitor::visit(UnitNode &expr) {}

void TypeCheckerVisitor::visit(CallNode &expr) 
{
    // Visit object expression
    expr.getObjExpr()->accept(*this);

    // Lookup for method on the object expression's type
    auto objectType = expr.getObjExpr()->get_ret_type();
    auto functionType = m_fTable.lookup(objectType + "." + expr.getMethodName());

    // Check if the number of arguments match the number of parameters
    if(functionType.parameter_types().size() != expr.getExprList().size())
    {
        throw SemanticException("The number of arguments does not match with the number of expected parameters");
    }

    // Check if argument types matches the expected types
    for (int i = 0; i < functionType.parameter_types().size(); ++i)
    {
        expr.getExprList()[i]->accept(*this);

        auto paramType = functionType.parameter_types()[i];
        auto argType = expr.getExprList()[i]->get_ret_type();
        if (paramType != argType)
        {
            throw SemanticException("Expected type : " + paramType + " got " + argType);
        }
    }

    // Set return type of the call to the return type of the function
    expr.set_ret_type(functionType.return_type());
}

void TypeCheckerVisitor::visit(BlockNode &expr) 
{
    // visit all expressions in block
    for (auto &e : expr.getExpressions())
    {
        e->accept(*this);
    }

    expr.set_ret_type(expr.getExpressions().back()->get_ret_type());
}

void TypeCheckerVisitor::visit(LiteralNode &expr)
{
    std::string type = expr.get_type();
    if (type == "int32")
    {
        try
        {
            int value = std::stoi(expr.get_value());
            if (value < INT32_MIN || value > INT32_MAX)
            { // TODO change to semantic exception
                throw std::runtime_error("Expression : " + expr.get_value() + " is out of the bounds of int32");
            }
        }
        catch (const std::invalid_argument &e)
        {
            throw std::runtime_error("Expression : " + expr.get_value() + " is not of type int32");
        }
        catch (const std::out_of_range &e)
        {
            throw std::runtime_error("Expression : " + expr.get_value() + " is not of type int32");
        }
    }

    expr.set_ret_type(type);
}

void TypeCheckerVisitor::visit(NewNode &expr) {}

bool TypeCheckerVisitor::isPrimitive(const std::string &type) const
{
    auto it = std::find(m_primitive_types.begin(), m_primitive_types.end(), type);
    return it != m_primitive_types.end();
}

bool TypeCheckerVisitor::isClass(const std::string &type) const
{
    for (const auto &classNode : m_ast.getClasses())
    {
        if (classNode->getName() == type)
        {
            return true;
        }
    }
    return false;
}

std::string TypeCheckerVisitor::parentTypeOf(const std::string &type) const
{
    if (type == "Object")
    {
        return "";
    }

    for (const auto &classNode : m_ast.getClasses())
    {
        if (classNode->getName() == type)
        {
            return classNode->getParent();
        }
    }

    // If the type is not found in any class, throw error
    throw SemanticException("Type : " + type + " is undefined");
}

std::string TypeCheckerVisitor::checkCycle(const std::string &type) const
{
    std::string parent = parentTypeOf(type);
    while (!parent.empty())
    {
        if (parent == type)
        {
            throw SemanticException("Type : " + type + " is involeved in a cycle");
        }
        parent = parentTypeOf(parent);
    }
}

std::vector<std::string> TypeCheckerVisitor::ancestorsOf(const std::string &type) const
{
    std::vector<std::string> ancestors;

    // Find the parent classes of the given type
    std::string parent = parentTypeOf(type);
    while (!parent.empty())
    {
        ancestors.push_back(parent);
        parent = parentTypeOf(parent);
    }

    return ancestors;
}

std::string TypeCheckerVisitor::commonAncestor(const std::string &typeA, const std::string &typeB) const
{
    auto ancestorsA = ancestorsOf(typeA);

    std::string parent = parentTypeOf(typeB);
    while (!parent.empty())
    {
        if (std::find(ancestorsA.begin(), ancestorsA.end(), parent) != ancestorsA.end())
        {
            return parent;
        }
        parent = parentTypeOf(parent);
    }

    return "";
}

bool TypeCheckerVisitor::conformsTo(const std::string &typeA, const std::string &typeB) const
{
    if (typeA == typeB)
    {
        return true;
    }

    std::string parent = parentTypeOf(typeA);
    while (!parent.empty())
    {
        if (parent == typeB)
        {
            return true;
        }
        parent = parentTypeOf(parent);
    }

    return false;
}

bool TypeCheckerVisitor::isValidType(const std::string &type) const
{
    return isPrimitive(type) || isClass(type);
}