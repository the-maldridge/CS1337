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

std::ostream& operator<<(std::ostream& os, const dNode& n) {
  os << n.ID << std::endl;
  os << n.desc << std::endl;
  os << n.quantity << std::endl;
  os << n.wCost << std::endl;
  os << n.rCost << std::endl;
  os << std::endl;
  return os;
}
