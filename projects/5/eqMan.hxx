//eqMan manages the equations and calculates them

#include "stack.hxx"
#include <string>

class Expression {
private:
  Stack operators, input, output;
public:
  Expression();
  ~Expression();

  void convert(Stack);
  string getExp();
  string getPostFix();
};

class Calculate {
private:
public:
  Calculate();
  ~Calculate();

  int result(Expression);
};
