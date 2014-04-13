#ifndef EQMAN_H
#define EQMAN_H

#include <string>
#include <cctype>
#include "stack.hxx"

class Tokenizer {
private:
  std::string input;
  std::string output;
  Stack opStack;
  int getOpPriority(char);
public:
  Tokenizer(std::string);
  ~Tokenizer();

  std::string tokenize();
};

class Evaluator {
private:
  std::string input;
  Stack evalStack;
  int left, right;
  float out;
public:
  Evaluator();
  ~Evaluator();

  float evaluate();
};
#endif
