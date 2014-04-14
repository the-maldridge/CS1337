
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
};
#endif
