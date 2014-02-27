#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  string input; //some place to put the input
  int ID; //the student ID number
  char ans[4]; // some place to put the answers

  //get our input 
  cout << "Enter a number followed by 4 letters" << endl;
  getline(cin, input);

  stringstream textstream(input); //create an object for the textstream

  textstream >> ID; //the ID is of type int, so we'll send it there first

  //we will use a loop to put the answers in
  //textstream.str().size() first converst the text stream to a string
  //then it calls the size command on it to find out how long it is
  for(int i=0; i<textstream.str().size(); i++) {
    textstream >> ans[i]; //add each answer to the score array
    // ^^ technically that will run past the end of the array, but we don't care
  }


  //output!
  cout << "ID: " << ID << endl;
  for(int i=0; i<4; i++) {
    //send out the values in the array one by one
    cout << "Answer " << i+1 << ": " << ans[i] << endl;
  }

  //let the system know we are done
  return 0;
}

//it should be noted that the file itself as you read in will provide an
//iterable object if you do it in such a way that you have the first thing
//(ID) read into a variable, and then jump into the for loop for the answers
//themselves;  the sstream solution is of course perfectly acceptable though
