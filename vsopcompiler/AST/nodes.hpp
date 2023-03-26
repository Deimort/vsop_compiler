#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

class ProgramNode;
class ClassNode;
class ClassBodyNode;
class FieldNode;
class MethodNode;
class FormalNode;
class IfNode;
class WhileNode;
class LetNode;
class AssignNode;
class BlockNode;
class CallNode;
class NewNode;
class ExprNode;
class UnOpNode;
class BinOpNode;
class LiteralNode;

class Serializer
{
public:
    void setType(const std::string &type);
    void addString(const std::string &str);
    void startList();
    void endList();
    std::string serialize();

private:
    bool m_hasType = false;
    bool m_hasPrevious = false;
    bool m_inList = false;
    std::stringstream m_buffer;
};

class Serializable
{
public:
    virtual ~Serializable() {}
    virtual std::string serialize() const = 0;
};

class ProgramNode : public Serializable
{
public:
    ProgramNode(std::vector<std::shared_ptr<ClassNode>> classes)
        : m_classes(classes) {}

    std::string serialize() const override;

private:
    std::vector<std::shared_ptr<ClassNode>> m_classes;
};

class ClassBodyNode : public Serializable
{
public:
    void addField(std::shared_ptr<FieldNode> field);
    void addMethod(std::shared_ptr<MethodNode> method);
    std::string serialize() const override;

private:
    std::vector<std::shared_ptr<FieldNode>> m_fields;
    std::vector<std::shared_ptr<MethodNode>> m_methods;
};

class ClassNode : public Serializable
{
public:
    ClassNode(const std::string &name, std::shared_ptr<ClassBodyNode> classBody, const std::string &parent = "Object")
        : m_name(name), m_parent(parent), m_classBody(classBody) {}

    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_parent;
    std::shared_ptr<ClassBodyNode> m_classBody;
};

class FieldNode : public Serializable
{
public:
    FieldNode(const std::string &name, const std::string &type, const std::shared_ptr<ExprNode> &initExpr = nullptr)
        : m_name(name), m_type(type), m_initExpr(initExpr) {}

    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_type;
    std::shared_ptr<ExprNode> m_initExpr;
};

class MethodNode : public Serializable
{
public:
    MethodNode(const std::string &name, std::vector<std::shared_ptr<FormalNode>> formals,
               const std::string &retType, std::shared_ptr<BlockNode> block)
        : m_name(name), m_formals(formals), m_retType(retType), m_block(block) {}

    std::string serialize() const override;

private:
    std::string m_name;
    std::vector<std::shared_ptr<FormalNode>> m_formals;
    std::string m_retType;
    std::shared_ptr<BlockNode> m_block;
};

class FormalNode : public Serializable
{
public:
    FormalNode(const std::string &name, const std::string &type)
        : m_name(name), m_type(type) {}

    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_type;
};

class ExprNode : public Serializable
{
};

class IfNode : public ExprNode
{
public:
    IfNode(std::shared_ptr<ExprNode> condExpr, std::shared_ptr<ExprNode> thenExpr, std::shared_ptr<ExprNode> elseExpr = nullptr)
        : m_condExpr(condExpr), m_thenExpr(thenExpr), m_elseExpr(elseExpr) {}
    std::string serialize() const override;

private:
    std::shared_ptr<ExprNode> m_condExpr;
    std::shared_ptr<ExprNode> m_thenExpr;
    std::shared_ptr<ExprNode> m_elseExpr;
};

class WhileNode : public ExprNode
{
public:
    WhileNode(std::shared_ptr<ExprNode> condExpr, std::shared_ptr<ExprNode> bodyExpr)
        : m_condExpr(condExpr), m_bodyExpr(bodyExpr) {}
    std::string serialize() const override;

private:
    std::shared_ptr<ExprNode> m_condExpr;
    std::shared_ptr<ExprNode> m_bodyExpr;
};

class LetNode : public ExprNode
{
public:
    LetNode(const std::string &name,
            const std::string &type, std::shared_ptr<ExprNode> scopedExpr,
            std::shared_ptr<ExprNode> initExpr = nullptr)
        : m_name(name), m_type(type), m_scopedExpr(scopedExpr), m_initExpr(initExpr) {}
    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_type;
    std::shared_ptr<ExprNode> m_scopedExpr;
    std::shared_ptr<ExprNode> m_initExpr;
};

