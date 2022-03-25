#ifndef GAMEMODE_H
#define GAMEMODE_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include <exception>
#include <unistd.h>
using namespace std;


class GameMode{
public:
  char **arr;
  char **tempArr;
  GameMode();//Constructor
  GameMode(int rows, int columns, float density);
  ~GameMode();//Destructor
  void randArray();
  void fileArray(string fileName);
  void printArray();
  void printFile(string file);
  void sleepMode();
  bool compareGen();
  void classicMode(int transitionType);//
  void donutMode(int transitionType);//
  void mirrorMode(int transitionType);
  void setFile(string file);
  string writeArray();
  int getRows();
  int getColumns();
  char** getArray();

private:
  string gameMode;
  int m_rows;
  int m_columns;
  float m_density;
  string m_fileName;
  string m_outputFile;
  int m_generation;
  int genCounter = 0;
};
#endif
