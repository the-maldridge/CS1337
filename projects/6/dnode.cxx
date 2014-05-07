#include "dnode.hxx"

dNode::dNode() {
  prev = NULL;
}

void dNode::setPrev(dNode* p) {
  prev = p;
}

dNode* dNode::getPrev() {
  if(prev!=NULL) {
    return prev;
  } else {
    throw new int(5); //if we make it this far, we're where the monsters are
  }
}
