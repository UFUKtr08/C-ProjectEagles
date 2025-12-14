#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Logger.h" // Loglama yapiyorsa lazim olabilir
#include <iostream>
#include <string>

using namespace std;

class InputHandler {
public:
  // Bu fonksiyonlar InputHandler.cpp'de tanimli olmali
  int getIntInput(int min, int max, string prompt);
  string getStringInput(string prompt);
  char getCharInput(string prompt);
  void waitPressEnter();
};

#endif