#ifndef TYPES_H
#define TYPES_H

union Data {double num; char op;};
enum Type {OPERAND, OPERATOR};
struct QType {
  Type type;
  Data dat;
};

#endif
