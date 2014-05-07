#include "singleLink.hxx"

slist::slist() {
  head = NULL;
}

slist::~slist() {
  if(head!=NULL) {
    delete head;
  }
}

void slist::add(Node* n) {
  
  if(head == NULL) {
    head = n;
  } else {
    Node *ptr = head;
    while (ptr->getNext() != NULL) {
	if ((ptr->getNext())->getID() > n->getID()) {
	    n->setNext(ptr->getNext());
	    ptr->setNext(n);
	    return;
	} else {
	  ptr=ptr->getNext();
	}      
    }
    ptr->setNext(n);
  }
}
