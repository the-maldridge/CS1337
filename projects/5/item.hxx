#ifndef ITEM_H
#define ITEM_H

enum Operator {ADD, SUB, MUL, DIV, EXP, LPAREN, RPAREN};
enum Type {OPERATOR, OPERAND};
union Payload {int num; Operator op;};
struct NodeData {Type type; Payload payload;};

class Item {
private:
  Item* next;
  NodeData data;
public:
  Item();
  Item(NodeData);
  ~Item();
  NodeData retrieveData();
  void setNext(Item*);
  Item* getNext();
};

#endif
