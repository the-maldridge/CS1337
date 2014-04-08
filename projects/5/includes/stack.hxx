#ifndef STACK_H
#define STACK_H

#include "item.hxx"

class Stack {
private:
  Item* head;
public:
  Stack();
  ~Stack();

  void push(nodeData_t);
  void purge();
  Item pop();
  Item peek();
};

#endif
