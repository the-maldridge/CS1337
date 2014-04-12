#ifndef STACK_H
#define STACK_H

#include "item.hxx"

class Stack {
private:
  Item* head;
public:
  Stack();
  ~Stack();

  void push(NodeData);
  void purge();
  Item pop();
  Item peek();
};

#endif
