/*
Automatic exam grading program.
It reads in SSV answer keys and student response files
Then spits out SSV grade report files
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <algorithm>
//pull in logging stuff
#include "log.h"

//back to normal stuff
using namespace std;

bool init(string answers, string tests, char* &ansKey, string* &ID, char** &responses, float* &grades, int &tSize, int &cSize) {
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
    ID = new string[cSize];

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
    grades = new float[cSize];
     
  } else {
    FILE_LOG(logERROR) << "A provided input file was invalid";
    return false;
  }
}

char letterGrade(float percent) {
  int lbracket = percent/10;

  switch(lbracket) {
  case 10:
  case 9:
    return 'A';
  case 8:
    return 'B';
  case 7:
    return 'C';
  case 6:
    return 'D';
  default:
    return 'F';
  }
}
  
void grade(string* ID, char** tests, char* key, string outfile, int cSize, int tSize, float* &grades) {
  //grade the exams
  ofstream report(outfile.c_str());

  for(int i=0; i<cSize; i++) {
    stringstream wrongNums, wrongAns, rightAns; //streams to put the report lines in
    int wrong=0;

    FILE_LOG(logINFO) << "Now grading student " << i+1;
    report << *(ID+i) <<endl; //output the ID number to the report
    char* student = *(tests+i); //"copy" single set of responses to pointer

    for(int j=0; j<tSize; j++) { //iterate over test answers
      if (toupper(*(student+j))==toupper(*(key+j))) { //normalize and grade
	//it was correct, put the answer in the log for debug purposes
	FILE_LOG(logDEBUG2) << "Answer "<< j+1 << " was   correct (" << *(key+j) << ":" << *(student+j) << ")";
      } else {
	//it was wrong, add the info to the streams
	FILE_LOG(logDEBUG2) << "Answer "<< j+1 << " was incorrect (" << *(key+j) << ":" << *(student+j) << ")";
	wrongNums << setw(3) << right << j; //record which one was wrong
	rightAns << setw(3) << right << *(key+j); //record the correct answer
	wrongAns << setw(3) << right << *(student +j); //record the wrong answer
	wrong++; //increment the number wrong
      }
    }
    FILE_LOG(logDEBUG3) << wrong << " questions were missed"; //sanity check

    float percentGrade = ((tSize-wrong)/static_cast<float>(tSize)) * 100; //calculate a percent
    report << setprecision(2) << fixed << percentGrade << "  "; //output the number grade
    report << setprecision(2) << fixed << letterGrade(percentGrade) << endl; //output the letter grade
    //only add wrong answer info if they missed something
    if(wrongNums.str().length()) {
      report << wrongNums.str() << endl;
      report << wrongAns.str() << endl;
      report << rightAns.str() << endl;
    } 
    report << endl; //seperator between students

    //save the grade into the array and debug out
    *(grades+i) = percentGrade;
    FILE_LOG(logDEBUG3) << "Student scored: " << percentGrade;
  }
  //close out the report so we can open it again later to add the final information
  report.close();
}

double calMedian(float* scores, int cSize) {
  FILE_LOG(logINFO) << "Now calculating median score";

  //create a new array that can be sorted
  float* scorestart = scores;
  float* scoreend = scores+--cSize;
  double median = 0;

  //use the sort function someone smarter than me wrote
  FILE_LOG(logDEBUG1) << "Attempting to sort scores";
  sort(scorestart, scoreend);
  FILE_LOG(logDEBUG1) << "Sort seems to have succeeded";

  if(cSize%2==0) {
    //there's an even number of students, average the 2 in the middle
    median = (*(scores+cSize/2) + *(scores+(cSize/2-1)))/2.0f;
  } else {
    //the class is odd and we can just pick the middle number
    median = *(scores +cSize/2);
  }

  //return the median
  FILE_LOG(logINFO) << "Class median score is: " << median;
  return median;
}

double calMean(float* scores, int cSize) {
  double totalPoints=0, mean=0;

  FILE_LOG(logINFO) << "Now calculating class average";

  for(int i=0; i<cSize; i++) {
    totalPoints += *(scores+i);
  }
  
  FILE_LOG(logDEBUG1) << "Total points: " << totalPoints;
  FILE_LOG(logDEBUG1) << "Total students: " << cSize;

  //divide by class size to get the class average
  mean = totalPoints/cSize;
  FILE_LOG(logINFO) << "Class average score is: " << mean;

  //return the average
  return mean;
}

int main(int argc, char** argv) {
  //begin the logger
  FILELog::ReportingLevel() = FILELog::FromString(argv[1]?argv[1]:"DEBUG3");
  FILE_LOG(logDEBUG) << "Program Start";

  //init a place to store the test stuff
  char* key;
  string* ID;
  char** tests;
  float* grades;
  int cSize, tSize;

  //add some more variables for other stuff
  string keyfile, examfile, reportfile;
  double mean, median, mode;

  keyfile = "answers.txt";
  examfile = "exams.txt";
  reportfile = "report.txt";

  if(init(keyfile, examfile, key, ID, tests, grades, tSize, cSize)) {
    grade(ID, tests, key, reportfile, cSize, tSize, grades);
    median = calMedian(grades, cSize);
    mean = calMean(grades, cSize);
  } else {
    FILE_LOG(logERROR) << "A load error occured, exiting...";
  }
  return 0;
}
