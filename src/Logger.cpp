#include "../include/Logger.h"
<<<<<<< HEAD

// Singleton Instance Başlatma
Logger* Logger::instance = NULL;

// Constructor
Logger::Logger() {
    // Dosyayı "append" (ekleme) modunda açıyoruz
    logFile.open("MSH_Log.txt", ios::app);
    if (!logFile.is_open()) {
        cout << "[LOGGER ERROR] Could not open log file!" << endl;
    }
}

// Destructor
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

// GetInstance
Logger* Logger::getInstance() {
    if (!instance) {
        instance = new Logger();
    }
    return instance;
}

// =========================================================
// GÜNCELLEME BURADA (Overloading Implementation)
// =========================================================

// 1. ESKİ FONKSİYON (Wrapper)
// Fatih'in yazdığı yerler buraya düşecek.
// Otomatik olarak "INFO" etiketi yapıştırıp diğer fonksiyona paslıyoruz.
void Logger::log(const string& message) {
    log(message, LOG_INFO); 
}

// 2. YENİ FONKSİYON (Asıl İşçi)
// Sen ve diğerleri bunu kullanacaksınız.
void Logger::log(const string& message, const string& level) {
    if (logFile.is_open()) {
        // Dosyaya yazma formatı: [SEVİYE] Mesaj
        logFile << "[" << level << "] " << message << endl;
        
        // İstersen konsola da basabilirsin (Test için iyi olur)
        // cout << "[" << level << "] " << message << endl;
=======
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
>>>>>>> 8d91ab7937d6b95c67b99dbbb7553c5d399ae840
    }
}