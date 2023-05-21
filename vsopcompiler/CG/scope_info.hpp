#pragma once

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Type.h"

using namespace llvm;

class ScopeInfo
{
public:
    void setCurrentMethod(BasicBlock *block) { m_currentMethod = block; }
    BasicBlock *getCurrentMethod() { return m_currentMethod; }

    void setCurrentClass(StructType *classType) { m_currentClass = classType; }
    StructType *getCurrentClass() { return m_currentClass; }

private:
    BasicBlock *m_currentMethod;
    StructType *m_currentClass;
};