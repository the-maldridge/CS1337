/*
Simple database program, written by M. Aldridge

Has options to add, remove, edit, and search database entries in a flat file
database.  The engine uses vectors to store structs of records.  This allows
the system to edit the data in RAM, and then sync back to disk only when
necessary.  In this way file operations can be made to be quasi-atomic, while
not completely atomic, this does allow me to significantly reduce the chance
of the database file being corrupted.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctype.h>
#include <algorithm>
using namespace std;

//create a datatype to store the DB records
struct record {
  string ID;
  string desc;
  int quantity;
  float wCost;
  float rCost;
};

enum action {ADD=1, SEARCH, EDIT, DELETE, REPORT, DUMP, EXIT};
enum searchmode {SEARCHDB, EDITDEL};
enum recordEdits {ID, DESC, QUANT, WCOST, RCOST};

bool loadDB(vector<record> &db, string fname) {
  ifstream diskFile(fname.c_str());
  string bounce; //general string for some file checks and a dump for blanks

  //check if we got the file
  if (diskFile.fail()) {
    cerr << "The database file couldn't be opened!"; //write to stderr
    return false; //file didn't open
  }

  //read data into the vector
  while (diskFile.good()) {
    record temp; //Create a temporary struct to read into
    getline(diskFile, temp.ID); //read in the ID
    getline(diskFile, temp.desc); //read in the description
    diskFile >> temp.quantity; //read in how many there are (can't getline ints)
    diskFile >> temp.wCost; //read in wholesale cost (can't getline floats)
    diskFile >> temp.rCost; //read in the retail cost (can't getline floats)
    diskFile >> ws; //Discard the whitespace between records

    db.push_back(temp); //store the record in the RAM database copy
  }

  return true;
}

void saveDB(vector<record> &db, string fname) {
  ofstream diskFile(fname.c_str()); //grab a handle to the output file

  //set the output stream operators
  diskFile << fixed << setprecision(2) << showpoint;

  //output each record individually
  for (int i=0; i<static_cast<int>(db.size()); i++) {
    diskFile << db[i].ID << endl;
    diskFile << db[i].desc << endl;
    diskFile << db[i].quantity << endl;
    diskFile << db[i].wCost << endl;
    diskFile << db[i].rCost << endl;
    diskFile << endl;
  }

  diskFile.close(); //close out the data file
}

void dumpdb(vector<record> &db) {
  for(int i=0; i<db.size(); i++) {
    cout << "--------BOR--------" << endl;
    cout << db[i].ID << endl;
    cout << db[i].desc << endl;
    cout << db[i].quantity << endl;
    cout << db[i].wCost << endl;
    cout << db[i].rCost << endl;
    cout << "--------EOR--------" << endl;
  }
}

void dumpdb(vector<record> &db, int i) {
    cout << "--------BOR--------" << endl;
    cout << "ID: " << db[i].ID << endl;
    cout << "Description: " << db[i].desc << endl;
    cout << "Quantity: " << db[i].quantity << endl;
    cout << "Wholesale Cost: " << db[i].wCost << endl;
    cout << "Retail Cost: " << db[i].rCost << endl;
    cout << "--------EOR--------" << endl;
}

action rootMenu() {
  int choice;
  //display a menu and then get a choice to see what they want to do
  
  //display the menu
  cout << "Context: ROOT MENU" << endl;
  cout << endl;
  cout << "Choose from a choice below and enter its number: " << endl;
  cout << "1. Add a record" << endl;
  cout << "2. Search for an existing record" << endl;
  cout << "3. Edit an existing record" << endl;
  cout << "4. Delete an existing record" << endl;
  cout << "5. Generate an inventory report" << endl;
  cout << "6. Dump a complete copy of the database to this shell" << endl;
  cout << "7. Exit" << endl;
  cout << endl;


  //get the user's response
  cout << "Input your selection number: ";
  cin >> choice;
  while(!cin.good() || (choice<ADD || choice > EXIT)) {
    cin.clear();
    cin.ignore(1024, '\n');
    cout << "Input a VALID selection number: ";
    cin >> choice;
  }

  //return what the choice was in the proper datatype
  return static_cast<action>(choice);
}

void addRecord(vector<record> &db) {
  record temp; //maintain a temp record to read into
  bool markupredo = false; //assume the markups will be correct

  //output our current context and instruction
  cout << "Context: ADD RECORD" << endl;
  cout << endl;
  cout << "Please input values when prompted:" << endl;

  //What is the item ID
  cout << "What is the item ID (should be a single expression): ";
  cin >> temp.ID;
  cin.ignore(1024, '\n');

  //What is the item description
  cout << "What is the one-line item description?" << endl;
  getline(cin, temp.desc);

  //What is the item quantity
  cout << "What is the current quantity in inventory: ";
  cin >> temp.quantity;
  while (!cin.good() || temp.quantity<0) {
    cin.clear();
    cin.ignore(1024, '\n');
    cout << "Please input a VALID quantity: ";
    cin >> temp.quantity;
  }

  //Enter a large validation loop for the prices
  do {
    markupredo = false; //reset the check for the markup

    //Input the wholesale cost
    cout << "What is the wholesale cost (may not exceed $100.00): ";
    cin >> temp.wCost;

    //check if the input cost was acceptable
    while (!cin.good() || (temp.wCost > 100 || temp.wCost < 0)) {
      cin.clear(); //reset the stream error state
      cin.ignore(1024, '\n');
      cout << "Your wholesale cost was invalid, input VALID data: ";
      cin >> temp.wCost;
    }

    //spaceballs the comment!


    //input the retail cost
    cout << "What is the retail cost (may not exceed $100.00 or 75% markup): ";
    cin >> temp.rCost;

    //check if the input cost was acceptable
    while (!cin.good() || (temp.rCost > 100 || temp.rCost < 0)) {
      cin.clear(); //reset the stream error state
      cin.ignore(1024, '\n');
      cout << "Your retail cost was invalid, input VALID data: ";
      cin >> temp.wCost;
    }

    //if the computed markup is higher than 75% one of the costs is wrong
    //or if we would be losing money with the sale
    if (((temp.rCost - temp.wCost)/temp.wCost >0.75) || temp.rCost<temp.wCost) {
      cout << "You have input a markup of: " << ((temp.rCost-temp.wCost)/temp.wCost) << endl;
      cout << "Your cost markup is invalid!" << endl;
      cout << "Please adjust the wholesale and retail costs as necessary." << endl;
      markupredo = true;
    }
  } while (!cin.good() || markupredo); //re-run if cost is bad

  //assuming that all the above checks have passed, add the record to the vector
  db.push_back(temp);
}

string normalize(string s) {
  transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
}

int search(vector<record> &db, searchmode sMode=SEARCHDB) {
  int mode; //what type of search will we perform
  string query; //string to store the search query
  int recordLoc=0; //what is the record's location in the RAM db
  bool found=false; //a flag to know if we find something
  char confirm; //for edit/delete mode confirm that we are returning something

  //tell the user what mode they are in and ask them for what search to do
  cout << "Context: " << (sMode==SEARCHDB?"EDIT/DELETE SEARCH":"SEARCH") << endl;
  cout << "What type of search do you wish to perform?" << endl;
  cout << "1. ID search" << endl;
  cout << "2. Description Search" << endl;
  cin >> mode;

  //make sure they entered a search mode we actually support
  while(mode!=1 && mode!=2) {
    cout << "INVALID DATA!" << endl;
    cout << "What do you wish to search?" << endl;
    cout << "1. ID search" << endl;
    cout << "2. Description Search" << endl;
    cin >> mode;
    cin.clear();
    cin.ignore(1024, '\n');
  }

  //prompt for and retrieve the search string
  cout << "Input your search string below:" << endl;
  cin >> ws;
  getline(cin, query);
  cin.clear();
  query=normalize(query);

  //split based on what search mode we selected earlier
  switch(mode) {
  case 1: //ID Search
    for(; recordLoc<static_cast<int>(db.size()); recordLoc++) {
      if(normalize(db[recordLoc].ID).find(query)!=string::npos) {
	found=true;
	cout << "Record at location " << recordLoc << " matches:" << endl;
	dumpdb(db, recordLoc);
      }
    }
    break;
  case 2: //keyword search
    for(; recordLoc<static_cast<int>(db.size()); recordLoc++) {
      if(normalize(db[recordLoc].desc).find(query)!=string::npos) {
	found=true;
	cout << "Record at location " << recordLoc << " matches:" << endl;
	dumpdb(db, recordLoc);
      }
    }
    break;
  default:
    cerr << "A search mode select error has occured!" << endl;
    break;
  }

  //if we don't find anything, make sure that is made apparent
  if(!found) {
    cout << "Your search returned no results." << endl;
  } else if(sMode==EDITDEL) { //we found something, lets select and confirm
    cout << "Please select which record you wish to edit/delete: " << endl;
    cin >> recordLoc;
    cout << "You have selected: " << endl;
    dumpdb(db, recordLoc);
    cout << "Is this correct? y/n: " << endl;
    cin >> confirm;
    if(toupper(confirm) == 'Y') {
      return recordLoc; //if we don't return this, the only other option is -1
    }
  }
  return -1; //return not found or select cancelled
}

recordEdits editMenu() {
  int choice;

  cout << "Context: EDIT MENU" << endl;
  cout << "What do you wish to edit?" << endl;

  cout << "1. ID" << endl;
  cout << "2. Description" << endl;
  cout << "3. Quantity" << endl;
  cout << "4. Wholesale Cost" << endl;
  cout << "5. Retail Cost" << endl;

  cout << "Enter your selection: ";
  cin >> choice;

  while(0>choice || choice>5) {
    cout << "INVALID INPUT" << endl;
    cout << "1. ID" << endl;
    cout << "2. Description" << endl;
    cout << "3. Quantity" << endl;
    cout << "4. Wholesale Cost" << endl;
    cout << "5. Retail Cost" << endl;

    cout << "Enter your selection: ";
    cin >> choice;
  }
  cin.clear();
  cin.ignore(1024, '\n');

  return static_cast<recordEdits>(--choice);

}
void edit(vector<record> &db) {
  record temp;
  int editLoc;

  //tell the user what is about to happen
  cout << "Context: EDIT MODE" << endl;
  cout << "Please search for a record to edit." << endl;
  
  //call the search function in returnable mode
  editLoc = search(db, EDITDEL);
  if(editLoc==-1) {
    cout << "Edit cancelled or no record found." << endl;
    return;
  } else {
    temp=db[editLoc]; //retrieve the entire record
    switch(editMenu()) {
    case ID:
      cout << "Now editing the ID" << endl;
      cout << "Current is " << temp.ID << ", please input replacement" << endl;
      getline(cin, temp.ID);
      break;
    case DESC:
      cout << "Now editing the description" << endl;
      cout << "Current is " << temp.desc << ", please input replacement" << endl;
      getline(cin, temp.desc);
      break;
    case QUANT:
      cout << "Now editing the quantity" << endl;
      cout << "Current is " << temp.quantity << ", please input replacement" << endl;
      cin >> temp.quantity;
      while(temp.quantity<0 || temp.quantity>100) {
	cout << "INVALID DATA" << endl;
	cout << "Please input valid data (1-100): " << endl;
	cin >> temp.quantity;
      }
      break;
    case WCOST:
      cout << "Now editing wholesale cost" << endl;
      cout << "Input new cost" << endl;
      cin >> temp.wCost;
      //validate the new cost has all constraints satisfied
      while(temp.wCost>temp.rCost || temp.wCost<0 || temp.wCost>100 || ((temp.rCost - temp.wCost)/temp.wCost >0.75)) {
	cout << "Your cost adjustment would invalidate a price constraint!" << endl;
	cout << "Input a valid cost: ";
	cin >> temp.wCost;
      }
      break;
    case RCOST:
      cout << "Now editing retail cost" << endl;
      cout << "Input new cost" << endl;
      cin >> temp.rCost;

      //validate the new cost has all constraints satisfied
      while(temp.wCost>temp.rCost || temp.rCost<0 || temp.rCost>100 || ((temp.rCost - temp.wCost)/temp.wCost >0.75)) {
	cout << "Your cost adjustment would invalidate a price constraint!" << endl;
	cout << "Input a valid cost: ";
	cin >> temp.rCost;
      }
      break;
    default:
      cerr << "Something wierd happened" << endl;
      break;
    }
    
    db[editLoc]=temp; // write the corrected version back to the vector
  }
}

void deletedb(vector<record> &db) {
  int delLoc;

  cout << "You will now be given the opportunity to find a record to delete" << endl;
  delLoc = search(db, EDITDEL);
  if(delLoc==-1) {
    cout << "Record not found or deletion cancelled" << endl;
  } else {
    cout << "Now deleting this record:" << endl;
    dumpdb(db, delLoc); //show which record was deleted
    db.erase(db.begin()+delLoc); //actually delete it
  }
}

void report(vector<record> &db) {
  string title = "Inventory Report";
  int tQuantity =0;
  float tRetail=0, tWholesale=0;

  //output a centered title
  cout << endl << endl;
  for(int i=0; i<(80-title.size())/2; i++) {
    cout << "-";
  }
  cout << title;
  for(int i=0; i<(80-title.size())/2; i++) {
    cout << "-";
  }

  for(int i=0; i<db.size(); i++) {
    tQuantity += db[i].quantity;
    tWholesale += db[i].wCost;
    tRetail += db[i].rCost;
  }

  cout << "There are currently " << tQuantity << " items in inventory." << endl;
  cout << "These are valued at $" << tWholesale << endl;
  cout << "They can be sold for a total value of $" << tRetail << endl;
  cout << "Fun fact, if we sell it all now we can net $" << tRetail-tWholesale << endl;

  //output the end of report line
  title = "END OF REPORT";
  for(int i=0; i<(80-title.size())/2; i++) {
    cout << "-";
  }
  cout << title;
  for(int i=0; i<(80-title.size())/2; i++) {
    cout << "-";
  }
  cout << endl;
}

int main(int argc, char** argv) {
  vector<record> database;
  const string filename = "inventory.dat";

  if(loadDB(database, filename)) {
    while(true) {
      //db was loaded, maybe not correctly, but loaded
      //present menu and switch accordingly
      switch(rootMenu()) {
      case ADD:
	addRecord(database); //add a record to the end of the database
	saveDB(database, filename); //save the database to disk
	break;
      case SEARCH:
	search(database, SEARCHDB); //call search on the database
	break;
      case EDIT:
	edit(database); //edit the database
	saveDB(database, filename); //save the database to disk
	break;
      case DELETE:
	deletedb(database); //remove the record from the vector
	saveDB(database, filename); //save the database to disk
	break;
      case REPORT:
	report(database);
	break;
      case DUMP:
	dumpdb(database);
	break;
      case EXIT:
	return 0;
	break;
      default:
	cerr << "Engine in undefined state!" << endl;
	
	//dump the database to cerr for review/recovery
	dumpdb(database);
	
	//because the engine is in an undefined state, we will exit hard
	//it is important to note that this will not call any of the
	//object destructors, and shall only be used here as the only way
	//to get here is to pass data validation, and have a switch in a
	//state that is not accounted for by the enum being passed to it
	exit(255);
      }
    }
  } else {
    //some error occured
    cerr << "A critical error occured during database load-in!" << endl;
    return 1;
  }
  return 0;
}
