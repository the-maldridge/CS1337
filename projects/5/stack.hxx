//generic stack type for rpn calculations

#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include "item.hxx"

template<typename T>
class Stack {
private:
  Item<T>* head;
  void purge();
public:
  Stack();
  ~Stack();

  void push(T);
  void pop();
  T top();
  bool empty();
};

template<typename T>
Stack<T>::Stack() {
  head = NULL;
}

template<typename T>
Stack<T>::~Stack() {
  //purge();
}

template<typename T>
void Stack<T>::push(T val) {
  Item<T>* oldhead = head;
  Item<T>* temp = new Item<T>(val);

  temp->setNext(oldhead);
  head = temp;
}

template<typename T>
void Stack<T>::pop() {
  Item<T>* toDelete = head;
  head = head->getNext();
  delete toDelete;
}

template<typename T>
T Stack<T>::top() {
  if(head != NULL) {
    return head->getOp();
  } else {
    //return the null char
    throw new int(5);
  }
}

template<typename T>
void Stack<T>::purge() {
  Item<T>* delNext;
  while(head != NULL) {
    delNext = head->getNext();
    delete head;
    head = delNext;
  }
}

template<typename T>
bool Stack<T>::empty() {
  return head == NULL;
}

#endif
