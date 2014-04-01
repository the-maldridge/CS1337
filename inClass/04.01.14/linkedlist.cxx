#include <iostream>
#include "linkedlist.h"

LinkList::LinkList() {
  head = NULL;
}

LinkList::~LinkList() {
  Node* ptr=head;

  while(head!=NULL) {
    head = head->getNext();
    delete ptr;
    ptr=head;
  }
}

void LinkList::Add(Node* ptr) {
  if(head==NULL) {
    head = ptr;
  } else {
    Node* search = head;
    if(ptr->getNum1() < head->getNum1()) {
      ptr->setNext(head);
      head = ptr;
      return;
    }
  }
}

