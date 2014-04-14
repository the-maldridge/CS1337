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

  std::cout << (int)'+' << ' ' << (int)'-' << ' ' <<
    (int)'*' << ' ' << (int)'/' << ' ' << (int)'^' << std::endl;

  for(; *str != 0;) {
    std::cout << str << std::endl;
    QType inQ = getToken(str, &str);
    std::cout << "!!!" << inQ.type << std::endl;

    if(inQ.type == OPERAND) {
      std::cout << "push'd" << std::endl;
      outQ.nq(inQ);
    } else if(inQ.type == OPERATOR) {
      if(inQ.dat.op == '(') {
	opStack.push(inQ);
      } else if(inQ.dat.op == ')') {
	while(opStack.top().dat.op != '(') {
	  std::cout << "loop" << opStack.top().dat.op << std::endl;
	  outQ.nq(opStack.top());
	  std::cout << "nq'd " << opStack.top().type << std::endl;
	  opStack.pop();
	  std::cout << "???" << std::endl;
	}
	std::cout << "oh hey; you made it " << opStack.top().dat.op << std::endl;
	opStack.pop();
      } else {
	std::cout << "in the probable place" << std::endl;
	while(!opStack.empty() &&
	      getOpPriority(inQ.dat.op) <= getOpPriority(opStack.top().dat.op)) {
	  outQ.nq(opStack.top());
	  std::cout << "###nq'd" << opStack.top().type << std::endl;
	  opStack.pop();
	}
	opStack.push(inQ);
	std::cout << "out the probable place" << std::endl;
      }
    } else {
      std::cout << "damnit michael version 2" << std::endl;
    }
  }
  while(!opStack.empty()) {
    outQ.nq(opStack.top());
    std::cout << "###nq'd" << opStack.top().type << std::endl;
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
    std::cout << "beep" << std::endl;
    QType temp = input.dq();
    std::cout << "TYPE " << temp.type << std::endl;

    switch(temp.type) {
    case OPERAND:
      std::cout << "OPERAND " << temp.dat.num << std::endl;
      evalStack.push(temp.dat.num);
      break;
    case OPERATOR:
      std::cout << "OPERATOR " << temp.dat.op << std::endl;
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
	std::cerr << "YOU HAVE DONE SOMETHING HORRIBLY WRONG" << std::endl;
	break;
      }
      break;
    default:
      std::cerr << "damnit michael" << std::endl;
      break;
    }
  }

  std::cout << evalStack.top() << std::endl;
  return evalStack.top();
}

