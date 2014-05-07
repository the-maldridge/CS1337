#ifndef NODE_H
#define NODE_H
#include <cstddef>
#include <string>

class Node {
private:
  std::string ID;
  std::string desc;
  int quantity;
  double wCost;
  double rCost;

  Node* next;
public:
  Node();
  ~Node();

  void setNext(Node*);
  Node* getNext();

  void setID(std::string);
  std::string getID();

  void setDesc(std::string);
  std::string getDesc();

  void setQuantity(int);
  int getQuantity();
 
  void setRCost(double);
  double getRCost();

  void setWCost(double);
  double getWCost();
};

#endif
