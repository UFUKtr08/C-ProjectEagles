#include "../include/Logger.h"
#include <iostream>

Logger* Logger::instance = NULL;

Logger::Logger() {
    logFile.open("MSH_Log.txt", ios::app);
    if (logFile.is_open()) {
        // Log dosyasina baslangic notu
        // cout << "Log System Init" << endl; 
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger* Logger::getInstance() {
    if (!instance) {
        instance = new Logger();
    }
    return instance;
}

// Overloading destegi (String ve Level)
void Logger::log(const string& message, const string& level) {
    if (logFile.is_open()) {
        logFile << "[" << level << "] " << message << endl;
        // Konsola da basmak istersen:
        // cout << "[LOG-" << level << "] " << message << endl;
    }
}

// Diger siniflarin kullandigi tek parametreli versiyon
void Logger::log(const string& message) {
    log(message, "INFO");
}