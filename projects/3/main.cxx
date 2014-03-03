/*
Automatic exam grading program.
It reads in SSV answer keys and student response files
Then spits out SSV grade report files
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
//pull in logging stuff
#include "log.h"

//back to normal stuff
using namespace std;

bool init(string answers, string tests, char* &ansKey, int* &ID, char** &responses, int* &grades, int &tSize, int &cSize) {
  ifstream key(answers.c_str());
  ifstream toGrade(tests.c_str());
  char* bounce = new char[1024];
  tSize=0; //length of the test
  cSize=0; //size of the class taking it

  if(key && toGrade){
    key >> tSize; //find out how long the test was
    FILE_LOG(logINFO) << "Your selected key contains " << tSize << " answers.";
    
    //build a place to put the answers
    ansKey = new char[tSize];
    
    //read in the answers to the key
    for(int i=0; i<tSize; i++) {
      key >> *(ansKey+i);
      FILE_LOG(logDEBUG1) << "Read answer: " << i + 1 << ":" << *(ansKey+i);
    }
    
    //do some absurd file stuff to account for inconsistencies in the 
    //provided file spec -- please revise rubric for next semester
    for(int i=0; toGrade.getline(bounce, 1024); i++) {
      cSize++;
      FILE_LOG(logDEBUG1) << "Read exam: " << i + 1 << ":" << bounce;
    }
    FILE_LOG(logINFO) << "The test file appears to have " << cSize << " tests";

    //build the array for IDs
    ID = new int[cSize];

    //build the array for responses
    responses = new char*[cSize];
    for (int i=0; i<cSize; ++i) {
      *(responses+i) = new char[tSize];
    }

    //create a bounce string to move stuff through before actual arrays
    string fbounce;

    //reset the file read pointer
    toGrade.clear();
    toGrade.seekg(0, toGrade.beg);
    
    //read in the class info to the array
    for(int i=0; i<cSize; i++) { //select row
      char* row = *(responses+i); //load row as new pointer
      getline(toGrade, fbounce); //grab a response set from the file
      FILE_LOG(logDEBUG1) << "Now importing: " << fbounce; //sanity check
      stringstream input(fbounce); //create a stream object to extract formatted output
      input >> *(ID+i); //put the ID into the ID array
      FILE_LOG(logDEBUG2) << "ID was: " << *(ID+i); //sanity check
      for(int j=0; j<tSize; j++) { //within the row, put in the answers
	input >> *(row+j); //extract and add answers
	FILE_LOG(logDEBUG2) << "Answer was: " << *(row+j); //sanity check
      }
    FILE_LOG(logDEBUG1) << "Imported test " << i+1;
    }

    //finally create the array for the scores
    grades = new int[cSize];
     
  } else {
    FILE_LOG(logERROR) << "A provided input file was invalid";
    return false;
  }
}
  
int* grade(int* ID, char** tests, char* key, int* grades, string outfile, int cSize, int tSize) {
  //grade the exams

  for(int i=0; i<cSize; i++) {
    FILE_LOG(logDEBUG1) << "Now grading student " << i+1;
    char* student = *(tests+i); //copy single set of responses to pointer
    for(int j=0; j<tSize; j++) {
      if (toupper(*(student+j))==toupper(*(key+j))) {
	FILE_LOG(logDEBUG2) << "Answer "<< j+1 << " was   correct (" << *(key+j) << ":" << *(student+j) << ")";
      } else {
	FILE_LOG(logDEBUG2) << "Answer "<< j+1 << " was incorrect (" << *(key+j) << ":" << *(student+j) << ")";
      }
    }
  }
}
int main(int argc, char** argv) {
  //begin the logger
  FILELog::ReportingLevel() = FILELog::FromString(argv[1]?argv[1]:"DEBUG3");
  FILE_LOG(logDEBUG) << "Program Start";

  //init a place to store the test stuff
  char* key;
  int* ID;
  char** tests;
  int* grades;
  int cSize, tSize;

  //add some more variables for other stuff
  string keyfile, examfile, reportfile;

  keyfile = "answers.txt";
  examfile = "exams.txt";
  reportfile = "report.txt";

  if(init(keyfile, examfile, key, ID, tests, grades, tSize, cSize)) {
    grades = grade(ID, tests, key, grades, reportfile, cSize, tSize);
  } else {
    FILE_LOG(logERROR) << "A load error occured, exiting...";
  }
  return 0;
}
