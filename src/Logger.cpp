#include "../include/Logger.h"
#include <ctime>
Logger* Logger::instance = NULL;
Logger::Logger() {
    logFile.open("MSH_Log.txt", ios::app);
    if (logFile.is_open()) log("--- SYSTEM START ---");
}
Logger::~Logger() {
    if (logFile.is_open()) {
        log("--- SYSTEM SHUTDOWN ---");
        logFile.close();
    }
}
Logger* Logger::getInstance() {
    if (instance == NULL) instance = new Logger();
    return instance;
}
void Logger::log(const string& message) {
    if (logFile.is_open()) {
        logFile << "[LOG] " << message << endl;
        cout << "[LOG] " << message << endl;
    }
}