/*
This file contains the definitions for both the tokenizer
and the evaluator, these two functions make up the RPN calculator
*/

// Begin the Tokenizer!
#include "eqMan.hxx"
#include <iostream>

Tokenizer::Tokenizer(std::string in) {
  input = in;
}

Tokenizer::~Tokenizer() {}

int Tokenizer::getOpPriority(char op) {
  // Compute the precidence of the operator
  switch(op) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  case '^':
    return 3;
  case '(':
    return 4;
  case '\0':
    return -1;
  default:
    //will never get here, but must have to clear warns
    return -2;
  }
}

std::string Tokenizer::tokenize() {
  char inQ, lastQ;

  for(int i=0; input.c_str()[i] != 0; i++) {
    lastQ = inQ;
    inQ = input.c_str()[i];
    if(isdigit(inQ)) {
      // If the character was a digit, append it
      output += input.c_str()[i];
    } else if(inQ != ')') {
      if(inQ != '(') {
	output += " ";
      }

      //its not a ) so it must be an op
      //pop until lower precidence is encountered
      while(getOpPriority(opStack.top()) > getOpPriority(inQ)) {
	if(opStack.top() == '(') {
	  break;
	}
	output += opStack.top();
	output += " ";
	opStack.pop();
      }
      opStack.push(inQ);
    } else if(inQ == ')') {
      if(isdigit(lastQ)) {
	output += " ";
      }
      while(opStack.top()) {
	// Pop until we hit a left paren
	if(opStack.top() != '(') {
	  output += opStack.top();
	  output += " ";
	  opStack.pop();
	} else {
	  opStack.pop();
	  break;
	}
      }
    }
  }
  if(!isdigit(lastQ)) {
    output += " ";
  }
  while(opStack.top()) {
    output += opStack.top();
    output += " ";
    opStack.pop();
  }
  return output;
}

