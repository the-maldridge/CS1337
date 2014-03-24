/*
Revenge of the database, need I say more?
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <cmath>
using namespace std;


enum menuAction {VIEW=1, ADD, DELETE, SEARCH, REPORT, QUIT};
struct dbrecord {
  string id;
  string desc;
  int quantity;
  float wCost;
  float rCost;
};


bool valID(string id) {
  //check if it has the right number of letters
  for(int i=0; i<3; i++) {
    if(!isalpha(id.c_str()[i])) {
      return false;
    }
  }

  //check if it has the right number of numbers
  for(int i=3; i<7; i++){
    if(!isdigit(id.c_str()[i])) {
      return false;
    }
  }

  //if it made it this far it is likely well formed
  return true;
}

bool valCost(float rCost, float wCost) {
  if(rCost<wCost) {
    //the retail less than wholesale
    cerr <<"\tNet loss cost analysis" << endl;
    return false;
  }
  if((abs(wCost/rCost))>0.75) {
    //the markup is invalid
    cerr << "\tInvalid markup "<< (wCost/rCost) << endl;
    return false;
  }
  if(false) {
    //check if they both look like numbers!
    return false;
  }

  //it passed all the checks return true
  return true;
}

bool init(string fname, vector<dbrecord> &db) {

  fstream disk(fname.c_str(), ios::in);

  if(!disk) {
    cerr << "No data file existed, I have created one for you!" << endl;
    disk.close();
    disk.open(fname.c_str(), ios::out);
    return true; //if we created it, the file was blank
  } else {
    while(disk.good()) {
      //temp place to store the db record
      dbrecord temp;

      //input the data to a temp struct
      disk >> temp.id;
      disk.ignore(1, '\n');
      getline(disk, temp.desc);
      disk >> temp.quantity;
      disk >> temp.wCost;
      disk >> temp.rCost;
      disk >> ws;

      //validate the incomming record
      if(valID(temp.id) && valCost(temp.rCost, temp.wCost)) {
	cerr << "Valid record: " << temp.id << "  was loaded!" << endl;
	db.push_back(temp);
      } else {
	cerr << "Invalid record: " << temp.id << "  was not loaded!" << endl;
      }
    }
  }

  cout << "Finished loading database!" << endl << endl;
}

menuAction mainMenu() {
  int choice;

  cout << "MAIN MENU" << endl;
  cout << endl << endl;

  cout << "1. View entire database" << endl;
  cout << "2. Add a record" << endl;
  cout << "3. Delete a record" << endl;
  cout << "4. Search for a record" << endl;
  cout << "5. Generate an inventory report" << endl;
  cout << "6. Quit" << endl;

  cout << endl;

  cout << "Input your selection: ";
  cin >> choice;

  while(choice<1 || choice>6) {
    cout << "Your selection was invalid!" << endl;
    cout << "Input a valid choice: ";
    cin >> choice;
  }

  return static_cast<menuAction>(choice);
}

void dumpdb(vector<dbrecord> &db) {
  cout << "The database currently contains the following:" << endl;
  for(int i=0; i<db.size(); i++) {
    cout << "----------BOR----------" << endl;
    cout << "ID: " << db[i].id << endl;
    cout << "Description: " << db[i].desc << endl;
    cout << "Quantity on hand" << db[i].quantity << endl;
    cout << "Wholesale Cost: " << db[i].wCost << endl;
    cout << "Retail Cost: " << db[i].rCost << endl;
    cout << "----------EOR----------" << endl;
  }
}

void dumpdb(vector<dbrecord> &db, int i) {
    cout << "----------BOR----------" << endl;
    cout << "ID: " << db[i].id << endl;
    cout << "Description: " << db[i].desc << endl;
    cout << "Quantity on hand" << db[i].quantity << endl;
    cout << "Wholesale Cost: " << db[i].wCost << endl;
    cout << "Retail Cost: " << db[i].rCost << endl;
    cout << "----------EOR----------" << endl;
}

int main() {
  menuAction action;
  vector<dbrecord> database;

  if(init("inventory.dat", database)) {
    while(true) {
      switch(mainMenu()) {
      case VIEW:
	dumpdb(database);
	break;
      case ADD:
	break;
      case DELETE:
	break;
      case SEARCH:
	break;
      case REPORT:
	break;
      case QUIT:
	cout << "Exiting..." << endl;
	return 0;
      }
    }
  } else {
    return 1;
  }
}
