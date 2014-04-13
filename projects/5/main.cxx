// infix calculator that first jumps through postfix
#include "eqMan.hxx"
#include <string>
#include <iostream>

int main() {
  std::string foo = "4+5*9-25*(32^2)";
  Tokenizer test(foo);
  std::cout << test.tokenize() << std::endl;
  std::cout << "This is the end" << std::endl;
  return 0;
}
