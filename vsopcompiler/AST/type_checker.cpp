#include <algorithm>
#include <iostream>
#include "type_checker.hpp"

void TypeCheckerVisitor::visit(BaseNode &expr)
{
}

void TypeCheckerVisitor::visit(ProgramNode &expr)
{
    m_fTable.enter_scope();

    // Add all functions to symbol table
    for (auto const &classNode : expr.getClasses())
    {
        for (auto const &methodNode : classNode->getBody()->getMethods())
        {
            std::vector<std::string> parameters_types;
            for (auto const &parameter : methodNode->getFormals())
            {
                parameters_types.push_back(parameter->getType());
            }
            FunctionType type(methodNode->getRetType(), parameters_types);
            try
            {
                m_fTable.insert(classNode->getName() + "." + methodNode->getName(), type);
            }
            catch (const SymbolException &e)
            {
                throw SemanticException(methodNode->getRow(), methodNode->getCol(), e.what());
            }
        }
    }

    // Check if main function exists
    if (!m_fTable.exists("Main.main"))
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Main function does not exist");
    }

    // Check if main function has correct signature
    auto main_type = m_fTable.lookup("Main.main");
    if (main_type.return_type() != "int32" || !main_type.parameter_types().empty())
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Main function has incorrect signature, should be () -> int32");
    }

    // Visit all classes in the program
    for (auto const &classNode : expr.getClasses())
    {
        if (classNode->getName() != "Object")
            classNode->accept(*this);
    }

    m_fTable.exit_scope();
}

void TypeCheckerVisitor::visit(ClassNode &expr)
{
    try
    {
        checkCycle(expr.getName());
    }
    catch (const InheritanceException &e)
    {
        throw SemanticException(expr.getRow(), expr.getCol(), e.what());
    }

    // Set current class
    m_currentClass = expr.getName();

    m_vTable.enter_scope();
    expr.getBody()->accept(*this);
    m_vTable.exit_scope();
}

void TypeCheckerVisitor::visit(ClassBodyNode &expr)
{
    // Visit all fields and methods in the class body
    for (auto const &node : expr.getFields())
    {
        node->accept(*this);
    }
    for (auto const &node : expr.getMethods())
    {
        node->accept(*this);
    }
}

void TypeCheckerVisitor::visit(FieldNode &expr)
{
    // Check if field type is valid
    if (!isValidType(expr.getType()))
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Invalid type for field " + expr.getName());
    }

    // Bind field name to type in symbol table
    try
    {
        m_vTable.insert(expr.getName(), expr.getType());
    }
    catch (const SymbolException &e)
    {
        throw SemanticException(expr.getRow(), expr.getCol(), e.what());
    }

    // Check if field has initializer expression
    if (expr.getInitExpr())
    {
        // Check if field initializer expression is of correct type
        m_vTable.deactive();
        m_fTable.deactive();
        expr.getInitExpr()->accept(*this);
        m_vTable.active();
        m_fTable.active();
        try
        {
            if (!conformsTo(expr.getInitExpr()->get_ret_type(), expr.getType()))
            {
                throw SemanticException(expr.getRow(), expr.getCol(), "Field initializer expression does not conform to declared type");
            }
        }
        catch (const InheritanceException &e)
        {
            throw SemanticException(expr.getRow(), expr.getCol(), e.what());
        }
    }
}

void TypeCheckerVisitor::visit(MethodNode &expr)
{
    m_vTable.enter_scope();

    // Check if method return type is valid
    if (!isValidType(expr.getRetType()))
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Invalid return type for method " + expr.getName());
    }

    // Add formal parameters to symbol table
    for (auto const &formal : expr.getFormals())
    {
        formal->accept(*this);
    }
    // Visit method body
    expr.getBlock()->accept(*this);

    // Check if method body conforms to declared return type
    if (expr.getBlock()->get_ret_type() != expr.getRetType())
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Method body does not conform to declared return type");
    }
    m_vTable.exit_scope();
}

