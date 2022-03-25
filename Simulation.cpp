#include "Simulation.h"
#include "GameMode.h"
using namespace std;

//I would like to use all 3 of my late days

Simulation::Simulation(){
  //constructor
  isRunning = true;
  // get game parameters
  int rows;
  int columns;
  float density;//change to float
  int configResponse;
  cout << "Hello, do you wish to start a random configuration or flat-file configuration?\nFor random type 1 for flat-file type 2." << endl;
  while(true){
    cin >> configResponse;
    if(configResponse == 1 || 2){
      if(configResponse == 1){
        cout << "Enter the amount of rows and columns desired for the game seperated by a space: " << endl;
        cin >> rows;
        cin >> columns;
        cout << "Enter the density desired for the game(needs to be between 0 & 1): " << endl;
        cin >> density;
        gameMode = new GameMode(rows,columns,density);
        gameMode->randArray();
      }else{
        string fileName = "";
        cout << "Enter file name: " << endl;
        cin >> fileName;
        gameMode->fileArray(fileName);//make a file class for error handlings
      }
      break;
    }
    cout << "Try again! For random type 1 for flat-file type 2. " << endl;
    cin >> configResponse;
  }
  // ask user for input file
}

Simulation::~Simulation(){
  //Destructor
}


void Simulation::boundaryMode(){
  int transitionType;
  cout << "Now select your game mode: Classic, Donut, or Mirror. Type in your choice." << endl;
  cin >> gameType;
  int downTime;
  string fileName;
  cout << "Would you like to set the game so that you have to press the enter key in order to go to the next generation?\n If so, type '0'.\n If you want to output to a file type '1'." << endl;
  cin >> downTime;
  if(downTime == 1){
    cout << "Enter file name: " << endl;
    cin >> fileName;
    gameMode->setFile(fileName);
  }
  if(to_lower(gameType) == "classic"){
    gameMode->classicMode(downTime);
  }else if(to_lower(gameType) == "donut"){
    gameMode->donutMode(downTime);
  }else if(to_lower(gameType) == "mirror"){
    gameMode->mirrorMode(downTime);
  }else{
    cout << "Try again! Type in the mode." << endl;
    cin >> gameType;
  }
}

string Simulation::to_lower(string s){
     for(char &c : s)
         c = tolower(c);
     return s;
}

void Simulation::runGame(){
  int count;
  while(isRunning){
    // reset array
    arr = gameMode->getArray();
    // init tempArr
    for(int i = 0; i < gameMode->getRows(); ++i){
      tempArr[i] = new char[gameMode->getColumns()];
    }
    // fill tempArr
    for(int i = 0; i < gameMode->getRows(); ++i){
      for(int j = 0; j < gameMode->getColumns(); ++j){
        tempArr[i][j] = arr[i][j];
      }
    }
    for(int i = 0; i < gameMode->getRows(); ++i){
      for(int j = 0; j < gameMode->getColumns(); ++j){
        if(tempArr[i][i] != arr[i][j]){
          count += 1;
          break;
        }
      }
    }
    if(count == 0){
      isRunning == false;
    }
    // compare ~ check if is the same
        // if same, game is over --> isRunning = false
  }
  //
}