class AssignNode : public ExprNode
{
public:
    AssignNode(const std::string &name, std::shared_ptr<ExprNode> expr)
        : m_name(name), m_expr(expr) {}
    std::string serialize() const override;

private:
    std::string m_name;
    std::shared_ptr<ExprNode> m_expr;
};

class UnOpNode : public ExprNode
{
public:
    UnOpNode(std::shared_ptr<ExprNode> expr) : m_expr(expr) {}

    std::string serialize() const override;

protected:
    virtual void completeOperator(Serializer &serializer) const = 0;

private:
    std::shared_ptr<ExprNode> m_expr;
};

class NotUnOpNode : public UnOpNode
{
public:
    NotUnOpNode(std::shared_ptr<ExprNode> expr) : UnOpNode(expr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("not");
    }
};

class MinusUnOpNode : public UnOpNode
{
public:
    MinusUnOpNode(std::shared_ptr<ExprNode> expr) : UnOpNode(expr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("-");
    }
};

class IsnullUnOpNode : public UnOpNode
{
public:
    IsnullUnOpNode(std::shared_ptr<ExprNode> expr) : UnOpNode(expr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("isnull");
    }
};

class BinOpNode : public ExprNode
{
public:
    BinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : m_lExpr(lExpr), m_rExpr(rExpr) {}

    std::string serialize() const override;

protected:
    virtual void completeOperator(Serializer &serializer) const = 0;

private:
    std::shared_ptr<ExprNode> m_lExpr;
    std::shared_ptr<ExprNode> m_rExpr;
};

class AddBinOpNode : public BinOpNode
{
public:
    AddBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("+");
    }
};

class MinusBinOpNode : public BinOpNode
{
public:
    MinusBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("-");
    }
};

class MulBinOpNode : public BinOpNode
{
public:
    MulBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("*");
    }
};

class DivBinOpNode : public BinOpNode
{
public:
    DivBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("/");
    }
};

class LowerBinOpNode : public BinOpNode
{
public:
    LowerBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("<");
    }
};

class LowerOrEqualBinOpNode : public BinOpNode
{
public:
    LowerOrEqualBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("<=");
    }
};

class EqualBinOpNode : public BinOpNode
{
public:
    EqualBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("=");
    }
};

class AndBinOpNode : public BinOpNode
{
public:
    AndBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("and");
    }
};

class PowBinOpNode : public BinOpNode
{
public:
    PowBinOpNode(std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("^");
    }
};

class SelfNode : public ExprNode
{
public:
    std::string serialize() const override;
};

class IdentifierNode : public ExprNode
{
public:
    IdentifierNode(std::string name) : m_name(name) {}
    std::string serialize() const override;

private:
    std::string m_name;
};

class UnitNode : public ExprNode
{
public:
    std::string serialize() const override;
};

class CallNode : public ExprNode
{
public:
    CallNode(std::string methodName,
             std::vector<std::shared_ptr<ExprNode>> exprList,
             std::shared_ptr<ExprNode> objExpr = std::make_shared<SelfNode>())
        : m_methodName(methodName), m_exprList(exprList), m_objExpr(objExpr) {}
    std::string serialize() const override;

private:
    std::string m_methodName;
    std::vector<std::shared_ptr<ExprNode>> m_exprList;
    std::shared_ptr<ExprNode> m_objExpr;
};

class BlockNode : public ExprNode
{
public:
    BlockNode(std::vector<std::shared_ptr<ExprNode>> expressions)
        : m_expressions(expressions) {}

    std::string serialize() const override;

private:
    std::vector<std::shared_ptr<ExprNode>> m_expressions;
};

class LiteralNode : public ExprNode
{
public:
    LiteralNode(std::string value) : m_value(value) {}
    std::string serialize() const override;

private:
    std::string m_value;
};

class NewNode : public ExprNode
{
public:
    NewNode(std::string typeName)
        : m_typeName(typeName) {}
    std::string serialize() const override;

private:
    std::string m_typeName;
};