// infix calculator that first jumps through postfix
#include "eqMan.hxx"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main() {
  //bind to the input file
  std::ifstream file("exp.txt");
  if(!file) {
    std::cerr << "File failed to link!" << std::endl;
    return 1;
  }

  //read in all the expressions to a vector
  std::vector<std::string> inputExpressions;
  while(file.good() && !file.eof()) {
    std::string temp;
    getline(file, temp);
    if(temp.size()>0) {
      inputExpressions.push_back(temp);
    }
  }

  //evaluate the expressions
  for(int i = 0; i<static_cast<int>(inputExpressions.size()); i++) {
    Queue<QType> funcQ = tokenize(inputExpressions[i]);
    std:: cout << funcQ.printQ() << '\t';
    std::cout << evaluate(funcQ) << std::endl;
  }
  std::cout << "Calculation Successful!" << std::endl;
  return 0;
}
