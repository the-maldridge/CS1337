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
#ifdef LOG1
#include "log1.h"
#else
#include "log.h"
#endif

//back to normal stuff
using namespace std;


bool init(string answers, string tests) {
  ifstream key(answers.c_str());
  ifstream toGrade(tests.c_str());
  int tSize;

  key >> tSize; //find out how long the test was
  FILE_LOG(logINFO) << "Your selected key contains " << tSize << " answers.";

}


int main(int argc, char** argv) {
  FILELog::ReportingLevel() = FILELog::FromString(argv[1]?argv[1]:"DEBUG");
  FILE_LOG(logDEBUG) << "Program Start";
  init("answers.txt", "exams.txt");
  return 0;
}
