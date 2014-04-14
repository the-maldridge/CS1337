#ifndef EQMAN_H
#define EQMAN_H

#include <string>
#include <cctype>
#include "stack.hxx"
#include "queue.hxx"

union Data {int num; char op;};
enum Type {OPERAND, OPERATOR};
struct QType {Type type; Data dat;};

class Tokenizer {
private:
  std::string input;
  std::string output;
  Stack opStack;
  int getOpPriority(char);
public:
  Tokenizer(std::string);
  ~Tokenizer();

  Queue<QType> tokenize();
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
