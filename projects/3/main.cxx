/*
Automatic exam grading program.
It reads in SSV answer keys and student response files
Then spits out SSV grade report files
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

//pull in logging stuff
#include "log.h"

//back to normal stuff
using namespace std;


bool init(string answers, string tests) {
  ifstream key(answers.c_str());
  ifstream toGrade(tests.c_str());
  string bounce;
  int tSize; //length of the test
  int cSize; //size of the class taking it

  if(key && toGrade){
    key >> tSize; //find out how long the test was
    FILE_LOG(logINFO) << "Your selected key contains " << tSize << " answers.";
    
    //build a place to put the answers
    char* ansKey = new char[tSize];
    
    //read in the answers to the key
    for(int i=0; i<tSize; i++) {
      key >> *(ansKey+i);
      FILE_LOG(logDEBUG1) << "Read answer: " << i + 1 << ":" << *(ansKey+i);
    }
    
    //do some absurd file stuff to account for inconsistencies in the 
    //provided file spec -- please revise rubric for next semester
    for(int i=0; getline(toGrade, bounce); i++) {
      cSize++;
      FILE_LOG(logDEBUG1) << "Read exam: " << i +1 << ":" << bounce;
    }
    FILE_LOG(logINFO) << "The test file appears to have " << cSize << " tests";
  } else {
    FILE_LOG(logERROR) << "A provided input file was invalid";
    return false;
  }
}
  

int main(int argc, char** argv) {
  FILELog::ReportingLevel() = FILELog::FromString(argv[1]?argv[1]:"DEBUG1");
  FILE_LOG(logDEBUG) << "Program Start";
  init("answers.txt", "exams.txt");
  return 0;
}