void TypeCheckerVisitor::visit(FormalNode &expr)
{
    // Check if formal type is valid
    if (!isValidType(expr.getType()))
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Invalid type for formal " + expr.getName());
    }

    // Bind formal name to type in symbol table
    try
    {
        m_vTable.insert(expr.getName(), expr.getType());
    }
    catch (const SymbolException &e)
    {
        throw SemanticException(expr.getRow(), expr.getCol(), e.what());
    }
}

// ==================== Expressions ====================

void TypeCheckerVisitor::visit(IfNode &expr)
{
    // Check condition is of bool type
    auto condExpr = expr.get_condExpr();
    condExpr->accept(*this);
    if (condExpr->get_ret_type() != "bool")
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Condition expression of if statement must be of boolean type.");
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
            try
            {

                expr.set_ret_type(commonAncestor(thenType, elseType));
            }
            catch (const InheritanceException &e)
            {
                throw SemanticException(expr.getRow(), expr.getCol(), e.what());
            }
        }
        else if (thenType == "unit" || elseType == "unit")
        { // One branch has type unit, the types agree
            expr.set_ret_type("unit");
        }
        else
        { // e type of both branches don’t agree
            throw SemanticException(expr.getRow(), expr.getCol(), "Types of branch then and else does not correspond");
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
        throw SemanticException(expr.getRow(), expr.getCol(), "Condition expression of while loop must be of boolean type.");
    }

    // Evaluate loop body expression (can be any type)
    expr.get_bodyExpr()->accept(*this);

    // Resulting type of loop is always unit
    expr.set_ret_type("unit");
}

void TypeCheckerVisitor::visit(LetNode &expr)
{
    if (expr.get_initExpr())
    {
        // Check if initializer expression is of correct type
        expr.get_initExpr()->accept(*this);
        std::string initType = expr.get_initExpr()->get_ret_type();
        if (!conformsTo(initType, expr.get_type()))
            throw SemanticException(expr.getRow(), expr.getCol(), "Initializer expression of let statement does not conform to declared type.");
    }
    else
    {
        // Check if type is valid
        if (!isValidType(expr.get_type()))
            throw SemanticException(expr.getRow(), expr.getCol(), "Invalid type for let statement " + expr.get_name());
    }

    // Bind variable name to type in symbol table
    try
    {
        m_vTable.insert(expr.get_name(), expr.get_type());
    }
    catch (const SymbolException &e)
    {
        throw SemanticException(expr.getRow(), expr.getCol(), e.what());
    }
    m_vTable.enter_scope();
    expr.get_scopedExpr()->accept(*this);
    m_vTable.exit_scope();
    expr.set_ret_type(expr.get_scopedExpr()->get_ret_type());
}

void TypeCheckerVisitor::visit(AssignNode &expr)
{
    try
    {
        expr.get_assign_expr()->accept(*this);
        std::string id_type = m_vTable.lookup(expr.get_name());

        std::string assign_expr_type = expr.get_assign_expr()->get_ret_type();

        if (id_type != assign_expr_type)
            throw SemanticException(expr.getRow(), expr.getCol(), "Invalid value for assignment, got \"" + assign_expr_type + "\" instead of \"" + id_type + "\"");
        expr.set_ret_type(id_type);
    }
    catch (SymbolException &e)
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Variable " + expr.get_name() + " is not defined");
    }
}

void TypeCheckerVisitor::visit(UnOpNode &expr)
{
    expr.get_expr()->accept(*this);
    expr.set_ret_type(expr.get_expr()->get_ret_type());
}

void TypeCheckerVisitor::visit(NotUnOpNode &expr)
{
    expr.get_expr()->accept(*this);
    if (expr.get_expr()->get_ret_type() != "bool")
        throw SemanticException(expr.getRow(), expr.getCol(), "Expression of not operator must be of bool type.");
    expr.set_ret_type("bool");
}

