#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Logger {
private:
    static Logger* instance;
    ofstream logFile;
    Logger();
public:
    ~Logger();
    static Logger* getInstance();
    void log(const string& message);
};
#endif