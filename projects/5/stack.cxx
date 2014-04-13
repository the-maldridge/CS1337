#include "stack.hxx"

Stack::Stack() {
  head = NULL;
}

Stack::~Stack() {
  purge();
}

void Stack::push(char val) {
  Item* oldhead = head;
  Item* temp = new Item(val);

  temp->setNext(oldhead);
  head = temp;
}

void Stack::pop() {
  Item* toDelete = head;
  head = head->getNext();
  delete toDelete;
}

char Stack::top() {
  if(head != NULL) {
    return head->getOp();
  } else {
    //return the null char
    return 0;
  }
}

void Stack::purge() {
  Item* delNext;
  while(head != NULL) {
    delNext = head->getNext();
    delete head;
    head = delNext;
  }
}
