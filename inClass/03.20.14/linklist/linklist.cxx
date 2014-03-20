#include "linklist.h"

Node::Node() {
  num1=0;
  num2=0.0;
  next=NULL;
}

Node::Node(int a, float b=0.0) {
  num1=a;
  num2=b;
}
