//backing item node class for the stack

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <cstddef>

class Item {
private:
  Item* next;
  char data;
public:
  Item(char);
  ~Item();

  void setOp(char);
  char getOp();
  void setNext(Item*);
  Item* getNext();
};
#endif
