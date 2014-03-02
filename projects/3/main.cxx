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

/*
bool init(string answers, string tests) {
  ifstream key(answers);
  ifstream toGrade(tests);
  int tSize;

  key >> tSize; //find out how long the test was

}
*/

int main(int argc, char** argv) {
  FILELog::ReportingLevel() = FILELog::FromString(argv[1]?argv[1]:"DEBUG1");
  FILE_LOG(logDEBUG1) << "Program Start";
  return 0;
}
