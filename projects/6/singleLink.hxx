#ifndef SLINK_H
#define SLINK_H

#include "node.hxx"

class slist {
private:
  Node* head;
public:
  slist();
  ~slist();

  virtual void add(Node*);
  virtual void purge();
};


#endif
