#ifndef LINKLIST
#define LINKLIST

class Node {
 private:
  int num1;
  float num2;
  Node* next;


 public:
  Node();
  Node(int, float) {}

  ~Node() {}

  int getNum1() { return num1; }
  float getNum2() { return num2; }

  void setNum1(int a) { num1=a; }
  void setNum2(float a) { num2=a; }
};

class LinkList {
 private:
  Node* head;

 public:
  void add(Node*);
  void delete(int);
  void debug();
};
#endif
