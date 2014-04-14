#include <cstddef>
#include "queue.hxx"

#include <iostream>

template<typename T>
Queue<T>::Queue() {
  head = NULL;
}

template<typename T>
Queue<T>::~Queue() {
  QNode<T>* delNext;
  while(head != NULL) {
    delNext = head->getNext();
    delete head;
    head = delNext;
  }
}

template<typename T>
void Queue<T>::nq(T toQ) {
  QNode<T>* newTail = new QNode<T>(toQ);

  if(head == NULL) {
    head = tail = newTail;
  } else {
    tail->setNext(newTail);
    tail = newTail;
  }
}

template<typename T>
T Queue<T>::dq() {
  QNode<T>* oldHead = head;
  
  if(head != NULL) {
    if(head == tail) {
      tail = tail->getNext();
    }
    head = head->getNext();
    return oldHead->getData();
  } else {
    std::cerr << "TRIED TO GET NULL PTR" << std::endl;
    throw new int(5);
  }
}

template<typename T>
QNode<T>::QNode(T datum) {
  data = datum;
}

template<typename T>
QNode<T>::~QNode() {}

template<typename T>
void QNode<T>::setNext(QNode* newNext) {
  next = newNext;
}

template<typename T>
QNode<T>* QNode<T>::getNext() {
  return next;
}

template<typename T>
T QNode<T>::getData() {
  return data;
}
  
