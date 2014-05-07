#ifndef DOUBLE_H
#define DOUBLE_H

#include "singleLink.hxx"
#include "dnode.hxx"

class dlink: private slist {
private:
  dNode* tail;
  int numElements;
public:
  dlink();

  void addNode(Node*);
  void delNode(int);

  int size();
};
#endif
