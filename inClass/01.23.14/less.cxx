/*
knockoff of less for the in class file example
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char** argv) {
  string bounce;
  bool linesleft = true;
  ifstream file;

  if (argc>1) {
    file.open(argv[1]);
    if (file.fail()) {
      cout << "Invalid File Descriptor" << endl;
      return 1;
    }
  } else {
    cout << "You must specify a file descriptor!" << endl;
    return 2;
  }

  while(linesleft) {
    for (int i=0; i<24; i++) {
      getline(file, bounce);
      if(!file.eof()) {
	cout << bounce << endl;
      } else {
	linesleft = false;
	break;
      }
    }
    cin.get();
    cin.ignore(1024, '\n');
  }
  return 0;
}
