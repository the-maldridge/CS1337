#include "stack.hxx"

Stack::Stack() {}
Stack::~Stack() {}

void Stack::push(char val) {
  Item* oldhead = head;
  Item temp(val);

  temp.setNext(oldhead);
  head = &temp;

}

void Stack::pop() {
  Item* toDelete = head;
  head = head->getNext();
  delete toDelete;
}

char Stack::top() {
  return head->getOp();
}

void Stack::purge() {
  Item* delNext;
  while(head->getNext() != NULL) {
    delNext = head->getNext();
    delete head;
    head = delNext;
  }
}
