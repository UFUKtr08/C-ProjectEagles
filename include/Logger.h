#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Log Seviyeleri (Standartlaştırma)
// C++98'de static const string headerda tanımlanırken dikkatli olunmalı,
// ama pratiklik için bu şekilde bırakıyorum.
static const string LOG_INFO = "INFO";
static const string LOG_WARN = "WARNING";
static const string LOG_ERR  = "ERROR";
static const string LOG_DEBUG = "DEBUG";

class Logger {
private:
    static Logger* instance;
    ofstream logFile;
    
    // Private Constructor (Singleton)
    Logger();

public:
    ~Logger();
    static Logger* getInstance();

    // 1. FATİH'İN ORİJİNAL FONKSİYONU (Aynen Kalıyor)
    // Eski kodlar çalışmaya devam etsin diye.
    void log(const string& message);

    // 2. YENİ EKLENEN FONKSİYON (Gelişmiş)
    // Seviye belirterek log atmak isteyenler bunu kullanacak.
    // Örn: logger->log("Hata oluştu", LOG_ERR);
    void log(const string& message, const string& level);
};

#endif