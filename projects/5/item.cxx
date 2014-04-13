#include "item.hxx"

Item::Item(char val) {
  next=NULL;
  data=val;
}

Item::~Item() {}

void Item::setOp(char input) {
  data = input;
}

char Item::getOp() {
  return data;
}

void Item::setNext(Item* nextItem) {
  next = nextItem;
}

Item* Item::getNext() {
  return next;
}
