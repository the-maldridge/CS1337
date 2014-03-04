/*
Automatic exam grading program. -- Michael Aldridge
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

  //only continue if the files linked correctly
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
    //something went wrong linking the file, return false so we don't try to continue
    FILE_LOG(logERROR) << "A provided input file was invalid";
    return false;
  }
}

char letterGrade(float percent) {
  int lbracket = percent/10;

  //convert to a letter grade from a percent
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
    //iterate over students
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
	wrongNums << setw(4) << right << j; //record which one was wrong
	rightAns << setw(4) << right << *(key+j); //record the correct answer
	wrongAns << setw(4) << right << *(student +j); //record the wrong answer
	wrong++; //increment the number wrong
      }
    }
    FILE_LOG(logDEBUG3) << wrong << " questions were missed"; //sanity check

    //calculate a percent
    float percentGrade = ((tSize-wrong)/static_cast<float>(tSize)) * 100;

    //put the percent and letter in the report
    report << setprecision(2) << fixed << percentGrade << "  ";
    report << setprecision(2) << fixed << letterGrade(percentGrade) << endl;

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
  //close out the report so we can open it again later to add the final statistics information
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
  FILE_LOG(logINFO) << "Class median score is: " << setprecision(2) << fixed << median;
  return median;
}

double calMean(float* scores, int cSize) {
  double totalPoints=0, mean=0;

  FILE_LOG(logINFO) << "Now calculating class average";

  //find the total points the class could have scored
  for(int i=0; i<cSize; i++) {
    totalPoints += *(scores+i);
  }
  
  //debugs for sanity checks
  FILE_LOG(logDEBUG1) << "Total points: " << totalPoints;
  FILE_LOG(logDEBUG1) << "Total students: " << cSize;

  //divide by class size to get the class average
  mean = totalPoints/cSize;
  FILE_LOG(logINFO) << "Class average score is: " << setprecision(2) << fixed << mean;

  //return the average
  return mean;
}

float* calMode(float* scores, int cSize) {
  int currentMax=1, totalMax=1;

  FILE_LOG(logINFO) << "Now calculating the mode(s)";

  //first sort the array
  FILE_LOG(logDEBUG1) << "Attempting to sort";
  float* scorestart = scores;
  float* scoreend = scores+cSize;
  sort(scorestart, scoreend);
  FILE_LOG(logDEBUG1) << "Sort appears to have succeeded";

  //find the largest mode
  FILE_LOG(logDEBUG1) << "calculating the largest mode order";
  for(int i=0; i<cSize-1; i++) {
    if (*(scores+i) == *(scores+i+1)) {
      currentMax++;
      FILE_LOG(logDEBUG2) << "Current max order is: " << currentMax;
      if(currentMax>totalMax) {
	totalMax = currentMax;
	FILE_LOG(logDEBUG3) << "replacing max order with: " << currentMax;
      }
    } else {
      currentMax=0;
    }
  }

  //find out how many times the largest mode occurs
  int occurences = 0, modes = 0;
  float last = *scores;

  //work out how many modes need to be returned
  FILE_LOG(logDEBUG1) << "counting the number of modes to return";
  for(int i=0; i<cSize; i++) {
    if(*(scores+i) != last) {
      last = *(scores+i);
      occurences=0;
    }
    if(occurences == totalMax) {
      modes++;
    } else {
      occurences++;
    }
  }
  FILE_LOG(logDEBUG1) << "Found " << modes << " modes";

  //store the found modes in an array for later return
  float* scoreModes = new float[modes+1];
  *(scoreModes+modes) = -1; //add a sentinel to know when we are out of modes later

  occurences = 0;
  int j = 0;
  last = *scores;
  
  FILE_LOG(logDEBUG1) << "Now saving the mode(s)";
  for(int i=0; i<cSize; i++) {
    if(*(scores+i) != last) {
      last = *(scores+i);
      occurences=0;
    }
    if(occurences == totalMax) {
      FILE_LOG(logDEBUG2) << "Saving mode: " << *(scores+i);
      *(scoreModes+j) = *(scores+i);
      j++;
    } else {
      occurences++;
    }
  }

  //log what modes were saved
  stringstream modesSaved;
  for(int i=0; *(scoreModes+i)!=-1; i++) {
    modesSaved << *(scoreModes+i) << " ";
  }

  FILE_LOG(logINFO) << "Saved mode(s): " << modesSaved.str();

  //return the pointer to the array of modes
  return scoreModes;
}

void statisticsReport(double median, double mean, float* mode, string outfile) {
  ofstream report(outfile.c_str(), ios::app);

  FILE_LOG(logINFO) << "Appending statistics info to the report";

  report << "Mean: " << setprecision(2) << fixed << mean << endl;
  report << "Median: " << setprecision(2) << fixed << median << endl;
  report << "Mode(s): ";

  for(int i=0; *(mode+i)!=-1; i++) {
    FILE_LOG(logDEBUG1) << "adding mode: " << *(mode + i);
    report << *(mode+i) << " ";
  }

  //add the standards compliant line ending
  report << endl;

  //close the file and we are done
  report.close();
}

int main(int argc, char** argv) {
  //begin the logger
  FILELog::ReportingLevel() = FILELog::FromString(argv[1]?argv[1]:"INFO");
  FILE_LOG(logDEBUG) << "Program Start";

  //init a place to store the test stuff
  char* key;
  string* ID;
  char** tests;
  float* grades;
  int cSize, tSize;

  //add some more variables for other stuff
  string keyfile, examfile, reportfile;
  double mean, median;
  float* modes;

  //where is the data coming from and going to
  keyfile = "answers.txt";
  examfile = "exams.txt";
  reportfile = "report.txt";

  if(init(keyfile, examfile, key, ID, tests, grades, tSize, cSize)) {

    //grade the tests
    grade(ID, tests, key, reportfile, cSize, tSize, grades);

    //perform the statistical analysis
    median = calMedian(grades, cSize);
    mean = calMean(grades, cSize);
    modes = calMode(grades, cSize);

    //append the statistics results to the output file
    statisticsReport(mean, median, modes, reportfile);
  } else {
    //we couldn't load the inputs, log and die
    FILE_LOG(logERROR) << "A load error occured, exiting...";
  }

  //free up memory -- ignoring for now the fact that the OS does this for us...
  delete [] key;
  delete [] ID;
  for(int i=0; i<cSize; i++) {
    delete [] *(tests+i);
  }
  delete [] tests;
  delete [] grades;

  //log that we are done, and exit
  FILE_LOG(logINFO) << "Grading Complete";
  return 0;
}
