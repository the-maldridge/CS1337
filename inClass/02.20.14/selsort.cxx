#include <iostream>
#include <cctype>
using namespace std;


char* selsort(char* ptr, int len) {
  int lowMemLoc;
  for(int i=0; i<len-1; i++) {
    lowMemLoc=i;
    for(int j=i+1; j<len; j++) {
      if(*(ptr+j)<*(ptr+lowMemLoc)) {
	  lowMemLoc = j;
	}
    }
    swap(*(ptr+i), *(ptr+lowMemLoc));
  }
  return ptr;
}


int main() {
  int size;
  cout << "how many letters to alphabet" << endl;
  cin >> size;
  char* foo = new char[size];
  
  for(int i=0; i<size; i++) {
    cout << "Enter a letter: ";
    cin >> *(foo+i);
  }

  for(int i=0; i<size; i++) {
    cout << *(foo+i) << " ";
    }
  cout << endl;
  foo = selsort(foo, size);
  for(int i=0; i<size; i++) {
    cout << *(foo+i) << " ";
  }
  cout << endl;

  return 0;
}
