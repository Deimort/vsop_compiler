#pragma once

class Expr {
public:
    virtual ~Expr() {}
    virtual <typename R> R accept(Visitor<R>& v) = 0;
};