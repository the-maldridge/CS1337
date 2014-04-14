#include "item.hxx"

Item::Item(char c) {
  data = c;
}

Item::~Item() {}

void Item::setOp(char c) {
  data = c;
}

char Item::getOp() {
  return data;
}

void Item::setNext(Item* p) {
  next = p;
}

Item* Item::getNext() {
  return next;
}
