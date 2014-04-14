// infix calculator that first jumps through postfix
#include "eqMan.hxx"
#include <string>
#include <iostream>

int main() {
  std::string foo = "(2+3)*5-4^2+35^(3/3*(4-2*3))";
  Tokenizer test(foo);
  std::cout << "This is the end" << std::endl;
  return 0;
}
