#ifndef DNODE_H
#define DNODE_H
#include "node.hxx"

class dNode: public Node {
private:
  dNode* prev;
public:
  dNode();
  void setPrev(dNode*);
  dNode* getPrev();
  friend std::ostream& operator<<(std::ostream& os, const dNode& n);
};

#endif
