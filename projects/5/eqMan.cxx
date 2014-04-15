/*
This file contains the definitions for both the tokenizer
and the evaluator, these two functions make up the RPN calculator
*/

// Begin the Tokenizer!
#include "eqMan.hxx"
#include <cstdlib>

int getOpPriority(char op) {
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

//convenience function to build the QType
QType toQ(double n) {
  QType temp;
  temp.type = OPERAND;
  temp.dat.num = n;
  return temp;
}

//convenience function to build the QType
QType toQ(char c) {
  QType temp;
  temp.type = OPERATOR;
  temp.dat.op = c;
  return temp;
}

//convenience function to build the QType
QType getToken(const char* str, const char** out) {
  //eat whitespace
  while(*str == ' ') {
    ++str;
  }

  QType item;

  //if its a digit, make read in all parts of the num
  if(isdigit(*str)) {
    int num = 0;
    while(isdigit(*str)) {
      //shift each digit by 10 as we read more
      num = num * 10 + *str - '0';
      ++str;
    }
    //make double as per assignment
    item = toQ(static_cast<double>(num));
  } else {
    item = toQ(*str);
    str++;
  }

  //reassign pointer from star
  *out = str;
  return item;
}

Queue<QType> tokenize(std::string input) {
  Stack<QType> opStack;
  Queue<QType> outQ;
  const char* str = input.c_str(); //for speed

  //work until we run out of infix
  while(*str != 0) {
    QType inQ = getToken(str, &str);

    if(inQ.type == OPERAND) {
      //if its an operand, then add it to the stack
      outQ.nq(inQ);
    } else if(inQ.type == OPERATOR) {
      //if its an operator check for paren
      if(inQ.dat.op == '(') {
	//if paren, push to stack and descend
	opStack.push(inQ);
      } else if(inQ.dat.op == ')') {
	//if right paren, pop all ops from the stack
	while(opStack.top().dat.op != '(') {
	  outQ.nq(opStack.top());
	  opStack.pop();
	}
	//pop the left paren from the stack
	opStack.pop();
      } else {
	while(!opStack.empty() && getOpPriority(inQ.dat.op) 
	      <= getOpPriority(opStack.top().dat.op)) {
	  //if the precidence is correct, pop it to the queue
	  outQ.nq(opStack.top());
	  opStack.pop();
	}
	//push the original operator into the queue
	opStack.push(inQ);
      }
    } else {
      //if we make it here, the expression isn't mathematically valid
      std::cerr << "INVALID EXPRESSION" << std::endl;
    }
  }

  //pop off all the rest of the ops from before any parens
  //were encountered
  while(!opStack.empty()) {
    outQ.nq(opStack.top());
    opStack.pop();
  }

  //return a queue OBJECT for processing by the evaluator
  return outQ;
}

double evaluate(Queue<QType>& input) {
  Stack<double> evalStack;

  //process while there are things to process
  while(!input.isEmpty()) {
    QType temp = input.dq();

    //unpack based on what the union is
    switch(temp.type) {
    case OPERAND:
      //push the number onto the eval stack
      evalStack.push(temp.dat.num);
      break;
    case OPERATOR:
      //switch based on what the operator was
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
	//this would occur if there is an op that wasn't defined
	std::cerr << "UNDEFINED OPERATOR EXPANSION" << std::endl;
	break;
      }
      break;
    default:
      //this would occur if there was a mathematically invalid statement
      std::cerr << "UNDEFINED EXPRESSION EXPANSION" << std::endl;
      break;
    }
  }

  //return the top of the stack, the calculation result
  return evalStack.top();
}

