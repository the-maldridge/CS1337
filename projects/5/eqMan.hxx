#ifndef EQMAN_H
#define EQMAN_H

#include <string>
#include <cctype>
#include <cmath>
#include "stack.hxx"
#include "queue.hxx"
#include "types.hxx"

//Tokenizer converts to postfix
Queue<QType> tokenize(std::string);

//Evaluator performs calculations on postfix
double evaluate(Queue<QType>);

#endif
