#include <iostream>
#include "nodes.hpp"

void Serializer::setType(const std::string &type)
{
    m_hasType = true;
    m_buffer << type << "(";
}

void Serializer::setRetType(const std::string &type)
{
    m_ret_type = type;
}

void Serializer::addString(const std::string &str)
{
    if (m_hasPrevious)
    {
        if (m_inList)
        {
            m_buffer << ",\n";
        }
        else
        {
            m_buffer << ", ";
        }
    }

    m_buffer << str;
    m_hasPrevious = true;
}

void Serializer::startList()
{
    if (m_hasPrevious)
    {
        m_buffer << ", ";
    }
    m_inList = true;
    m_hasPrevious = false;
    m_buffer << "[";
}

void Serializer::endList()
{
    m_inList = false;
    m_hasPrevious = true;
    m_buffer << "]";
}

std::string Serializer::serialize()
{
    if (m_hasType)
    {
        m_buffer << ")";
    }
    if (!m_ret_type.empty())
    {
        m_buffer << " : " << m_ret_type;
    }
    std::string result = m_buffer.str();
    m_buffer.str("");
    return result;
}

std::string ProgramNode::serialize() const
{
    Serializer serializer;
    serializer.startList();
    for (auto &classNode : m_classes)
    {
        if (classNode->getName() != "Object")
            serializer.addString(classNode->serialize());
    }
    serializer.endList();
    return serializer.serialize();
}

std::string ClassBodyNode::serialize() const
{
    Serializer serializer;
    serializer.startList();
    for (auto &fieldNode : m_fields)
    {
        serializer.addString(fieldNode->serialize());
    }
    serializer.endList();
    serializer.startList();
    for (auto &methodNode : m_methods)
    {
        serializer.addString(methodNode->serialize());
    }
    serializer.endList();
    return serializer.serialize();
}

void ClassBodyNode::addMethod(std::shared_ptr<MethodNode> method)
{
    m_methods.push_back(method);
}

void ClassBodyNode::addField(std::shared_ptr<FieldNode> field)
{
    m_fields.push_back(field);
}

std::string ClassNode::serialize() const
{
    Serializer serializer;
    serializer.setType("Class");
    serializer.addString(m_name);
    serializer.addString(m_parent);
    serializer.addString(m_classBody->serialize());
    return serializer.serialize();
}

std::string FieldNode::serialize() const
{

    Serializer serializer;
    serializer.setType("Field");
    serializer.addString(m_name);
    serializer.addString(m_type);
    if (m_initExpr)
        serializer.addString(m_initExpr->serialize());
    return serializer.serialize();
}

std::string MethodNode::serialize() const
{
    Serializer serializer;
    serializer.setType("Method");
    serializer.addString(m_name);
    serializer.startList();
    for (auto &formalNode : m_formals)
    {
        serializer.addString(formalNode->serialize());
    }
    serializer.endList();
    serializer.addString(m_retType);
    serializer.addString(m_block->serialize());
    return serializer.serialize();
}

std::string FormalNode::serialize() const
{
    return m_name + " : " + m_type;
}

std::string IfNode::serialize() const
{
    Serializer serializer;
    serializer.setType("If");
    serializer.setRetType(get_ret_type());
    serializer.addString(m_condExpr->serialize());
    serializer.addString(m_thenExpr->serialize());
    if (m_elseExpr)
    {
        serializer.addString(m_elseExpr->serialize());
    }
    return serializer.serialize();
}

std::string WhileNode::serialize() const
{
    Serializer serializer;
    serializer.setType("While");
    serializer.setRetType(get_ret_type());
    serializer.addString(m_condExpr->serialize());
    serializer.addString(m_bodyExpr->serialize());
    return serializer.serialize();
}

std::string LetNode::serialize() const
{
    Serializer serializer;
    serializer.setType("Let");
    serializer.setRetType(get_ret_type());
    serializer.addString(m_name);
    serializer.addString(m_type);
    if (m_initExpr)
    {
        serializer.addString(m_initExpr->serialize());
    }
    serializer.addString(m_scopedExpr->serialize());
    return serializer.serialize();
}

std::string AssignNode::serialize() const
{
    Serializer serializer;
    serializer.setType("Assign");
    serializer.setRetType(get_ret_type());
    serializer.addString(m_name);
    serializer.addString(m_expr->serialize());
    return serializer.serialize();
}

std::string UnOpNode::serialize() const
{
    Serializer serializer;
    serializer.setType("UnOp");
    serializer.setRetType(get_ret_type());
    completeOperator(serializer);
    serializer.addString(m_expr->serialize());
    return serializer.serialize();
}

std::string BinOpNode::serialize() const
{
    Serializer serializer;
    serializer.setType("BinOp");
    serializer.setRetType(get_ret_type());
    completeOperator(serializer);
    serializer.addString(m_lExpr->serialize());
    serializer.addString(m_rExpr->serialize());
    return serializer.serialize();
}

std::string IdentifierNode::serialize() const
{
    Serializer serializer;
    serializer.addString(m_name);
    serializer.setRetType(get_ret_type());
    return serializer.serialize();
}

std::string SelfNode::serialize() const
{
    Serializer serializer;
    serializer.addString("self");
    serializer.setRetType(get_ret_type());
    return serializer.serialize();
}

std::string UnitNode::serialize() const
{
    Serializer serializer;
    serializer.addString("()");
    serializer.setRetType(get_ret_type());
    return serializer.serialize();
}

std::string CallNode::serialize() const
{
    Serializer serializer;
    serializer.setType("Call");
    serializer.addString(m_objExpr->serialize());
    serializer.addString(m_methodName);
    serializer.startList();
    for (auto &expr : m_exprList)
    {
        serializer.addString(expr->serialize());
    }
    serializer.endList();
    serializer.setRetType(get_ret_type());
    return serializer.serialize();
}

std::string BlockNode::serialize() const
{
    Serializer serializer;
    serializer.startList();
    for (auto &expressionNode : m_expressions)
    {
        serializer.addString(expressionNode->serialize());
    }
    serializer.endList();
    serializer.setRetType(get_ret_type());
    return serializer.serialize();
}

std::string LiteralNode::serialize() const
{
    Serializer serializer;
    serializer.addString(m_value);
    serializer.setRetType(get_ret_type());
    return serializer.serialize();
}

std::string NewNode::serialize() const
{
    Serializer serializer;
    serializer.setType("New");
    serializer.setRetType(get_ret_type());
    serializer.addString(m_typeName);
    return serializer.serialize();
}