#include <iostream>
#include <cmath>
#include <cfloat>

inline double f(double x) {
  return (x <= 1?1:x*f(x-1));
}

double taylorExpand(double x, int i=0) {
  double current;
  
  current = (pow(-1,i) * pow(x,2*i)) / f(2*i);

  std::cout << current << std::endl;

  if(fabs(current) <= FLT_EPSILON) {
    return current + x;
  } else {
    return current + taylorExpand(x, i+1);
  }
}

int main() {
  int foo;

  std::cout << f(5);
  
  std::cout << "Cos: ";
  std::cin >> foo;

  std::cout << "Result: " << taylorExpand(foo);
  return 0;
}