void TypeCheckerVisitor::visit(MinusUnOpNode &expr)
{
    expr.get_expr()->accept(*this);
    if (expr.get_expr()->get_ret_type() != "int32")
        throw SemanticException(expr.getRow(), expr.getCol(), "Expression of minus operator must be of int32 type.");
    expr.set_ret_type("int32");
}

void TypeCheckerVisitor::visit(IsnullUnOpNode &expr)
{
    expr.get_expr()->accept(*this);
    if (isPrimitive(expr.get_expr()->get_ret_type()))
        throw SemanticException(expr.getRow(), expr.getCol(), "Expression of isnull operator must be of class type.");
    expr.set_ret_type("bool");
}

void TypeCheckerVisitor::visit(BinOpNode &expr)
{
    expr.get_leftExpr()->accept(*this);
    expr.get_rightExpr()->accept(*this);
}

void TypeCheckerVisitor::visit(AddBinOpNode &expr)
{
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != "int32" || rightExpr->get_ret_type() != "int32")
        throw SemanticException(expr.getRow(), expr.getCol(), "Left and right expressions of minus operator must be of type int32.");

    expr.set_ret_type("int32");
}

void TypeCheckerVisitor::visit(MinusBinOpNode &expr)
{
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != "int32" || rightExpr->get_ret_type() != "int32")
        throw SemanticException(expr.getRow(), expr.getCol(), "Left and right expressions of minus operator must be of type int32.");

    expr.set_ret_type("int32");
}

void TypeCheckerVisitor::visit(MulBinOpNode &expr)
{
    // Check if left and right expressions are of same type
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != "int32" || rightExpr->get_ret_type() != "int32")
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Left and right expressions of multiplication operator must be of type int32.");
    }

    // Resulting type of multiplication operator is int
    expr.set_ret_type("int32");
}

void TypeCheckerVisitor::visit(DivBinOpNode &expr)
{
    // Check if left and right expressions are of same type
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != "int32" || rightExpr->get_ret_type() != "int32")
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Left and right expressions of division operator must be of type int32.");
    }

    // Resulting type of division operator is int
    expr.set_ret_type("int32");
}

void TypeCheckerVisitor::visit(LowerBinOpNode &expr)
{
    // Check if left and right expressions are of same type
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != "int32" || rightExpr->get_ret_type() != "int32")
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Left and right expressions of lower operator must be of type int32.");
    }

    // Resulting type of lower operator is bool
    expr.set_ret_type("bool");
}

void TypeCheckerVisitor::visit(LowerOrEqualBinOpNode &expr)
{
    // Check if left and right expressions are of same type
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != "int32" || rightExpr->get_ret_type() != "int32")
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Left and right expressions of lower or equal operator must be of type int32.");
    }

    // Resulting type of lower or equal operator is bool
    expr.set_ret_type("bool");
}

void TypeCheckerVisitor::visit(EqualBinOpNode &expr)
{
    // Check if left and right expressions are of same type
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != rightExpr->get_ret_type())
    {
        throw SemanticException(expr.getRow(), expr.getRow(), "Left and right expressions of equal operator must be of same type.");
    }

    // Resulting type of equal operator is bool
    expr.set_ret_type("bool");
}

void TypeCheckerVisitor::visit(AndBinOpNode &expr)
{
    // Check if left and right expressions are of bool type
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != "bool" || rightExpr->get_ret_type() != "bool")
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Left and right expressions of and operator must be of boolean type.");
    }

    // Resulting type of and operator is bool
    expr.set_ret_type("bool");
}

void TypeCheckerVisitor::visit(PowBinOpNode &expr)
{
    // Check if left and right expressions are of int32 type
    auto leftExpr = expr.get_leftExpr();
    auto rightExpr = expr.get_rightExpr();

    leftExpr->accept(*this);
    rightExpr->accept(*this);

    if (leftExpr->get_ret_type() != "int32" || rightExpr->get_ret_type() != "int32")
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Left and right expressions of pow operator must be of int32 type.");
    }

    // Resulting type of pow operator is int32
    expr.set_ret_type("int32");
}

