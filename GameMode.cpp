#include "GameMode.h"
using namespace std;


GameMode::GameMode(int rows, int columns, float density){
  m_rows = rows;
  m_columns = columns;
  m_density = density;
}

GameMode::~GameMode(){
  //destructor
}

GameMode::GameMode(){
  //constructor
}

void GameMode::randArray(){
  float r;
  arr = new char*[m_rows];
  	for (int i = 0; i < m_rows; ++i){//this allocates the memory for the 2D array
  		arr[i] = new char[m_columns];
  	}
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_columns; j++){
        r = ((float)rand()/(float)RAND_MAX);
        if(r <= m_density){
          arr[i][j] = 'X';
        }else{
          arr[i][j] = '-';
        }
    }
  }
}

void GameMode::fileArray(string fileName){
  m_generation = 1;
  ifstream inFile;
  int rows;
  int columns;
  string line;
  bool first = true;
  bool second = false;
  inFile.open(fileName);
  string temp;
  while(getline(inFile, line)){
    temp = line;
    if(first){
      m_rows = stoi(temp);
      first = false;
      second = true;
      continue;
    }
    if(second){
      m_columns = stoi(temp);
      second = false;
      inFile.close();
      break;
    }
  }
  // dynamic allocation
  arr = new char*[m_rows];
  for(int i = 0; i < m_rows; ++i){
      arr[i] = new char[m_columns];
  }
  inFile.open(fileName);
  string currentLine;
  getline(inFile, currentLine);
  getline(inFile, currentLine);
  int counter = 0;
  while(getline(inFile, currentLine)){
    if(currentLine.length() == 0)
      break;
    for(int i = 0; i < currentLine.length(); ++i){
      arr[counter][i] = (currentLine[i]);
    }
    counter++;
  }
}

void GameMode::printArray(){
  cout << "Generation: " << genCounter << endl;
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_columns; j++){
      cout << arr[i][j] << '-';
		}
		cout << "\n";
  }
}

string GameMode::writeArray(){
  string str = "";
  str += "Generation: ";
  str += genCounter;
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_columns; j++){
      str += arr[i][j];
      str += '-';
		}
		str += "\n";
  }
  return str;
}

void GameMode::printFile(string outputFile){
  ofstream out_file;
  ifstream in_file;
  string line;
  out_file.open(outputFile);
  out_file << writeArray() << endl;
  out_file.close();
}

void GameMode::classicMode(int transitionType){
  cout << "in classic mode" << endl;
  int neighbor_count = 0;
  cout << "before make temp" << endl;
  tempArr = new char*[m_rows];
  // init tempArr to correct dimensions
  for(int i = 0; i < m_rows; ++i){
    tempArr[i] = new char[m_columns];
  }
  // fill tempArr
  for(int i = 0; i < m_rows; ++i){
    for(int j = 0; j < m_columns; ++j){
      tempArr[i][j] = arr[i][j];
    }
  }
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_columns; j++){
      if(i == 0 && j == 0){
        if(arr[i][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          neighbor_count += 1;
        }else{
          continue;
        }
      }
      else if(i == m_rows-1 && j == 0){
          if(arr[i-1][j] == 'X'){
            neighbor_count += 1;
          }else if(arr[i][j+1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i-1][j+1] == 'X'){
            neighbor_count += 1;
          }else{
            continue;
          }
      }else if(i == 0 && j == m_columns-1){

          if(arr[i][j-1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i+1][j-1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i+1][j] == 'X'){
            neighbor_count += 1;
          }else{
            continue;
          }
      }else if(i == m_rows-1 && j == m_columns-1){
          if(arr[i][j-1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i-1][j-1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i-1][j] == 'X'){
            neighbor_count += 1;
          }else{
            continue;
          }
      }else if(i != 0 && i != m_rows-1 && j == 0){
          // TODO - seg fault
          if(arr[i-1][j] == 'X'){
            neighbor_count += 1;
          }else if(arr[i+1][j] == 'X'){ // error
            neighbor_count += 1;
          }else if(arr[i-1][j+1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i][j+1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i+1][j+1] == 'X'){
            neighbor_count += 1;
          }else{
            continue;
          }
      }else if(j != 0 && j != m_columns-1 && i == 0){
          if(arr[i][j-1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i+1][j-1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i+1][j] == 'X'){
            neighbor_count += 1;
          }else if(arr[i][j+1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i+1][j+1] == 'X'){
            neighbor_count += 1;
          }else{
            continue;
          }
      }else if(j != 0 && j != m_columns-1 && i == m_rows-1){
          if(arr[i][j-1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i-1][j-1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i-1][j] == 'X'){
            neighbor_count += 1;
          }else if(arr[i-1][j+1] == 'X'){
            neighbor_count += 1;
          }else if(arr[i][j+1] == 'X'){
            neighbor_count += 1;
          }else{
            continue;
          }
      }else if(i != 0 && i != m_rows-1 && j != 0 && j != m_columns-1){
        if(arr[i][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j-1] == 'X'){
          neighbor_count += 1;
        }
      }else{
      }
      if(neighbor_count <= 1){
        tempArr[i][j] == '-';
      }else if(neighbor_count == 2){
        continue;
      }else if(neighbor_count == 3){
        tempArr[i][j] == 'X';
      }else if(neighbor_count >= 4){
        tempArr[i][j] == '-';
      }else{
        continue;
      }
    }
  }
  printArray();
  genCounter += 1;
  // if(compareGen() == true){
  //
  // }else{
  //   continue;
  // }
  arr = tempArr;
  delete tempArr;
  if(transitionType == 0){// no transition
    sleepMode();
  }
  else if(transitionType == 1){
    printFile(m_outputFile);

  }
}

