#include "doubleLink.hxx"
#include <cassert>

dlink::dlink() {
  tail = NULL;
  numElements = 0;
}

void dlink::addNode(dNode* n) {
  if(head == NULL) {
    //case where this is the only node
    head = n;
  } else {
    //case where we are adding somewhere after head
    dNode* ptr = static_cast<dNode*>(head);
    while (ptr->getNext() != NULL) {
      if(ptr->getNext()->getID() > n->getID()) {
	n->setNext(ptr->getNext());
	n->setPrev(ptr);
	ptr->setNext(n);
      } else {
	ptr = ptr->getNext();
      }
    }
  } 
  numElements++;
}

void dlink::delNode(int n) {
  dNode* current;

  //find which one is to be deleted
  for(int i=0; i<n; i++) {
    current = current->getNext();
  }

  //relink around current
  static_cast<dNode*>(current->getNext())->setPrev(current->getPrev()); //set prev
  current->getPrev()->setNext(current->getNext()); //set next

  //remove the node we originally wanted to delete
  current->setNext(NULL); //fully unlink to prevent unintentional deletion
  delete current;

  numElements--;
}

dNode& dlink::operator[](int n) {
  dNode* current = head;

  //bounds check or die
  assert(0<=n && n < numElements);

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
    
