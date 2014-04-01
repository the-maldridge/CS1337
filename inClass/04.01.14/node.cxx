#include "node.h"
#include <cstddef>

Node::Node() {
  num1=0;
  next=NULL;
}

Node::Node(int inum, Node* overthere) {
  num1=inum;
  next=overthere;
}
