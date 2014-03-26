/*
Revenge of the database, need I say more?
*/

/*
Questions:
  Case sensitivity? -- not a concern
  Validate that numbers look like numbers -- yes, must have a . and 2 decimals
  Implement EDIT
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <stack>
using namespace std;


enum menuAction {VIEW=1, ADD, EDIT, DELETE, SEARCH, REPORT, QUIT};
enum searchAction {FIND, MODIFY, REMOVE};
struct dbrecord {
  string id;
  string desc;
  int quantity;
  float wCost;
  float rCost;
};

string normalize(string s) {
  transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
}

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
bool looksLikePrice(float cost) {
  char price[10]={'\0'};
  bool begIsGood=false, endIsGood=false, good=true;

  //convert to c-string for validation
  sprintf(price, "%.2f", cost);

  for(int i=0; price[i]!='\0'; i++) {
    //check if there are non-good characters in the array
    if(price[i]!='.' && !isalpha(price[i]) && !isdigit(price[i])) {
      //the string contains something that isn't a valid component
      good=false;
    }

    //check if the point and beyond are good
    if(price[i]=='.') {
      //we found a point, the next two characters have to be number
      if(isdigit(price[i+1]) && isdigit(price[i+2])) {
	//after the numbers there must not be anything
	if(price[i+3]=='\0') {
	  endIsGood=true;
	}
      }
    }
  }
  //we made it all the way through the string
  return good && endIsGood;
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
  if(!looksLikePrice(rCost) && !looksLikePrice(wCost)) {
    //check if they both look like numbers!
    cerr << "\tGiven price doesn't look like a price!" << endl;
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

      //fix any IDs coming in from disk
      temp.id = normalize(temp.id);

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
  cout << "3. Edit a record" << endl;
  cout << "4. Delete a record" << endl;
  cout << "5. Search for a record" << endl;
  cout << "6. Generate an inventory report" << endl;
  cout << "7. Quit" << endl;

  cout << endl;

  cout << "Input your selection: ";
  cin >> choice;

  while(choice<1 || choice>7) {
    cout << "Your selection was invalid!" << endl;
    cout << "Input a valid choice: ";
    cin >> choice;
  }

  return static_cast<menuAction>(choice);
}

void dumpdb(vector<dbrecord> &db) {
  //dump the entire database
  cout << "The database currently contains the following:" << endl;
  for(int i=0; i<db.size(); i++) {
    cout << "----------BOR----------" << endl;
    cout << "ID: " << db[i].id << endl;
    cout << "Description: " << db[i].desc << endl;
    cout << "Quantity on hand: " << db[i].quantity << endl;
    cout << "Wholesale Cost: " << db[i].wCost << endl;
    cout << "Retail Cost: " << db[i].rCost << endl;
    cout << "----------EOR----------" << endl;
  }
}

void dumpdb(vector<dbrecord> &db, int i) {
  //dump a select record from the database
    cout << "----------BOR----------" << endl;
    cout << "ID: " << db[i].id << endl;
    cout << "Description: " << db[i].desc << endl;
    cout << "Quantity on hand: " << db[i].quantity << endl;
    cout << "Wholesale Cost: " << db[i].wCost << endl;
    cout << "Retail Cost: " << db[i].rCost << endl;
    cout << "----------EOR----------" << endl;
}

bool uniqueID(vector<dbrecord> db, string id) {
  //verify the ID is unique
  bool match=false;

  //look at all the IDs
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

  //get an ID and make sure it is unique
  do {
    cout << "Input an id of 3 letters followed by 4 numbers: ";
    cin >> temp.id;
  } while(!valID(temp.id) || !uniqueID(db, temp.id));

  //normalize the ID
  temp.id = normalize(temp.id);

  cout << "Input a brief description of the item: " << endl;
  cin.ignore(1,'\n');
  getline(cin, temp.desc);

  //get the number of things in the inventory
  do {
    cout << "How many items are in inventory now: ";
    cin >> temp.quantity;
  } while(temp.quantity<0);

  //get the retail and wholesale cost and validate it
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
  //this function is needed to make std::sort() work on structs
  return (a.id<b.id)?true:false;
}

void save(vector<dbrecord> db, string fname) {

  //sort everything and open the file
  cout << "Ordering output..." << endl;
  sort(db.begin(), db.end(), sortCompID);
  fstream disk(fname.c_str(), ios::trunc | ios::out);
  
  //write it to disk
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
}

int searchRecord(vector<dbrecord> &db, searchAction mode) {
  string id;
  int recordLoc=0;
  bool found=false;
  char choice;

  cout << "Input your query: ";
  cin >> id;

  //normalize the ID
  id = normalize(id);

  for(; recordLoc<db.size(); recordLoc++) {
    if(mode==REMOVE) {
      if(db[recordLoc].id==id) {
	found=true;
	dumpdb(db, recordLoc);
	break;
      }
    } else if(mode==MODIFY) {
      if(db[recordLoc].id==id) {
	found=true;
	dumpdb(db, recordLoc);
	break;
      }
    } else if(mode==FIND) {
      if((db[recordLoc].id==id) || (db[recordLoc].desc.find(id)!=string::npos)) {
	dumpdb(db, recordLoc);
	found=true;
      }
    }
  }
  
  if(!found) {
    cerr << "Your query returned 0 results." << endl;
    return -1;
  } else if(mode==REMOVE) {
    //prompt to see if the user is sure and continue
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
  } else if(mode==MODIFY) {
    //prompt to see if the user if sure and continue
    do {
      cout << "Are you SURE you want to edit the record above? [y/n]: ";
      cin >> choice;
    } while(toupper(choice) != 'Y' && toupper(choice)!='N');
    if(toupper(choice)=='Y') {
      cout << "Editing record with id " << db[recordLoc].id << endl;
      return recordLoc;
    } else {
      cout << "Edit cancelled, record preserved" << endl;
      return -1;
    }
  }
  else return -1;
}

void deleteRecord(vector<dbrecord> &db, int recordLoc) {
  //erase the record at a given offset
  db.erase(db.begin()+recordLoc);
}

void inventoryReport(vector<dbrecord> db) {
  //generate an inventory report
  int items = 0;
  float wholesale = 0, retail = 0;

  //total the costs based on how many of each item are in inventory
  for(int i=0; i<db.size(); i++) {
    items += db[i].quantity;
    wholesale += db[i].quantity * db[i].wCost;
    retail += db[i].quantity * db[i].rCost;
  }

  //display the report
  cout << "Report is as follows:" << endl;
  cout << "Total number of items in inventory: " << items << endl;
  cout << "Total wholesale value: " << wholesale << endl;
  cout << "Total retail value: " << retail << endl;
      
}

void editRecord(vector<dbrecord> &db, int loc) {
  stack<int> choice;
  int bounce;

  //find out what they want to edit
  cout << "What would you like to edit?" << endl;
  cout << endl;
  cout << "1. Description" << endl;
  cout << "2. Quantity" << endl;
  cout << "3. Wholesale Cost" << endl;
  cout << "4. Retail Cost" << endl;
  cout << endl;
  cout << "Edit: ";
  cin >> bounce;

  //validate the user choice
  while(bounce<1 || bounce>4) {
    cerr << "INVALID INPUT" << endl;
    cout << "Input a valid choice: ";
    cin >> bounce;
    cin.ignore(1,'\n');
  }

  //add the option to the stack
  choice.push(bounce);

  //perform the requested operations
  do {
    switch(choice.top()) {
    case 1:
      //edit the description
      cout << "The current description is:" << endl;
      cout << db[loc].desc << endl;
      cout << "Please enter new description:" << endl;
      cin.ignore(1, '\n');
      getline(cin, db[loc].desc);
      break;
    case 2:
      //edit the quantity
      cout << "The current quantity is: " << db[loc].quantity << endl;
      cout << "Input new quantity: ";
      cin.ignore(1, '\n');
      cin >> db[loc].quantity;
      break;
    case 4:
      //edit the wholesale cost
      cout << "The wholesale cost is $" << db[loc].wCost << endl;
      cout << "Enter new wholesale cost: ";
      cin.ignore(1, '\n');
      cin >> db[loc].wCost;

      //validate the cost
      if(valCost(db[loc].wCost, db[loc].rCost)) {
	cout << "Costs valid" << endl;
	break;
      } else {
	cout << "You must now change the retail cost" << endl;
	choice.push(5);
	break;
      }
    case 5:
      //edit the retail cost
      cout << "The retail cost is $" << db[loc].rCost << endl;
      cout << "Enter new retail cost: ";
      cin.ignore(1, '\n');
      cin >> db[loc].rCost;
      
      if(valCost(db[loc].wCost, db[loc].rCost)) {
	cout << "Costs valid" << endl;
	break;
      } else {
	cout << "You must now change the wholesale cost" << endl;
	choice.push(4);
	break;
      }
    }
    choice.pop();
  } while(!choice.empty());
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
      case EDIT:
	loc=searchRecord(database, MODIFY);
	if(loc!=-1) {
	  editRecord(database, loc);
	}
	break;
      case DELETE:
	loc=searchRecord(database, REMOVE);
	if(loc!=-1) {
	  deleteRecord(database, loc);
	}
	break;
      case SEARCH:
	searchRecord(database, FIND);
	break;
      case REPORT:
	inventoryReport(database);
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
