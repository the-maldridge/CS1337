//generic stack type for rpn calculations

#include "item.hxx"

class Stack {
private:
  Item* head;
public:
  Stack();
  ~Stack();

  void push(char);
  void pop();
  char top();
  void purge();
};
