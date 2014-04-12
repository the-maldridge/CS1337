#include "stack.hxx"
#include <cstddef>

Stack::Stack() {
  head=NULL;
}

void Stack::push(NodeData incoming) {
  Item* oldhead=head;
  Item* temp = new Item(incoming);
  temp->setNext(oldhead);
  head = temp;
}

void Stack::purge() {
  while(head != NULL) {
    Item* next = head->getNext();
    delete head;
    head = next;
  }
}

Item Stack::pop() {
  Item* next = head->getNext();
  NodeData dat = head->retrieveData();
  delete head;
  head = next;
  return dat;
}

Item Stack::peek() {
  return head->retrieveData();
}
