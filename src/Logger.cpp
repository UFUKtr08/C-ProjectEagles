#include "../include/Logger.h"

// Static degisken baslatma
Logger *Logger::instance = NULL;

Logger::Logger() { logFile.open("MSH_Log.txt", ios::app); }

Logger::~Logger() {
  if (logFile.is_open()) {
    logFile.close();
  }
}

Logger *Logger::getInstance() {
  if (instance == NULL) {
    instance = new Logger();
  }
  return instance;
}

void Logger::log(const string &message, const string &level) {
  if (logFile.is_open()) {
    logFile << "[" << level << "] " << message << endl;
    // Konsolda da gorelim
    cout << "[" << level << "] " << message << endl;
  }
}