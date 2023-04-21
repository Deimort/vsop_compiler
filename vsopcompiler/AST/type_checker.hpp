#pragma once

#include <vector>

#include "visitor.hpp"
#include "nodes.hpp"
#include "symbol_table.hpp"
#include "semantic_exception.hpp"

class Visitor;

class TypeCheckerVisitor : public Visitor
{
public:
    explicit TypeCheckerVisitor(const ProgramNode &ast) : m_ast(ast) {}

    void visit(BaseNode &expr) override;
    void visit(ProgramNode &expr) override;
    void visit(ClassNode &expr) override;
    void visit(ClassBodyNode &expr) override;
    void visit(FieldNode &expr) override;
    void visit(MethodNode &expr) override;
    void visit(FormalNode &expr) override;

    // Expressions
    void visit(IfNode &expr) override;
    void visit(WhileNode &expr) override;
    void visit(LetNode &expr) override;
    void visit(AssignNode &expr) override;
    void visit(UnOpNode &expr) override;
    void visit(NotUnOpNode &exp) override;
    void visit(MinusUnOpNode &expr) override;
    void visit(IsnullUnOpNode &expr) override;
    void visit(BinOpNode &expr) override;
    void visit(AddBinOpNode &expr) override;
    void visit(MinusBinOpNode &expr) override;
    void visit(MulBinOpNode &expr) override;
    void visit(DivBinOpNode &expr) override;
    void visit(LowerBinOpNode &expr) override;
    void visit(LowerOrEqualBinOpNode &expr) override;
    void visit(EqualBinOpNode &expr) override;
    void visit(AndBinOpNode &expr) override;
    void visit(PowBinOpNode &expr) override;
    void visit(SelfNode &expr) override;
    void visit(IdentifierNode &expr) override;
    void visit(UnitNode &expr) override;
    void visit(CallNode &expr) override;
    void visit(BlockNode &expr) override;
    void visit(LiteralNode &expr) override;
    void visit(NewNode &expr) override;

private:
    bool isPrimitive(const std::string &type) const;
    bool isClass(const std::string &type) const;
    std::string parentTypeOf(const std::string &type) const;
    std::string checkCycle(const std::string &type) const;
    std::vector<std::string> ancestorsOf(const std::string &type) const;
    std::string commonAncestor(const std::string &typeA, const std::string &typeB) const;
    bool conformsTo(const std::string &typeA, const std::string &typeB) const;
    bool isValidType(const std::string &type) const;

    std::vector<std::string> m_primitive_types = {"unit", "bool", "int32", "string"};
    const ProgramNode m_ast;
    SymbolTable<std::string> m_vTable;
    SymbolTable<FunctionType> m_fTable;
};