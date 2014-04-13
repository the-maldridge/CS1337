//generic stack type for rpn calculations

#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include "item.hxx"

class Stack {
private:
  Item* head;
  void purge();
public:
  Stack();
  ~Stack();

  void push(char);
  void pop();
  char top();
};
#endif
