#include "doubleLink.hxx"

dlink::dlink() {
  tail = NULL;
}

void dlink::addNode(dNode* n) {
  if(head == NULL) {
    //case where this is the only node
    head = n;
  } else {
    //case where we are adding somewhere after head
    dNode *ptr = head;
    while (ptr->getNext() != NULL) {
      if ((ptr->getNext())->getID() > n->getID()) {
	n->setNext(ptr->getNext()); //tell n where next is
	n->setPrev(ptr); //tell n where prev is
	ptr->setNext(n); //tell previous where n is
	n->getNext()->setPrev(n); //tell next where n is
	return;
      } else {
	ptr=ptr->getNext();
      }
    }
    ptr->setNext(n);
  } 
  numElements++;
}

void dlink::delNode(int i) {
  dNode* current;

  //find which one is to be deleted
  for(int i=0; i<n; i++) {
    current = current->getNext();
  }

  //relink around current
  current->getNext()->setPrev(current->getPrev()); //set prev
  current->getPrev()->setNext(current->getNext()); //set next

  //remove the node we originally wanted to delete
  current->setNext(NULL); //fully unlink to prevent unintentional deletion
  delete current;

  numElements--;
}

dNode& dlink::operator[](int n) {
  dNode* current;

  //find the node according to the offset
  for(int i=0; i<n; i++) {
    current = current->getNext();
  }

  //return the node object itself
  return *current;
}

int dlink::size() {
  return numElements;
}