void GameMode::donutMode(int transitionType){
  int neighbor_count = 0;
  for(int i = 0; i < m_rows; ++i){
    tempArr[i] = new char[m_columns];
  }
  // fill tempArr
  for(int i = 0; i < m_rows; ++i){
    for(int j = 0; j < m_columns; ++j){
      tempArr[i][j] = arr[i][j];
    }
  }
  for(int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_columns; j++){
      //top left case
      if(i == 0 && j == 0){
        if(arr[i][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[0][m_columns-1] == 'X'){//the one on the end on the top [0,m_columns]
          neighbor_count += 1;
        }else if(arr[1][m_columns-1] == 'X'){//the one underneath the one on the top
          neighbor_count += 1;
        }else if(arr[m_rows-1][0] == 'X'){// the one one the bottom [m_rows,0]
          neighbor_count += 1;
        }else if(arr[m_rows-1][j+1] == 'X'){//the one opposite to [i,j+1]
          neighbor_count += 1;
        }else if(arr[m_rows-1][m_columns-1] == 'X'){// diagonal to [i,j] so [m_rows,m_columns]
          neighbor_count += 1;
        }
      } //top right case
      else if(i == 0 && j == m_columns-1){
        if(arr[i][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[0][0] == 'X'){//arr[0,0]
          neighbor_count += 1;
        }else if(arr[1][0] == 'X'){//arr below arr[0,0]
          neighbor_count += 1;
        }else if(arr[m_rows-1][0] == 'X'){//arr[m_rows,0]
          neighbor_count += 1;
        }else if(arr[m_rows-1][m_columns-1] == 'X'){//arr[m_rows,m_columns]
          neighbor_count += 1;
        }else if(arr[m_rows-1][m_columns-1] == 'X'){//arr[m_rows, m_columns -1]
          neighbor_count += 1;
        }
      }//bottom left case
      else if(i == m_rows-1 && j == 0){
        if(arr[i-1][j]){
          neighbor_count += 1;
        }else if(arr[i-1][j+1]){
          neighbor_count += 1;
        }else if(arr[i][j+1]){
          neighbor_count += 1;
        }else if(arr[m_rows-1][m_columns-1] == 'X'){//arr[not 0 or m_rows, j = m_columns]
          neighbor_count += 1;
        }else if(arr[m_rows-1][m_columns-1]){//arr[m_rows,m_columns]
          neighbor_count += 1;
        }else if(arr[0][0] == 'X'){//arr[0,0]
          neighbor_count += 1;
        }else if(arr[0][1] == 'X'){//one next to arr[0,0]
          neighbor_count += 1;
        }else if(arr[0][m_columns-1]){//arr[0,m_columns]
          neighbor_count += 1;
        }
      }//bottom left
      else if(i == m_rows-1 && j == m_columns-1){
        if(arr[i][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[0][m_columns-1] == 'X'){//arr[0,m_columns]
          neighbor_count += 1;
        }else if(arr[0][0] == 'X'){//arr[0,0]
          neighbor_count += 1;
        }else if(arr[m_rows-1][0] == 'X'){//arr[m_rows,0]
          neighbor_count += 1;
        }else if(arr[m_rows-1][0]){//arr[row above the last row,0]
          neighbor_count += 1;
        }else if(arr[0][m_columns-1] == 'X'){//arr[0, one before m_columns]
          neighbor_count += 1;
        }
      }//middle top ones
      else if(i == 0 && j != 0 && j != m_columns-1){
        if(arr[i][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[m_rows-1][j-1] == 'X'){//arr[m_rows,j-1]
          neighbor_count += 1;
        }else if(arr[m_rows-1][j] == 'X'){//arr[m_rows,j]
          neighbor_count += 1;
        }else if(arr[m_rows-1][j+1] == 'X'){//arr[m_rows,j+1]
          neighbor_count += 1;
        }
      }//middle side on the left
      else if(i != 0 && i != m_rows-1 && j == 0){
        if(arr[i-1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][m_columns-1] == 'X'){//above but on the other side
          neighbor_count += 1;
        }else if(arr[i][m_columns-1] == 'X'){//same thing but on other side
          neighbor_count += 1;
        }else if(arr[i+1][m_columns-1] == 'X'){//one below but on other side
          neighbor_count += 1;
        }
      }//middle on the right
      else if(i != 0 && i != m_rows-1 && j == m_columns-1){
        if(arr[i-1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][0] == 'X'){//above but on the other side
          neighbor_count += 1;
        }else if(arr[i][0] == 'X'){//same thing but on other side
          neighbor_count += 1;
        }else if(arr[i+1][0] == 'X'){//one below but on other side
          neighbor_count += 1;
        }
      }//middle top
      else if(i == 0 && j != 0 && j != m_columns-1){
        if(arr[i][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[m_rows-1][j-1] == 'X'){//bottom to the left
          neighbor_count += 1;
        }else if(arr[m_rows-1][j] == 'X'){//bottom middle
          neighbor_count += 1;
        }else if(arr[m_rows-1][j+1] == 'X'){//bottom to the right
          neighbor_count += 1;
        }
      }//middle bottom
      else if(i == m_rows-1 && j != 0 && j != m_columns-1){
        if(arr[i][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[0][j-1] == 'X'){//top the the left
          neighbor_count += 1;
        }else if(arr[0][j] == 'X'){//top middle
          neighbor_count += 1;
        }else if(arr[0][j+1] == 'X'){//top to the right
          neighbor_count += 1;
        }
      }//not the border now
      else if(i != 0 && i != m_rows-1 && j != 0 && j != m_columns-1){
        if(arr[i][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i-1][j] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          neighbor_count += 1;
        }
      }

      if(neighbor_count <= 1){
        tempArr[i][j] == '-';
      }else if(neighbor_count == 2){
        continue;
      }else if(neighbor_count == 3){
        tempArr[i][j] == 'X';
      }else if(neighbor_count >= 4){
        tempArr[i][j] == '-';
      }else{
        continue;
      }
    }
  }
  printArray();//do all
  genCounter += 1;
  // if(compareGen() == true){
  //
  // }else{
  //   continue;
  // }
  arr = tempArr;
  delete tempArr;
  if(transitionType == 0){// no transition
    sleepMode();
  }
  else if(transitionType == 1){
    printFile(m_outputFile);
  }
}

void GameMode::mirrorMode(int transitionType){
  for(int i = 0; i < m_rows; ++i){
    tempArr[i] = new char[m_columns];
  }
  // fill tempArr
  for(int i = 0; i < m_rows; ++i){
    for(int j = 0; j < m_columns; ++j){
      tempArr[i][j] = arr[i][j];
    }
  }
  int neighbor_count = 0;
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_columns; j++){
      if(i != 0 && i != m_rows-1 && j != 0 && j != m_columns-1){
        if(arr[i][j-1] == 'X'){
          if(i != 0 && i != m_rows-1 && j - 1 == 0){
            neighbor_count += 1;
          }else if(i != 0 && i != m_rows-1 && j - 1 == m_columns-1){
            neighbor_count += 1;
          }else if(i == m_rows-1 && j - 1 != 0 && j - 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i == m_rows-1 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i == m_rows-1 && j - 1 == m_columns-1){
            neighbor_count += 2;
          }else if(j - 1 != 0 && j - 1 != m_columns-1 && i == 0){
            neighbor_count += 1;
          }else if(i == 0 && j - 1 == m_columns-1){
            neighbor_count += 2;
          }else if(i == 0 && j - 1 == 0){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          if(i != 0 && i != m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 1;
          }else if(i == m_rows-1 && j + 1 != 0 && j + 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i == m_rows-1 && j + 1 == 0){
            neighbor_count += 2;
          }else if(i == m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }else if(j + 1 != 0 && j + 1 != m_columns-1 && i == 0){
            neighbor_count += 1;
          }else if(i == 0 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }else if(i == 0 && j + 1 == 0){
            neighbor_count += 2;
          }else if(i != 0 && i != m_rows-1 && j + 1 == 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          if(i + 1 == m_rows-1 && j != 0 && j != m_columns-1){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j == 0){
            neighbor_count += 2;
          }else if(i + 1 == m_rows-1 && j == m_columns-1){
            neighbor_count += 2;
          }else if(j != 0 && j != m_columns-1 && i + 1 == 0){
            neighbor_count += 1;
          }else if(i + 1 == 0 && j == m_columns-1){
            neighbor_count += 2;
          }else if(i + 1 == 0 && j == 0){
            neighbor_count += 2;
          }else if(i + 1 != 0 && i + 1 != m_rows-1 && j == 0){
            neighbor_count += 1;
          }else if(i + 1 != 0 && i + 1 != m_rows-1 && j == m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          if(i + 1 == m_rows-1 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i + 1 == m_rows-1 && j - 1 == m_columns-1){
            neighbor_count += 2;
          }else if(j - 1 != 0 && j - 1 != m_columns-1 && i + 1 == 0){
            neighbor_count += 1;
          }else if(i + 1 == 0 && j - 1 == m_columns-1){
            neighbor_count += 2;
          }else if(i + 1 == 0 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i + 1 != 0 && i + 1 != m_rows-1 && j - 1 == 0){
            neighbor_count += 1;
          }else if(i + 1 != 0 && i + 1 != m_rows-1 && j - 1 == m_columns-1){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j - 1 != 0 && j - 1 != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          if(i + 1 == m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }else if(j + 1 != 0 && j + 1 != m_columns-1 && i + 1 == 0){
            neighbor_count += 1;
          }else if(i + 1 == 0 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }else if(i + 1 == 0 && j + 1 == 0){
            neighbor_count += 2;
          }else if(i + 1 != 0 && i + 1 != m_rows-1 && j + 1 == 0){
            neighbor_count += 1;
          }else if(i + 1 != 0 && i + 1 != m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j + 1 != 0 && j + 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j + 1 == 0){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j] == 'X'){
          if(j != 0 && j != m_columns-1 && i - 1 == 0){
            neighbor_count += 1;
          }else if(i - 1 == 0 && j == m_columns-1){
            neighbor_count += 2;
          }else if(i - 1 == 0 && j == 0){
            neighbor_count += 2;
          }else if(i - 1 != 0 && i - 1 != m_rows-1 && j == 0){
            neighbor_count += 1;
          }else if(i - 1 != 0 && i - 1 != m_rows-1 && j == m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == m_rows-1 && j != 0 && j != m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == m_rows-1 && j == 0){
            neighbor_count += 2;
          }else if(i - 1 == m_rows-1 && j == m_columns-1){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j+1] == 'X'){
          if(i - 1 == 0 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }else if(i - 1 == 0 && j + 1 == 0){
            neighbor_count += 2;
          }else if(i - 1 != 0 && i - 1 != m_rows-1 && j + 1 == 0){
            neighbor_count += 1;
          }else if(i - 1 != 0 && i - 1 != m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == m_rows-1 && j + 1 != 0 && j + 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == m_rows-1 && j + 1 == 0){
            neighbor_count += 2;
          }else if(i - 1 == m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }else if(j + 1 != 0 && j + 1 != m_columns-1 && i - 1 == 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j-1] == 'X'){
          if(i - 1 == 0 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i - 1 != 0 && i - 1 != m_rows-1 && j - 1 == 0){
            neighbor_count += 1;
          }else if(i - 1 != 0 && i - 1 != m_rows-1 && j - 1 == m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == m_rows-1 && j - 1 != 0 && j - 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == m_rows-1 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i - 1 == m_rows-1 && j - 1 == m_columns-1){
            neighbor_count += 2;
          }else if(j - 1 != 0 && j - 1 != m_columns-1 && i - 1 == 0){
            neighbor_count += 1;
          }else if(i - 1 == 0 && j - 1 == m_columns-1){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }
      }else if(i == 0 && j == 0){
        if(arr[i][j+1] == 'X'){
          if(i == 0 && j != 0 && j != m_columns-1){
            neighbor_count += 1;
          }else if(i == 0 && j == m_columns-1){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          if(i + 1 != 0 && i + 1 != m_rows-1 && j == 0){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j == 0){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          if(i + 1 != m_rows-1 && i + 1 != 0 && j + 1 != m_columns-1 && j + 1 != 0){
            continue;
          }else if(i + 1 == m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }
      }else if(i == m_rows-1 && j == 0){
        if(arr[i-1][j] == 'X'){
          if(i - 1 != 0 && i - 1 != m_rows-1 && j == 0){
            neighbor_count += 1;
          }else if(i - 1 == 0 && j == 0){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j+1] == 'X'){
          if(i - 1 != 0 && i - 1 != m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == 0 && j - 1 == m_columns-1){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          if(i == m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }if(i - 1 == m_rows-1 && j - 1 != m_columns-1 && j - 1 != 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }
      }else if(i == 0 && j == m_columns-1){
        if(arr[i][j-1] == 'X'){
          if(i == 0 && j - 1 != 0 ){
          neighbor_count += 1;
          }else if(i == 0 && j - 1 == 0){
          neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          if(i + 1 != 0 && i + 1 != m_rows-1 && j - 1 == 0){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j - 1 != 0){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j - 1 == 0){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          if(i + 1 != m_rows-1 && j == m_columns-1){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j == m_columns-1){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }
      }else if(i == m_rows-1 && j == m_columns-1){
        if(arr[i-1][j-1] == 'X'){
          if(i - 1 != 0 && i - 1 != m_rows && j - 1 != 0 && j - 1 != m_columns-1){
            continue;
          }else if(i - 1 == 0 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i - 1 == 0 and j - 1 != 0 && j - 1 != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i][j-1] == 'X'){
          if(i == m_rows-1 && j - 1 != 0 && j - 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i == m_rows-1 && j - 1 == 0){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j] == 'X'){
          if(i - 1 == 0 && j == m_columns-1){
            neighbor_count += 2;
          }else if(i - 1 != 0 && j == m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }
      }else if(i == 0 && j != 0 && j != m_columns-1){
        if(arr[i][j-1] == 'X'){
          if(i == 0 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i == 0 && j - 1 != 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          if(i + 1 == m_rows-1 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i + 1 == m_rows-1 && j - 1 != 0 && j - 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i + 1 != m_rows-1 && i + 1 != 0 && j - 1 == 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          if(i + 1 != m_rows-1 && j != 0 && j != m_columns-1){
            continue;
          }else if(i + 1 == m_rows-1 && j != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          if(i + 1 != m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 1;
          }else if(i + 1 == m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          if(i == 0 && j + 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i == 0 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }
          neighbor_count += 1;
        }
      }else if(i == m_rows-1 && j != 0 && j != m_columns-1){
        if(arr[i][j-1] == 'X'){
          if(i == m_rows-1 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i + 1 == m_rows-1 && j - 1 != 0 && j - 1 != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j-1] == 'X'){
          if(i - 1 == 0 && j - 1 == 0){//corner
            neighbor_count += 2;
          }else if(i - 1 == 0 && j - 1 != 0){//middkles
            neighbor_count += 1;
          }else if(i - 1 != 0 && j - 1 == 0){//againt the side
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          if(i == m_rows-1 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }else if(i == m_rows-1 && j + 1 != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j+1] == 'X'){
          if(i - 1 == 0 && j + 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i == 0 && j + 1 == m_columns-1){
            neighbor_count += 2;
          }else if(i - 1 != 0 && j + 1 == m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j] == 'X'){
          if(i - 1 == 0 && j != 0 && j != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }
      }else if(i != 0 && i != m_rows-1 && j == 0){
        if(arr[i-1][j] == 'X'){
          if(i - 1 == 0 && j == 0){
            neighbor_count += 2;
          }else if(i - 1 != 0 && j == 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          if(i + 1 == m_rows-1 && j == 0){
            neighbor_count += 2;
          }else if(i - 1 != m_rows-1 && j == 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j+1] == 'X'){
          if(i - 1 == 0 && j == m_columns-1){
            neighbor_count += 2;
          }else if(i - 1 != 0 && j == m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == 0 && j != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j+1] == 'X'){
          if(i - 1 == m_rows-1 && j == m_columns-1){
            neighbor_count += 2;
          }else if(i - 1 != m_rows-1 && j == m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 == m_rows-1 && j != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i][j+1] == 'X'){
          if(i - 1 != m_rows-1 && j == m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }
      }else if(i != 0 && i != m_rows-1 && j == m_columns-1){
        if(arr[i-1][j-1] == 'X'){
          if(i - 1 == 0 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i - 1 == 0 && j != 0 && j != m_columns-1){
            neighbor_count += 1;
          }else if(i - 1 != 0 && j == 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j-1] == 'X'){
          if(i + 1 == 0 && j - 1 == 0){
            neighbor_count += 2;
          }else if(i + 1 == 0 && j - 1 != 0 && j - 1 != m_columns-1){
            neighbor_count += 1;
          }else if(i + 1 != 0 && j - 1 == 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i-1][j] == 'X'){
          if(i - 1 == 0 && j == m_columns-1){
            neighbor_count += 2;
          }else if(i - 1 == 0 && j != m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i+1][j] == 'X'){
          if(i + 1 == m_rows-1 && j == m_columns-1){
            neighbor_count += 2;
          }else if(i + 1 != m_rows-1 && j == m_columns-1){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }else if(arr[i][j-1] == 'X'){
          if(i != 0 && j - 1 == 0){
            neighbor_count += 1;
          }
          neighbor_count += 1;
        }
        }
        if(neighbor_count <= 1){
          tempArr[i][j] == '-';
        }else if(neighbor_count == 2){
          continue;
        }else if(neighbor_count == 3){
          tempArr[i][j] == 'X';
        }else if(neighbor_count >= 4){
          tempArr[i][j] == '-';
        }else{
          continue;
        }
      }
    }
    printArray();
    genCounter += 1;
    // if(compareGen() == true){
    //
    // }else{
    //
    // }
    arr = tempArr;
    delete tempArr;
    if(transitionType == 0){// no transition
      sleepMode();
    }
    else if(transitionType == 1){
      printFile(m_outputFile);
    }
  }

void GameMode::sleepMode(){
  while(true){
    string in;
    cout << "Press the Enter key to continue." << endl;
    getline(cin,in);
    if(in.empty()){
      break;
    }else{
      cout << "Error: invalid input" << endl;
      continue;
    }
  }
}

bool GameMode::compareGen(){
  int count = 0;
  for(int i = 0; i < m_rows; ++i){
    for(int j = 0; j < m_columns; ++j){
      if(arr[i][j] != tempArr[i][j]){
        count += 1;
        break;
      }
    }
  }
  return (count == 0);
}

void GameMode::setFile(string file){
  m_outputFile = file;
}

int GameMode::getRows(){
  return m_rows;
}

int GameMode::getColumns(){
  return m_columns;
}

char** GameMode::getArray(){
  return arr;
}
