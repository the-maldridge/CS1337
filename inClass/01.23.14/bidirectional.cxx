#include <fstream>
#include <iostream>
using namespace std;

int main() {
  fstream testfile("test.txt", ios::in | ios::out);
  cout << testfile;
  return 0;
}
