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

string Logger::getTimestamp() {
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  char buffer[25];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  return string(buffer);
}

void Logger::log(const string &message, const string &level) {
  if (logFile.is_open()) {
    string timestamp = getTimestamp();
    logFile << "[" << timestamp << "][" << level << "] " << message << endl;
    cout << "[" << timestamp << "][" << level << "] " << message << endl;
  }
}