#pragma once

#include "nodes.hpp"

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

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(BaseNode &expr){/* No default behaviour here */};
    virtual void visit(ProgramNode &expr) = 0;

    // Expressions
    virtual void visit(IfNode &expr) = 0;
    virtual void visit(WhileNode &expr) = 0;
    virtual void visit(LetNode &expr) = 0;
    virtual void visit(AssignNode &expr) = 0;
    virtual void visit(UnOpNode &expr) = 0;
    virtual void visit(NotUnOpNode &expr) = 0;
    virtual void visit(MinusUnOpNode &expr) = 0;
    virtual void visit(IsnullUnOpNode &expr) = 0;
    virtual void visit(BinOpNode &expr) = 0;
    virtual void visit(AddBinOpNode &expr) = 0;
    virtual void visit(MinusBinOpNode &expr) = 0;
    virtual void visit(MulBinOpNode &expr) = 0;
    virtual void visit(DivBinOpNode &expr) = 0;
    virtual void visit(LowerBinOpNode &expr) = 0;
    virtual void visit(LowerOrEqualBinOpNode &expr) = 0;
    virtual void visit(EqualBinOpNode &expr) = 0;
    virtual void visit(AndBinOpNode &expr) = 0;
    virtual void visit(PowBinOpNode &expr) = 0;
    virtual void visit(SelfNode &expr) = 0;
    virtual void visit(IdentifierNode &expr) = 0;
    virtual void visit(UnitNode &expr) = 0;
    virtual void visit(CallNode &expr) = 0;
    virtual void visit(BlockNode &expr) = 0;
    virtual void visit(LiteralNode &expr) = 0;
    virtual void visit(NewNode &expr) = 0;
};