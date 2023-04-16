#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "../location.hh"
#include "visitor.hpp"

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
    Serializable(const int mode = 0, location loc) : m_mode(mode), m_loc(loc) {}
    virtual ~Serializable() {}
    virtual std::string serialize() const = 0;
private:
    int m_mode;
    location m_loc;
};

class ProgramNode : public Serializable
{
public:
    ProgramNode(int mode, location loc, std::vector<std::shared_ptr<ClassNode>> classes)
        : Serializable(mode, loc), m_classes(classes) {}

    std::vector<std::shared_ptr<ClassNode>> getClasses() const { return m_classes; }
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
    ClassNode(const int mode, location loc, const std::string &name, std::shared_ptr<ClassBodyNode> classBody, const std::string &parent = "Object")
        : Serializable(mode, loc), m_name(name), m_parent(parent), m_classBody(classBody) {}

    std::string getName() const { return m_name; }
    std::string getParent() const { return m_parent; }
    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_parent;
    std::shared_ptr<ClassBodyNode> m_classBody;
};

class FieldNode : public Serializable
{
public:
    FieldNode(const int mode, location loc, const std::string &name, const std::string &type, const std::shared_ptr<ExprNode> &initExpr = nullptr)
        : Serializable(mode, loc), m_name(name), m_type(type), m_initExpr(initExpr) {}

    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_type;
    std::shared_ptr<ExprNode> m_initExpr;
};

class MethodNode : public Serializable
{
public:
    MethodNode(const int mode, location loc, const std::string &name, std::vector<std::shared_ptr<FormalNode>> formals,
               const std::string &retType, std::shared_ptr<BlockNode> block)
        : Serializable(mode, loc), m_name(name), m_formals(formals), m_retType(retType), m_block(block) {}

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
    FormalNode(const int mode, location loc, const std::string &name, const std::string &type)
        : Serializable(mode, loc), m_name(name), m_type(type) {}

    std::string serialize() const override;

private:
    std::string m_name;
    std::string m_type;
};

class ExprNode : public Serializable, public Visitable
{
public:
    ExprNode(const int mode, location loc) : Serializable(mode, loc) {}
    const std::string get_ret_type() const { return m_ret_type; }
    void set_ret_type(const std::string &type) { m_ret_type = type; }
    virtual void accept(Visitor& visitor);

private:
    std::string m_ret_type;
};

class IfNode : public ExprNode
{
public:
    IfNode(const int mode, location loc, std::shared_ptr<ExprNode> condExpr, std::shared_ptr<ExprNode> thenExpr, std::shared_ptr<ExprNode> elseExpr = nullptr)
        : ExprNode(mode, loc), m_condExpr(condExpr), m_thenExpr(thenExpr), m_elseExpr(elseExpr) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }
    
    std::shared_ptr<ExprNode> get_condExpr() { return m_condExpr; }
    std::shared_ptr<ExprNode> get_thenExpr() { return m_thenExpr; }
    std::shared_ptr<ExprNode> get_elseExpr() { return m_elseExpr; }

private:
    std::shared_ptr<ExprNode> m_condExpr;
    std::shared_ptr<ExprNode> m_thenExpr;
    std::shared_ptr<ExprNode> m_elseExpr;
};

class WhileNode : public ExprNode
{
public:
    WhileNode(const int mode, location loc, std::shared_ptr<ExprNode> condExpr, std::shared_ptr<ExprNode> bodyExpr)
        : ExprNode(mode, loc), m_condExpr(condExpr), m_bodyExpr(bodyExpr) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }

    std::shared_ptr<ExprNode> get_condExpr() { return m_condExpr; }
    std::shared_ptr<ExprNode> get_bodyExpr() { return m_bodyExpr; }

private:
    std::shared_ptr<ExprNode> m_condExpr;
    std::shared_ptr<ExprNode> m_bodyExpr;
};

class LetNode : public ExprNode
{
public:
    LetNode(const int mode, location loc, const std::string &name,
            const std::string &type, std::shared_ptr<ExprNode> scopedExpr,
            std::shared_ptr<ExprNode> initExpr = nullptr)
        : ExprNode(mode, loc), m_name(name), m_type(type), m_scopedExpr(scopedExpr), m_initExpr(initExpr) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }

    std::shared_ptr<ExprNode> get_scopedExpr() const { return m_scopedExpr; }
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
    AssignNode(const int mode, location loc, const std::string &name, std::shared_ptr<ExprNode> expr)
        : ExprNode(mode, loc), m_name(name), m_expr(expr) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }

private:
    std::string m_name;
    std::shared_ptr<ExprNode> m_expr;
};

