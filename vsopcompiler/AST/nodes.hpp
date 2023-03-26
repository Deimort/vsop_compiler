#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

class Serializer {
public:
    void setType(const std::string& type);
    void addString(const std::string& str);
    void startList();
    void endList();
    std::string serialize() const;
private:
    bool m_hasType = false;
    bool m_hasPrevious = false;
    bool m_inList = false;
    std::stringstream m_buffer;
};

class Serializable {
public:
    virtual ~Serializable() {}
    virtual std::string serialize() const = 0;
};

class ProgramNode : public Serializable {
public:
    void addClass(std::unique_ptr<ClassNode> classNode) {
        m_classes.push_back(std::move(classNode));
    }

    std::string serialize() const override {
        Serializer serializer;
        serializer.startList();
        for(auto& classNode : m_classes) {
            serializer.addString(classNode->serialize());
        }
        serializer.endList();
        return serializer.serialize();
    }

private:
    std::vector<std::unique_ptr<ClassNode>> m_classes;
};

class ClassNode : public Serializable {
public:
    ClassNode(const std::string& name, const std::string& parent = "Object")
        : m_name(name), m_parent(parent) {}

    void addField(std::unique_ptr<FieldNode> field) {
        m_fields.push_back(std::move(field));
    }

    void addMethod(std::unique_ptr<MethodNode> method) {
        m_methods.push_back(std::move(method));
    }

    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("Class");
        serializer.addString(m_name);
        serializer.addString(m_parent);
        serializer.startList();
        for(auto& fieldNode : m_fields) {
            serializer.addString(fieldNode->serialize());
        }
        serializer.endList();
        serializer.startList();
        for(auto& methodNode : m_methods) {
            serializer.addString(methodNode->serialize());
        }
        serializer.endList();
        return serializer.serialize();
    }

private:
    std::string m_name;
    std::string m_parent;
    std::vector<std::unique_ptr<FieldNode>> m_fields;
    std::vector<std::unique_ptr<MethodNode>> m_methods;
};

class FieldNode: public Serializable {
public:
    FieldNode(const std::string& name, const std::string& type, const std::string& initExpr = "")
        : m_name(name), m_type(type), m_initExpr(initExpr) {}

    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("Field");
        serializer.addString(m_name);
        serializer.addString(m_type);
        serializer.addString(m_initExpr);
        return serializer.serialize();
    }

private:
    std::string m_name;
    std::string m_type;
    std::string m_initExpr;
};

class MethodNode : public Serializable {
public:
    MethodNode(const std::string& name, std::vector<std::unique_ptr<FormalNode>> formals,
               const std::string& retType, std::unique_ptr<BlockNode> block)
        : m_name(name), m_formals(std::move(formals)), m_retType(retType), m_block(std::move(block)) {}

    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("Method");
        serializer.addString(m_name);
        serializer.startList();
        for(auto& formalNode : m_formals) {
            serializer.addString(formalNode->serialize());
        }
        serializer.endList();
        serializer.addString(m_retType);
        serializer.addString(m_block->serialize());
        return serializer.serialize();
    }

private:
    std::string m_name;
    std::vector<std::unique_ptr<FormalNode>> m_formals;
    std::string m_retType;
    std::unique_ptr<BlockNode> m_block;
};

class FormalNode : public Serializable {
public:
    FormalNode(const std::string& name, const std::string& type)
        : m_name(name), m_type(type) {}

    std::string serialize() const override {
        return m_name + " : " + m_type;
    }

private:
    std::string m_name;
    std::string m_type;
};

class ExprNode : public Serializable {
};

class IfNode : public ExprNode {
public:
    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("If");
        serializer.addString(m_condExpr->serialize());
        serializer.addString(m_thenExpr->serialize());
        if(m_elseExpr) {
            serializer.addString(m_elseExpr->serialize());
        }
        return serializer.serialize();
    }

private:
    std::unique_ptr<ExprNode> m_condExpr;
    std::unique_ptr<ExprNode> m_thenExpr;
    std::unique_ptr<ExprNode> m_elseExpr;
};