void TypeCheckerVisitor::visit(SelfNode &expr)
{
    expr.set_ret_type(m_currentClass);
}

void TypeCheckerVisitor::visit(IdentifierNode &expr)
{
    try
    {
        // Lookup variable in symbol table
        auto varType = m_vTable.lookup(expr.getName());

        // Set type of identifier expression
        expr.set_ret_type(varType);
    }
    catch (const SymbolException &e)
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Variable " + expr.getName() + " is not defined.");
    }
}

void TypeCheckerVisitor::visit(UnitNode &expr)
{
    expr.set_ret_type("unit");
}

void TypeCheckerVisitor::visit(CallNode &expr)
{
    // Visit object expression
    expr.getObjExpr()->accept(*this);

    // Lookup for method on the object expression's type
    auto objectType = expr.getObjExpr()->get_ret_type();
    try
    {
        auto functionType = lookupMethod(objectType, expr.getMethodName());

        // Check if the number of arguments match the number of parameters
        if (functionType.parameter_types().size() != expr.getExprList().size())
        {
            throw SemanticException(expr.getRow(), expr.getCol(), "The number of arguments does not match with the number of expected parameters");
        }

        // Check if argument types matches the expected types
        for (std::size_t i = 0; i < functionType.parameter_types().size(); ++i)
        {
            expr.getExprList()[i]->accept(*this);

            auto paramType = functionType.parameter_types()[i];
            auto argType = expr.getExprList()[i]->get_ret_type();
            if (paramType != argType)
            {
                throw SemanticException(expr.getRow(), expr.getCol(), "Expected type : " + paramType + " got " + argType);
            }
        }

        // Set return type of the call to the return type of the function
        expr.set_ret_type(functionType.return_type());
    }
    catch (SymbolException &e)
    {
        throw SemanticException(expr.getRow(), expr.getCol(), "Method " + expr.getMethodName() + " not found on type " + objectType);
    }
    catch (InheritanceException &e)
    {
        throw SemanticException(expr.getRow(), expr.getCol(), e.what());
    }
}

void TypeCheckerVisitor::visit(BlockNode &expr)
{
    // visit all expressions in block
    for (auto const &e : expr.getExpressions())
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
            {
                throw SemanticException(expr.getRow(), expr.getRow(), "Expression : " + expr.get_value() + " is out of the bounds of int32");
            }
        }
        catch (const std::invalid_argument &e)
        {
            throw SemanticException(expr.getRow(), expr.getRow(), "Expression : " + expr.get_value() + " is not of type int32");
        }
        catch (const std::out_of_range &e)
        {
            throw SemanticException(expr.getRow(), expr.getRow(), "Expression : " + expr.get_value() + " is not of type int32");
        }
    }

    expr.set_ret_type(type);
}

void TypeCheckerVisitor::visit(NewNode &expr)
{
    std::string newType = expr.get_type();
    if (!isClass(newType))
        throw SemanticException(expr.getRow(), expr.getCol(), "Type : " + newType + " is unknown");
    expr.set_ret_type(newType);
}

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
    throw InheritanceException("Type : " + type + " is undefined");
}

void TypeCheckerVisitor::checkCycle(const std::string &type) const
{

    std::string parent = parentTypeOf(type);

    while (!parent.empty())
    {
        if (parent == type)
        {
            throw InheritanceException("Type : " + type + " is involeved in a cycle");
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

FunctionType TypeCheckerVisitor::lookupMethod(const std::string &type, const std::string methodName) const
{
    auto typesToSearchMethod = ancestorsOf(type);
    typesToSearchMethod.push_back(type);

    for (const auto &typeToSearchMethod : typesToSearchMethod)
    {
        try
        {
            return m_fTable.lookup(typeToSearchMethod + "." + methodName);
        }
        catch (SymbolException &e)
        {
        }
    }

    throw SymbolException("Method " + methodName + " not found on type " + type);
}