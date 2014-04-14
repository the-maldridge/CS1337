#include <cstddef>
#include <iostream>
#include <sstream>
#include "types.hxx"

//the nodes in the queue
#ifndef QNODE_H
#define QNODE_H
template<typename T>
class QNode {
private:
  QNode* next;
  T data;
public:
  QNode(T);
  ~QNode();

  void setNext(QNode*);
  QNode* getNext();
  T getData();
};

template<typename T>
QNode<T>::QNode(T datum) {
  next = NULL;
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

#endif

//the queue
#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue {
private:
  QNode<T>* head;
  QNode<T>* tail;
public:
  Queue();
  ~Queue();

  void nq(T);
  T dq();  
  bool isEmpty();
  std::string printQ();
};

template<typename T>
Queue<T>::Queue() {
  head = NULL;
  tail = NULL;
}

template<typename T>
Queue<T>::~Queue() {}

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
    head = head->getNext();
    T data = oldHead->getData();
    delete oldHead;
    return data;
  } else {
    std::cerr << "TRIED TO GET NULL PTR" << std::endl;
    throw new int(5);
  }
}

template<typename T>
bool Queue<T>::isEmpty() {
  return head==NULL;
}

template<typename T>
std::string Queue<T>::printQ() {
  std::stringstream out;
  QNode<QType>* temp = head;
  
  while(temp != NULL) {
    if(temp->getData().type == OPERATOR) {
      out << temp->getData().dat.op;
      out << ' ';
    } else if(temp->getData().type == OPERAND) {
      out << temp->getData().dat.num;
      out << ' ';
    }
    temp = temp->getNext();
  }
  
  return out.str();
}
#endif
