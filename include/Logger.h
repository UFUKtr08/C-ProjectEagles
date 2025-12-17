#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Logger {
private:
  static Logger *instance;
  ofstream logFile;

  // Singleton oldugu icin constructor private
  Logger();

public:
  // Kopya olusturmayi engelle
  Logger(const Logger &obj) = delete;
  void operator=(const Logger &) = delete;

  ~Logger();

  static Logger *getInstance();

  // Get current timestamp
  string getTimestamp();

  // Varsayilan parametre sadece header'da olur
  void log(const string &message, const string &level = "INFO");
};

#endif