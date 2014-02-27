#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
using namespace std;

double float_validate() {
  string line;
  bool foundPoint, foundDigit;

  cout << "Enter a valid floating point number: " << endl;
  cin >> line;
  
  const char* flt = line.c_str();

  for(int i=0; i<strlen(flt); i++) {
    if(flt[i]=='.') {
      if(foundPoint) {
	cout << "You only get one point!" << endl;
	return 0;
      } else {
	foundPoint = true;
      }
    } else {
      if(!isdigit(flt[i])) {
	cout << "Floating point means numbers and points, LEARN!" << endl;
	return 0;
      } else {
	foundDigit = true;
      }
    }
  }

  return atof(flt);
}

int main() {
  double foo;

  foo = float_validate();

  cout << foo << endl;

  return 0;
}
