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

  void addNode(dNode*);
  void delNode(int);

  int size();
  dNode& operator[](int);
};
#endif
