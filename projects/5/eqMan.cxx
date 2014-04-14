/*
This file contains the definitions for both the tokenizer
and the evaluator, these two functions make up the RPN calculator
*/

// Begin the Tokenizer!
#include "eqMan.hxx"
#include <cstdlib>

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
  case ')':
    return 0;
  case '\0':
    return -1;
  default:
    //will never get here, but must have to clear warns
    return -2;
  }
}

QType toQ(double n) {
  QType temp;
  temp.type = OPERAND;
  temp.dat.num = n;
  return temp;
}

QType toQ(char c) {
  QType temp;
  temp.type = OPERATOR;
  temp.dat.op = c;
  return temp;
}

QType getToken(const char* str, const char** out) {
  while(*str == ' ') {
    ++str;
  }

  QType item;

  if(isdigit(*str)) {
    int num = 0;
    while(isdigit(*str)) {
      num = num * 10 + *str - '0';
      ++str;
    }
    item = toQ((double)num);
  } else {
    item = toQ(*str);
    str++;
  }

  *out = str;
  return item;
}

Queue<QType> Tokenizer::tokenize() {
  Queue<QType> outQ;
  const char* str = input.c_str(); //for speed

  for(; *str != 0;) {
    QType inQ = getToken(str, &str);

    if(inQ.type == OPERAND) {
      outQ.nq(inQ);
    } else if(inQ.type == OPERATOR) {
      if(inQ.dat.op == '(') {
	opStack.push(inQ);
      } else if(inQ.dat.op == ')') {
	while(opStack.top().dat.op != '(') {
	  outQ.nq(opStack.top());
	  opStack.pop();
	}
	opStack.pop();
      } else {
	while(!opStack.empty() &&
	      getOpPriority(inQ.dat.op) <= getOpPriority(opStack.top().dat.op)) {
	  outQ.nq(opStack.top());
	  opStack.pop();
	}
	opStack.push(inQ);
      }
    } else {
      std::cerr << "INVALID EXPRESSION" << std::endl;
    }
  }
  while(!opStack.empty()) {
    outQ.nq(opStack.top());
    opStack.pop();
  }
  return outQ;
}

Evaluator::Evaluator(Queue<QType> toEval) {
  input = toEval;
}

Evaluator::~Evaluator() {}

double Evaluator::evaluate() {
  Stack<double> evalStack; //shadowing!
  while(!input.isEmpty()) {
    QType temp = input.dq();

    switch(temp.type) {
    case OPERAND:
      evalStack.push(temp.dat.num);
      break;
    case OPERATOR:
      switch(temp.dat.op) {
      case '+': {
	double op1, op2;
	op2 = evalStack.top();
	evalStack.pop();
	op1 = evalStack.top();
	evalStack.pop();
	evalStack.push(op1+op2);
	break;
      }
      case '-': {
	double op1, op2;
	op2 = evalStack.top();
	evalStack.pop();
	op1 = evalStack.top();
	evalStack.pop();
	evalStack.push(op1-op2);
	break;
      }
      case '*': {
	double op1, op2;
	op2 = evalStack.top();
	evalStack.pop();
	op1 = evalStack.top();
	evalStack.pop();
	evalStack.push(op1*op2);
	break;
      }
      case '/': {
	double op1, op2;
	op2 = evalStack.top();
	evalStack.pop();
	op1 = evalStack.top();
	evalStack.pop();
	evalStack.push(op1/op2);
	break;
      }
      case '^': {
	double op1, op2;
	op2 = evalStack.top();
	evalStack.pop();
	op1 = evalStack.top();
	evalStack.pop();
	evalStack.push(pow(op1,op2));
	break;
      }
      default:
	std::cerr << "UNDEFINED OPERATOR EXPANSION" << std::endl;
	break;
      }
      break;
    default:
      std::cerr << "UNDEFINED EXPRESSION EXPANSION" << std::endl;
      break;
    }
  }
  return evalStack.top();
}

