#include <iostream>
#include <fstream>
using namespace std;

int main() {
  int bounce;
  fstream test("test.txt", ios::in | ios::out);

  test >> bounce;
  cout << bounce << endl;
  cout << "What shall I add: ";
  test.seekg(0, ios::end);
  cin >> bounce;
  test << bounce;
  test.close();

  return 0;
}