class UnOpNode : public ExprNode
{
public:
    UnOpNode(const int mode, location loc, std::shared_ptr<ExprNode> expr) : ExprNode(mode, loc), m_expr(expr) {}

    std::string serialize() const override;

protected:
    virtual void completeOperator(Serializer &serializer) const = 0;

private:
    std::shared_ptr<ExprNode> m_expr;
};

class NotUnOpNode : public UnOpNode
{
public:
    NotUnOpNode(const int mode, location loc, std::shared_ptr<ExprNode> expr) : UnOpNode(mode, loc, expr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("not");
    }
};

class MinusUnOpNode : public UnOpNode
{
public:
    MinusUnOpNode(const int mode, location loc, std::shared_ptr<ExprNode> expr) : UnOpNode(mode, loc, expr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("-");
    }
};

class IsnullUnOpNode : public UnOpNode
{
public:
    IsnullUnOpNode(const int mode, location loc, std::shared_ptr<ExprNode> expr) : UnOpNode(mode, loc, expr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("isnull");
    }
};

class BinOpNode : public ExprNode
{
public:
    BinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : ExprNode(mode, loc), m_lExpr(lExpr), m_rExpr(rExpr) {}

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
    AddBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, loc, lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("+");
    }
};

class MinusBinOpNode : public BinOpNode
{
public:
    MinusBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, loc, lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("-");
    }
};

class MulBinOpNode : public BinOpNode
{
public:
    MulBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, loc, lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("*");
    }
};

class DivBinOpNode : public BinOpNode
{
public:
    DivBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, loc, lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("/");
    }
};

class LowerBinOpNode : public BinOpNode
{
public:
    LowerBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, lo lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("<");
    }
};

class LowerOrEqualBinOpNode : public BinOpNode
{
public:
    LowerOrEqualBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, loc, lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("<=");
    }
};

class EqualBinOpNode : public BinOpNode
{
public:
    EqualBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, loc, lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("=");
    }
};

class AndBinOpNode : public BinOpNode
{
public:
    AndBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, loc, lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("and");
    }
};

class PowBinOpNode : public BinOpNode
{
public:
    PowBinOpNode(const int mode, location loc, std::shared_ptr<ExprNode> lExpr, std::shared_ptr<ExprNode> rExpr)
        : BinOpNode(mode, loc, lExpr, rExpr) {}
    void accept(Visitor& visitor) override { visitor.visit(*this); }

protected:
    void completeOperator(Serializer &serializer) const override
    {
        serializer.addString("^");
    }
};

class SelfNode : public ExprNode
{
public:
    SelfNode(const int mode, location loc) : ExprNode(mode, loc) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }
};

class IdentifierNode : public ExprNode
{
public:
    IdentifierNode(const int mode, location loc, std::string name) : ExprNode(mode, loc), m_name(name) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }

private:
    std::string m_name;
};

class UnitNode : public ExprNode
{
public:
    UnitNode(const int mode, location loc) : ExprNode(mode, loc) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }
};

class CallNode : public ExprNode
{
public:
    CallNode(const int mode, location loc, std::string methodName,
             std::vector<std::shared_ptr<ExprNode>> exprList,
             std::shared_ptr<ExprNode> objExpr = std::make_shared<SelfNode>())
        : ExprNode(mode, loc), m_methodName(methodName), m_exprList(exprList), m_objExpr(objExpr) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }

private:
    std::string m_methodName;
    std::vector<std::shared_ptr<ExprNode>> m_exprList;
    std::shared_ptr<ExprNode> m_objExpr;
};

class BlockNode : public ExprNode
{
public:
    BlockNode(const int mode, location loc, std::vector<std::shared_ptr<ExprNode>> expressions)
        : ExprNode(mode, loc), m_expressions(expressions) {}

    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }

private:
    std::vector<std::shared_ptr<ExprNode>> m_expressions;
};

class LiteralNode : public ExprNode
{
public:
    LiteralNode(const int mode, location loc, std::string value, std::string type) 
        : ExprNode(mode, loc), m_value(value), m_type(type) {}
    std::string serialize() const override;
    void accept(Visitor& visitor) override { visitor.visit(*this); }
    std::string get_type() { return m_type; }
    std::string get_value() { return m_value; }
private:
    std::string m_value;
    std::string m_type;
};

class NewNode : public ExprNode
{
public:
    NewNode(const int mode, location loc, std::string typeName)
        : ExprNode(mode, loc), m_typeName(typeName) {}
    std::string serialize() const override;

private:
    std::string m_typeName;
};