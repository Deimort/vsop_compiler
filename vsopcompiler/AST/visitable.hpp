#pragma once

#include "visitor.hpp"

class Visitor;

class Visitable
{
public:
    virtual void accept(Visitor &visitor) = 0;
    virtual ~Visitable() = default;
};
