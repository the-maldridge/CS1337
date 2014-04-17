//backing item node class for the stack

#ifndef ITEM_H
#define ITEM_H
#include <cstddef>

template<typename T>
class Item {
private:
  Item<T>* next;
  T data;
public:
  Item(T);
  ~Item();

  void setOp(T);
  T getOp();
  void setNext(Item<T>*);
  Item<T>* getNext();
};

template<typename T>
Item<T>::Item(T c) {
  data = c;
  next = NULL;
}

template<typename T>
Item<T>::~Item() {}

template<typename T>
void Item<T>::setOp(T c) {
  data = c;
}

template<typename T>
T Item<T>::getOp() {
  return data;
}

template<typename T>
void Item<T>::setNext(Item<T>* p) {
  next = p;
}

template<typename T>
Item<T>* Item<T>::getNext() {
  return next;
}
#endif
