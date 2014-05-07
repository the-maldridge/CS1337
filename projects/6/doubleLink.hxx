#ifndef DOUBLE_H
#define DOUBLE_H

#include "singleLink.hxx"
#include "dnode.hxx"

class dlink: private slink {
private:
  dNode* tail;
public:
  dlink();
  void addNode(Node*);
  void delNode(int);
};

#endif
