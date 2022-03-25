#include <iostream>
#include "Simulation.h"
using namespace std;

//I would like to use all 3 of my late days

int main(){
  Simulation* s1 = new Simulation();
  s1->boundaryMode();
  s1->runGame();
  delete s1;
}
