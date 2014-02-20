/*
Read in some names and determine who should be at the start of the line.

Accomplish by reading names and checking if ASCII is lower/higher -> first/last
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
  int lineLength;
  string first, last, name;
  bool firstrun = true;

  cout << "Line alphabetizer will tell you who is at the front and back.\n";
  cout << "In between is your problem!" << endl;

  do {
    cout << "How many students are in the line? (min 1. max 25.)" << endl;
    cin >> lineLength;
  } while(lineLength < 1 || lineLength > 25);

  for (; lineLength > 0; lineLength--) {
    cout << "Enter a name: ";
    cin >> name;

    first = ((name < first) || firstrun)?name:first;
    last = (!(name < last) || firstrun)?name:last;
    firstrun=false;
  }

  cout << "First student is " << first << "." << endl;
  cout << "Last student is " << last << "." << endl;

  return 0;
}
