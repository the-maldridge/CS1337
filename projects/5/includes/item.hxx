#ifndef ITEM_H
#define ITEM_H

enum operators_t {ADD, SUB, MUL, DIV, EXP};
enum type_t {OPERATOR, OPERAND};
union payload_t {int num; operators_t ops;};
struct nodeData_t {type_t type; payload_t payload;};

class Item {
private:
  Item* next;
  nodeData_t data;
public:
  Item();
  Item(nodeData_t);
  ~Item();
  nodeData_t retrieveData();
  void setNext(Item*);
  Item* getNext();
};

#endif
