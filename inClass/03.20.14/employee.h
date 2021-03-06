#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <cstring>
using namespace std;

class Employee {
 private:
  char name[20];
  int ID;
  char hiredate[9];

 public:
  Employee();
  Employee(char*, int, char*);
  ~Employee() {};


  void setName(char* n) { strncpy(name, n, 19); }

  void setID(int i) { ID = i; }

  void setHireDate(char* d) { strcpy(hiredate, d); }

  char* getName() { return name; }

  int getID() { return ID; }

  char* getHireDate() { return hiredate; }
};
#endif
