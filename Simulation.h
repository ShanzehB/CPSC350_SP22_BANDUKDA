#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include <exception>
#include "GameMode.h"
using namespace std;

class Simulation{
  static string to_lower(string s);
public:
  Simulation();//Constructor
  ~Simulation();//Destructor
  void boundaryMode();//
  void runGame();
private:
  char **arr;
  char **tempArr;
  string gameType;
  GameMode* gameMode;
  int downTime;
  bool isRunning;
};
