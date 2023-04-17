#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "../location.hh"
#include "visitor.hpp"

class Visitable;
class Visitor;

class BaseNode;
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
class NotUnOpNode;
class MinusUnOpNode;
class IsnullUnOpNode;
class BinOpNode;
class AddBinOpNode;
class MinusBinOpNode;
class MulBinOpNode;
class DivBinOpNode;
class LowerBinOpNode;
class LowerOrEqualBinOpNode;
class EqualBinOpNode;
class AndBinOpNode;
class PowBinOpNode;
class SelfNode;
class IdentifierNode;
class UnitNode;
class LiteralNode;

class Visitable
{
public:
    virtual void accept(Visitor &visitor) = 0;
    virtual ~Visitable() = default;
};

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
    virtual ~Serializable() = default;
    virtual std::string serialize() const = 0;
};

class BaseNode : public Visitable, public Serializable
{
public:
    explicit BaseNode(const VSOP::location &loc) : m_loc(loc) {}
    void accept(Visitor &visitor) override { visitor.visit(*this); }

private:
    VSOP::location m_loc;
};

class ProgramNode : public BaseNode
{
public:
    ProgramNode(const VSOP::location &loc, const std::vector<std::shared_ptr<ClassNode>> &classes)
        : BaseNode(loc), m_classes(classes) {}

    std::vector<std::shared_ptr<ClassNode>> getClasses() const { return m_classes; }
    std::string serialize() const override;

private:
    std::vector<std::shared_ptr<ClassNode>> m_classes;
};

class ClassBodyNode : public BaseNode
{
public:
    using BaseNode::BaseNode;
    void addField(std::shared_ptr<FieldNode> field);
    void addMethod(std::shared_ptr<MethodNode> method);
    std::vector<std::shared_ptr<FieldNode>> getFields() const { return m_fields; }
    std::vector<std::shared_ptr<MethodNode>> getMethods() const { return m_methods; }
    std::string serialize() const override;

private:
    std::vector<std::shared_ptr<FieldNode>> m_fields;
    std::vector<std::shared_ptr<MethodNode>> m_methods;
};

class ClassNode : public BaseNode
{
public:
    ClassNode(const VSOP::location &loc, const std::string &name, std::shared_ptr<ClassBodyNode> classBody, const std::string &parent = "Object")
        : BaseNode(loc), m_name(name), m_parent(parent), m_classBody(classBody) {}

    std::string getName() const { return m_name; }
    std::string getParent() const { return m_parent; }
    std::shared_ptr<ClassBodyNode> getBody() const { return m_classBody; }
    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_parent;
    std::shared_ptr<ClassBodyNode> m_classBody;
};

class FieldNode : public BaseNode
{
public:
    FieldNode(const VSOP::location &loc, const std::string &name, const std::string &type, const std::shared_ptr<ExprNode> &initExpr = nullptr)
        : BaseNode(loc), m_name(name), m_type(type), m_initExpr(initExpr) {}
    std::string getName() const { return m_name; }
    std::string getType() const { return m_type; }
    std::shared_ptr<ExprNode> getInitExpr() const { return m_initExpr; }
    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_type;
    std::shared_ptr<ExprNode> m_initExpr;
};

class MethodNode : public BaseNode
{
public:
    MethodNode(const VSOP::location &loc, const std::string &name, const std::vector<std::shared_ptr<FormalNode>> &formals,
               const std::string &retType, std::shared_ptr<BlockNode> block)
        : BaseNode(loc), m_name(name), m_formals(formals), m_retType(retType), m_block(block) {}

    std::string serialize() const override;

private:
    std::string m_name;
    std::vector<std::shared_ptr<FormalNode>> m_formals;
    std::string m_retType;
    std::shared_ptr<BlockNode> m_block;
};

class FormalNode : public BaseNode
{
public:
    FormalNode(const VSOP::location &loc, const std::string &name, const std::string &type)
        : BaseNode(loc), m_name(name), m_type(type) {}

    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_type;
};

class ExprNode : public BaseNode
{
public:
    using BaseNode::BaseNode;
    std::string get_ret_type() const { return m_ret_type; }
    void set_ret_type(const std::string &type) { m_ret_type = type; }

private:
    std::string m_ret_type;
};

class IfNode : public ExprNode
{
public:
    IfNode(const VSOP::location &loc, std::shared_ptr<ExprNode> condExpr, std::shared_ptr<ExprNode> thenExpr, std::shared_ptr<ExprNode> elseExpr = nullptr)
        : ExprNode(loc), m_condExpr(condExpr), m_thenExpr(thenExpr), m_elseExpr(elseExpr) {}
    std::string serialize() const override;

    std::shared_ptr<ExprNode> get_condExpr() const { return m_condExpr; }
    std::shared_ptr<ExprNode> get_thenExpr() const { return m_thenExpr; }
    std::shared_ptr<ExprNode> get_elseExpr() const { return m_elseExpr; }

private:
    std::shared_ptr<ExprNode> m_condExpr;
    std::shared_ptr<ExprNode> m_thenExpr;
    std::shared_ptr<ExprNode> m_elseExpr;
};

class WhileNode : public ExprNode
{
public:
    WhileNode(const VSOP::location &loc, std::shared_ptr<ExprNode> condExpr, std::shared_ptr<ExprNode> bodyExpr)
        : ExprNode(loc), m_condExpr(condExpr), m_bodyExpr(bodyExpr) {}
    std::string serialize() const override;

