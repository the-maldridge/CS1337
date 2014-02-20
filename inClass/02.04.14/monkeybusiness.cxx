#include <fstream>
#include <iostream>
#include <string>

#define DAYS 7
#define POP 3

using namespace std;

bool parseInput(float food[POP][DAYS], string fname) {
  ifstream datfile(fname.c_str());

  if (!datfile) {
    cout << "Could not open data file" << endl;
    return false;
  } else {
    for(int i=0; i<DAYS; i++) {
      for(int j=0; j<POP; j++) {
	datfile >> food[i][j];
      }
    }
  }

  datfile.close();
  return true;
}

float weekAvg(float food[POP][DAYS]) {
  float avg;

  for(int i=0; i<DAYS; i++) {
    for(int j=0; j<POP; j++) {
      avg += food[i][j];
    }
  }

  cout << "total food was: " << avg << endl;
  return avg/DAYS;
}

void bounds(float food[POP][DAYS], float &lower, float &upper) {
  for(int i=0; i<DAYS; i++) {
    for(int j=0; j<POP; j++) {
      cout << food[i][j] << endl;
      if (food[i][j] > upper) {
	cout << "replacing old upper value of: " << upper << " with " << food[i][j] << endl;
	upper = food[i][j];
      }
      if (food[i][j]<lower) {
	lower = food[i][j];
	cout << "replacing old lower value of: " << lower << " with " << food[i][j] << endl;      }
    }
  }
}

void output(float avg, float lower, float upper) {
  cout << "The average food consumed was: \t" << avg << endl;
  cout << "The least food consumed was: \t" << lower << endl;
  cout << "The most food consumed was: \t" << upper << endl;
}

int main() {
  float foodstuffs[POP][DAYS] = {0};
  float lowest, greatest, average;

  if (parseInput(foodstuffs, "input.ssv")) {
    average = weekAvg(foodstuffs);
    bounds(foodstuffs, lowest, greatest);
    output(average, lowest, greatest);
    return 0;
  } else {
    cout << "A serious error occured!" << endl;
    return 1;
  }
}
