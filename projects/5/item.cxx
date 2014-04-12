#include "item.hxx"
#include <cstddef>

Item::Item() {
  next=NULL;
  data.type = OPERAND;
  data.payload.num = 0;
}

Item::Item(NodeData incoming) {
  data = incoming;
}

Item::~Item() {}

NodeData Item::retrieveData() {
  return data;

}

void Item::setNext(Item* nextItem) {
  next = nextItem;
}

Item* Item::getNext() {
  return next;
}
