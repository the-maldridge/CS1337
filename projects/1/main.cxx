/*
Geometry Calculator

Calculates the volume of the following geometric figures
Dumbell
Spear
Axle

*/

#include <iostream>
#include <cmath>
#include <ctype.h>
#include <iomanip>
#define PI 3.14159265359

using namespace std;

int menu() {
  int choice;
  //Show a menu
  cout << "Geometry Calculator" << endl;
  cout << "Please choose one of the following:" << endl;
  cout << "1: Dumbell (2 spheres connected by a rod)" << endl;
  cout << "2: Spear (2 cones connected by a rod)" << endl;
  cout << "3: Axle (2 cylinders connected by a rod" << endl;
  cout << "4: Exit" << endl;
  cout << "Input your choice: ";
  cin >> choice;

  //retrive and validate a choice from the menu
  while(!(0<choice || choice>4)) {
    cout << "Your choice was invalid, please input a valid choice" << endl;
    cin >> choice;
  }
  return choice;
}

void getAndValidateInput(float &input) {
  //read some input and check if it is valuable
  cout << "Please enter your input (Valid between 0 and 1 million): ";
  cin >> input;

  //if the user can't read, make them send more input
  while (!(0<input || input < 1000000)) { //check if input is out of bounds
    cout << "Input out of bounds, try again: ";
    cin >> input;
  }
}

float calVSphere(float r) {
  //compute the volume of a sphere given radius
  float volume;
  volume = (4 * PI * pow(r,3)) / 3;
  return volume;
}

float calVCone(float r, float h) {
  //compute the volume of a cone given radius and height
  float volume;
  volume = (PI * pow(r,2) * h) / 3;
  return volume;
}

float calVCylinder(float r, float h) {
  //compute the volume of a cylinder given radius and height
  float volume;
  volume  = PI * pow(r,2) * h;
  return volume;
}

void axle() {
  float endR=1, endH=1, midR=1, midH=1, endV=1, midV=1, totalV=1;
  //loop until the user gets the parameters right
  while (endR/2 < midR) { 
    cout << "The mid cylinder can't exceed half the radius of the ends!" << endl;
    cout << "What is the radius of the center rod?" << endl;
    getAndValidateInput(midR);
    cout << "What is the radius of the end cylinder?" << endl;
    getAndValidateInput(endR);
  }
 
  //get the remaining parameters
  cout << "What is the height of the end cylinders?" << endl;
  getAndValidateInput(endH);
  cout << "What is the height of the mid-cylinder?" << endl;
  getAndValidateInput(midH);

  //calculate the volume of the components
  midV = calVCylinder(midR, midH);
  endV = calVCylinder(endR, endH);

  //calculate the total volume
  totalV = endV*2 + midV;

  //send output of the figure
  cout << endl << endl << endl;
  cout << "Your axle with dimensions of:" << endl;
  cout << "Center rod radius: " << midR << endl;
  cout << "Center rod length: " << midH << endl;
  cout << "End rod radius: " << endR << endl;
  cout << "End rod height: " << endH << endl;
  cout << "Has a total volume of: " << totalV << endl;
  cout << endl << endl << endl;
}

void spear() {
  float rodR=1, rodH=1, rodV=1, coneR=2, coneH=1, coneV=1, totalV=1;

  while(rodR != coneR) { //loop until the user gets the radius right
    cout << "The rod and cone must have the same radius!" << endl;
    cout << "What is the radius of the rod?" << endl;
    getAndValidateInput(rodR);
    cout << "What is the radius of the cones" << endl;
    getAndValidateInput(coneR);
  }
  //get the remaining parameters
  cout << "What is the height of the cones?" << endl;
  getAndValidateInput(coneH);
  cout << "What is the height of the rod?" << endl;
  getAndValidateInput(rodH);

  //calculate the volume of the components
  rodV = calVCylinder(rodR, rodH);
  coneV = calVCone(coneR, coneH);

  //calculate the total volume
  totalV = rodV + 2*coneV;

  //send some output
  cout << endl << endl << endl;
  cout << "Your spear of dimensions:" << endl;
  cout << "Rod radius: " << rodR << endl;
  cout << "Rod height: " << rodH << endl;
  cout << "Cone radius: " << coneR << endl;
  cout << "Cone height: " << coneH << endl;
  cout << "Has a total volume of: " << totalV << endl;
  cout << endl << endl << endl;
}

void dumbbell() {
  float sphereR=1, cylR=1, cylH=1, sphereV=1, cylV=1, totalV=1;
  //loop until the radius condition is met
  while (sphereR/2<cylR){
    cout << "The sphere must have a radius at least twice the rod's!" << endl;
    cout << "What is the radius of the sphere? ";
    getAndValidateInput(sphereR);
    cout << "What is the radius of the rod? ";
    getAndValidateInput(cylR);
  }

  //get the remaining parameters
  cout << "What is the length of the rod? ";
  getAndValidateInput(cylH);

  //calculate the volume
  cylV = calVCylinder(cylR, cylH);
  sphereV = calVSphere(sphereR);

  //sum the components to the final volume
  totalV = sphereV * 2 + cylV;

  //send some output
  cout << endl << endl << endl;
  cout << "Your dumbbell of dimensions:" << endl;
  cout << "Rod radius: " << cylR << endl;
  cout << "Rod height: " << cylH << endl;
  cout << "Sphere radius: " << sphereR << endl;
  cout << "Has a total volume of: " << totalV << endl;
  cout << endl << endl << endl;
}


int main(int argc, char** argv) {
  cout << setprecision(3) << fixed; //Set the output stream parameters
  while(true) {
    switch(menu()) { //Figure out which case we are transfering to
    case 1: //dumbell
      dumbbell();
      break;
    case 2: //spear
      spear();
      break;
    case 3: //axle
      axle();
      break;
    case 4: //exit
      return 0;
    }
  }
}
