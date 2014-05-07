#ifndef SLINK_H
#define SLINK_H

#include "node.hxx"

class slist {
protected:
  Node* head;
public:
  slist();
  ~slist();

  virtual void add(Node*);
};


#endif
