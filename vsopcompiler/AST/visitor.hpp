#pragma once

template<typename R>
class Visitor {
public:
  virtual R visit(Num& num) = 0;
  virtual R visit(Add& add) = 0;
  virtual R visit(Sub& sub) = 0;
};