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
enum searchAction {FIND, EDITREMOVE};
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

bool uniqueID(vector<dbrecord> db, string id) {
  bool match=false;
  for(int i=0; i<db.size(); i++) {
    match=false;
    for(int j=0; j<7; j++) {
      if(db[i].id.c_str()[j]==id.c_str()[j]) {
	match=true;
      } else {
	match=false;
	break;
      }
    }
    if(match) {
      //id was not unique
      cerr << "Primary key collision!" << endl;
      return false;
    }
  }
  //we went through the entire array and the id was unique
  return true;
}

void addRecord(vector<dbrecord> &db) {
  dbrecord temp;

  cout << "Add a record:" << endl;
  cout << "Directions for input are provided for each step, if the" << endl;
  cout << "prompt appears a second point, your input did not satisfy" << endl;
  cout << "one or more parameters for the given option." << endl << endl;

  do {
    cout << "Input an id of 3 letters followed by 4 numbers: ";
    cin >> temp.id;
  } while(!valID(temp.id) || !uniqueID(db, temp.id));

  cout << "Input a brief description of the item: " << endl;
  cin.ignore(1,'\n');
  getline(cin, temp.desc);

  do {
    cout << "How many items are in inventory now: ";
    cin >> temp.quantity;
  } while(temp.quantity<0);

  do {
    cout << "The wholesale cost may not exceed $100." << endl;
    cout << "The retail markup may not exceed %75." << endl;
    cout << "What is the wholesale cost: ";
    cin >> temp.wCost;
    cout << "What is the retail cost: ";
    cin >> temp.rCost;
  } while(!valCost(temp.rCost, temp.wCost));

  db.push_back(temp);
}

bool sortCompID(const dbrecord &a, const dbrecord &b) {
  return (a.id<b.id)?true:false;
}

void save(vector<dbrecord> db, string fname) {
  if(db.size()>0){

    cout << "Ordering output..." << endl;
    sort(db.begin(), db.end(), sortCompID);
    fstream disk(fname.c_str(), ios::trunc | ios::out);

    cout << "Writing data to disk..." << endl;
    for(int i=0; i<db.size(); i++) {
      disk << db[i].id << endl;
      disk << db[i].desc << endl;
      disk << db[i].quantity << endl;
      disk << db[i].wCost << endl;
      disk << db[i].rCost << endl;
      disk << endl;
    }

    disk.close();
    cout << "Finished saving to disk" << endl;
  } else {
    cout << "Database of zero length, NOT SAVING!" << endl;
  }
}

int searchRecord(vector<dbrecord> &db, searchAction mode) {
  string id;
  int recordLoc=0;
  bool found=false;
  char choice;

  cout << "Input your ID query: ";
  cin >> id;

  for(; recordLoc<db.size(); recordLoc++) {
    if(db[recordLoc].id==id) {
      found=true;
      dumpdb(db, recordLoc);
    }
  }

  if(!found) {
    cerr << "Your query returned 0 results." << endl;
  } else if(mode==EDITREMOVE) {
    do {
      cout << "Are you SURE you want to delete the record above? [y/n]: ";
      cin >> choice;
    } while(toupper(choice) != 'Y' && toupper(choice)!='N');
    if(toupper(choice)=='Y') {
      cout << "Deleting record with id " << db[recordLoc].id << endl;
      return recordLoc;
    } else {
      cout << "Delete cancelled, record preserved" << endl;
      return -1;
    }
  }
  else return -1;
}

void deleteRecord(vector<dbrecord> &db, int recordLoc) {
  db.erase(db.begin()+recordLoc);
}
      
int main() {
  menuAction action;
  vector<dbrecord> database;
  int loc;

  if(init("inventory.dat", database)) {
    while(true) {
      switch(mainMenu()) {
      case VIEW:
	dumpdb(database);
	break;
      case ADD:
	addRecord(database);
	break;
      case DELETE:
	loc=searchRecord(database, EDITREMOVE);
	cout << "location: " << loc << endl;
	if(loc!=-1) {
	  deleteRecord(database, loc);
	}
	break;
      case SEARCH:
	searchRecord(database, FIND);
	break;
      case REPORT:
	break;
      case QUIT:
	save(database, "inventory.dat");
	cout << "Exiting..." << endl;
	return 0;
      }
    }
  } else {
    return 1;
  }
}