    std::shared_ptr<ExprNode> get_condExpr() const { return m_condExpr; }
    std::shared_ptr<ExprNode> get_bodyExpr() const { return m_bodyExpr; }

private:
    std::shared_ptr<ExprNode> m_condExpr;
    std::shared_ptr<ExprNode> m_bodyExpr;
};

class LetNode : public ExprNode
{
public:
    LetNode(const VSOP::location &loc, const std::string &name,
            const std::string &type, std::shared_ptr<ExprNode> scopedExpr,
            std::shared_ptr<ExprNode> initExpr = nullptr)
        : ExprNode(loc), m_name(name), m_type(type), m_scopedExpr(scopedExpr), m_initExpr(initExpr) {}
    std::string serialize() const override;

    std::shared_ptr<ExprNode> get_initExpr() const { return m_initExpr; }
    std::string get_type() const { return m_type; }
    std::string get_name() const { return m_name; }

private:
    std::string m_name;
    std::string m_type;
    std::shared_ptr<ExprNode> m_scopedExpr;
    std::shared_ptr<ExprNode> m_initExpr;
};

class AssignNode : public ExprNode
{
public:
    AssignNode(const VSOP::location &loc, const std::string &name, std::shared_ptr<ExprNode> expr)
        : ExprNode(loc), m_name(name), m_expr(expr) {}
    std::string serialize() const override;

private:
    std::string m_name;
    std::shared_ptr<ExprNode> m_expr;
};

class UnOpNode : public ExprNode
{
public:
    UnOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> expr) : ExprNode(loc), m_expr(expr) {}

    std::string serialize() const override;

protected:
    virtual void completeOperator(Serializer &serializer) const = 0;

private:
    std::shared_ptr<ExprNode> m_expr;
};

class NotUnOpNode : public UnOpNode
{
public:
    NotUnOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> expr) : UnOpNode(loc, expr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("not");
    }
};

class MinusUnOpNode : public UnOpNode
{
public:
    MinusUnOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> expr) : UnOpNode(loc, expr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("-");
    }
};

class IsnullUnOpNode : public UnOpNode
{
public:
    IsnullUnOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> expr) : UnOpNode(loc, expr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("isnull");
    }
};

class BinOpNode : public ExprNode
{
public:
    BinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : ExprNode(loc), m_lExpr(lExpr), m_rExpr(rExpr) {}

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
    AddBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("+");
    }
};

class MinusBinOpNode : public BinOpNode
{
public:
    MinusBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("-");
    }
};

class MulBinOpNode : public BinOpNode
{
public:
    MulBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("*");
    }
};

class DivBinOpNode : public BinOpNode
{
public:
    DivBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("/");
    }
};

class LowerBinOpNode : public BinOpNode
{
public:
    LowerBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("<");
    }
};

class LowerOrEqualBinOpNode : public BinOpNode
{
public:
    LowerOrEqualBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("<=");
    }
};

class EqualBinOpNode : public BinOpNode
{
public:
    EqualBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("=");
    }
};

class AndBinOpNode : public BinOpNode
{
public:
    AndBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("and");
    }
};

class PowBinOpNode : public BinOpNode
{
public:
    PowBinOpNode(const VSOP::location &loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(loc, lExpr, rExpr) {}

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("^");
    }
};

class SelfNode : public ExprNode
{
public:
    using ExprNode::ExprNode;
    std::string serialize() const override;
};

class IdentifierNode : public ExprNode
{
public:
    IdentifierNode(const VSOP::location &loc, const std::string &name) : ExprNode(loc), m_name(name) {}
    std::string serialize() const override;

private:
    std::string m_name;
};

class UnitNode : public ExprNode
{
public:
    using ExprNode::ExprNode;
    std::string serialize() const override;
};

class CallNode : public ExprNode
{
public:
    CallNode(const VSOP::location &loc, const std::string &methodName,
             const std::vector<std::shared_ptr<ExprNode>> &exprList,
             std::shared_ptr<ExprNode> objExpr = nullptr)
        : ExprNode(loc), m_methodName(methodName), m_exprList(exprList)
    {
        if (objExpr)
            m_objExpr = objExpr;
        else
            m_objExpr = std::make_shared<SelfNode>(loc);
    }
    std::string serialize() const override;

private:
    std::string m_methodName;
    std::vector<std::shared_ptr<ExprNode>> m_exprList;
    std::shared_ptr<ExprNode> m_objExpr;
};

class BlockNode : public ExprNode
{
public:
    BlockNode(const VSOP::location &loc, const std::vector<std::shared_ptr<ExprNode>> &expressions)
        : ExprNode(loc), m_expressions(expressions) {}

    std::string serialize() const override;

private:
    std::vector<std::shared_ptr<ExprNode>> m_expressions;
};

class LiteralNode : public ExprNode
{
public:
    LiteralNode(const VSOP::location &loc, const std::string &value, const std::string &type)
        : ExprNode(loc), m_value(value), m_type(type) {}
    std::string serialize() const override;
    std::string get_type() const { return m_type; }
    std::string get_value() const { return m_value; }

private:
    std::string m_value;
    std::string m_type;
};

class NewNode : public ExprNode
{
public:
    NewNode(const VSOP::location &loc, const std::string &typeName)
        : ExprNode(loc), m_typeName(typeName) {}
    std::string serialize() const override;

private:
    std::string m_typeName;
};