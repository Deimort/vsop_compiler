#pragma once

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"

#include "AST/visitor.hpp"
#include "AST/nodes.hpp"

#include "scope_info.hpp"

using namespace llvm;

class CodeGeneratorVisitor : public Visitor 
{
public:
    explicit CodeGeneratorVisitor(const ProgramNode &ast) : m_ast(ast), m_scopeInfo(std::make_unique<ScopeInfo>()) {
        m_context = std::make_unique<LLVMContext>();
        m_module = std::make_unique<Module>("vsop", m_context.get());
        m_builder = std::make_unique<IRBuilder<>>(m_context.get());

    }

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
    static *Type getLLVMType(const std::string &type) const;

    const ProgramNode &m_ast;
    std::unique_ptr<LLVMContext> m_context;
    std::unique_ptr<Module> m_module;
    std::unique_ptr<IRBuilder> m_builder;

    std::unique_ptr<ScopeInfo> m_scopeInfo;
    llvm::Value* m_returnValue;

    int m_pass_count = 0;
};