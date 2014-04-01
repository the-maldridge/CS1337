#ifndef LINKLIST_H
#define LINKLIST_H

#include "node.h"

class LinkList {
private:
  Node* head;

public:
  LinkList();
  ~LinkList();
  void Add(Node*);
  void Delete(int);
  void Print() const;
};
#endif
