#include "node.hxx"

Node::Node() {
  next = NULL;
}

Node::~Node() {
  //recursively delete by magic of the destructor!
  if(next!=NULL) {
    delete next;
  }
}

void Node::setNext(Node* n) {
  next = n;
}

Node* Node::getNext() {
  return next;
}

void Node::setID(string s) {
  ID = s;
}

std::string Node::getID() {
  return ID;
}

void Node::setDesc(string s) {
  desc = s;
}

std::string Node::getDesc() {
  return desc;
}

void Node::setQuantity(int c) {
  quantity = c;
}

int Node::getQuantity() {
  return quantity;
}

void Node::setRCost(double c) {
  rCost = c;
}

double Node::getRCost() {
  return rCost;
}

void Node::setWCost(double c) {
  wCost = c;
}

double Node::getWCost() {
  return wCost;
};
