#ifndef EQMAN_H
#define EQMAN_H

#include <string>
#include <cctype>
#include <cmath>
#include "stack.hxx"
#include "queue.hxx"
#include "types.hxx"

class Tokenizer {
private:
  std::string input;
  std::string output;
  Stack<QType> opStack;
  int getOpPriority(char);
public:
  Tokenizer(std::string);
  ~Tokenizer();

  Queue<QType> tokenize();
};

class Evaluator {
private:
  Queue<QType> input;
  Stack<double> evalStack;
  int left, right;
  double out;
public:
  Evaluator(Queue<QType>);
  ~Evaluator();

  double evaluate();
};
#endif