class WhileNode : public ExprNode {
public:
    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("While");
        serializer.addString(m_condExpr->serialize());
        serializer.addString(m_bodyExpr->serialize());
        return serializer.serialize();
    }

private:
    std::unique_ptr<ExprNode> m_condExpr;
    std::unique_ptr<ExprNode> m_bodyExpr;
};

class LetNode : public ExprNode {
public:
    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("Let");
        serializer.addString(m_name);
        serializer.addString(m_type);
        if(m_initExpr) {
            serializer.addString(m_initExpr->serialize());
        }
        serializer.addString(m_scopedExpr->serialize());
        return serializer.serialize();
    }

private:
    std::string m_name;
    std::string m_type;
    std::unique_ptr<ExprNode> m_initExpr;
    std::unique_ptr<ExprNode> m_scopedExpr;
};

class AssignNode : public ExprNode {
public:
    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("Assign");
        serializer.addString(m_name);
        serializer.addString(m_expr->serialize());
        return serializer.serialize();
    }

private:
    std::string m_name;
    std::unique_ptr<ExprNode> m_expr;
};

class AssignNode : public ExprNode {
public:
    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("Assign");
        serializer.addString(m_name);
        serializer.addString(m_expr->serialize());
        return serializer.serialize();
    }

private:
    std::string m_name;
    std::unique_ptr<ExprNode> m_expr;
};

class UnOpNode : public ExprNode {
public:
    UnOpNode(std::unique_ptr<ExprNode> expr): m_expr(std::move(expr)) {}

    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("UnOp");
        completeOperator(serializer);
        serializer.addString(m_expr->serialize());
        return serializer.serialize();
    }

protected:
    virtual void completeOperator(Serializer& serializer) const = 0;

private:
    std::unique_ptr<ExprNode> m_expr;
};

class NotUnOpNode : public UnOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("not");
    }
};

class MinusUnOpNode : public UnOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("-");
    }
};

class IsnullUnOpNode : public UnOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("not");
    }
};

class BinOpNode : public ExprNode {
public:
    BinOpNode(std::unique_ptr<ExprNode> lExpr, std::unique_ptr<ExprNode> rExpr)
        : m_lExpr(std::move(lExpr)), m_rExpr(std::move(rExpr)) {}

    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("BinOp");
        completeOperator(serializer);
        serializer.addString(m_lExpr->serialize());
        serializer.addString(m_rExpr->serialize());
        return serializer.serialize();
    }

protected:
    virtual void completeOperator(Serializer& serializer) const = 0;

private:
    std::unique_ptr<ExprNode> m_lExpr;
    std::unique_ptr<ExprNode> m_rExpr;
};

class AddBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("+");
    }
};

class MinusBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("-");
    }
};

class MultiplyBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("*");
    }
};

class DevideBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("/");
    }
};

class LessBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("<");
    }
};

class LessOrEqualBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("<=");
    }
};

class EqualBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("=");
    }
};

class AndBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("and");
    }
};

class EqualBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("=");
    }
};

class PowBinOpNode : public BinOpNode {
protected:
    void completeOperator(Serializer& serializer) const override {
        serializer.addString("^");
    }
};

class CallNode : public ExprNode {
public:
    std::string serialize() const override {
        Serializer serializer;
        serializer.setType("Call");
        serializer.addString(m_objExpr->serialize());
        serializer.addString(m_methodName);
        serializer.startList();
        for(auto& expr : m_exprList) {
            serializer.addString(expr->serialize());
        }
        serializer.endList();
        return serializer.serialize();
    }
private:
    std::unique_ptr<ExprNode> m_objExpr;
    std::string m_methodName;
    std::vector<std::unique_ptr<ExprNode>> m_exprList;
};

class BlockNode : public Serializable {
public:
    BlockNode(std::vector<std::unique_ptr<ExprNode>> expressions)
        : m_expressions(std::move(expressions)) {}

    std::string serialize() const override {
        Serializer serializer;
        serializer.startList();
        for(auto& expressionNode : m_expressions) {
            serializer.addString(expressionNode->serialize());
        }
        serializer.endList();
        return serializer.serialize();
    }

private:
    std::vector<std::unique_ptr<ExprNode>> m_expressions;
};