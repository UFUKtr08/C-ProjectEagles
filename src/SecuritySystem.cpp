#include "../include/SecuritySystem.h"
#include "../include/Logger.h"
#include <iostream>

// String birleştirme hatası almamak için using namespace std şart
using namespace std;

SecuritySystem::SecuritySystem() {
    this->attachedAlarm = NULL;
}

void SecuritySystem::setAlarm(Alarm* alm) {
    this->attachedAlarm = alm;
}

void SecuritySystem::notifyBreach(string sensorName, string breachType) {
    cout << "\n>>> SECURITY ALERT: " << breachType << " detected by " << sensorName << " <<<" << endl;
    
    // LOGLAMA (Fatih'in Logger'ına uygun manuel formatlama)
    if (Logger::getInstance()) {
        // "[SECURITY] Breach: MOTION (Camera1)" şeklinde tek string yapıyoruz
        string logMsg = "[SECURITY] Breach: " + breachType + " (" + sensorName + ")";
        Logger::getInstance()->log(logMsg);
    }

    triggerSequence();
}

void SecuritySystem::triggerSequence() {
    cout << "--- SECURITY PROTOCOL INITIATED ---" << endl;
    
    cout << "1. [ACTION] Triggering Alarm..." << endl;
    if (attachedAlarm) {
        attachedAlarm->trigger();
    } else {
        cout << "   (No alarm attached!)" << endl;
    }

    cout << "2. [ACTION] Turning ON all lights (Simulated)..." << endl;
    cout << "3. [ACTION] Dialing 155 (Police)..." << endl;
    
    if (Logger::getInstance()) {
        Logger::getInstance()->log("[SECURITY] Protocol Executed: Alarm -> Lights -> Police");
    }
}

void SecuritySystem::checkNoiseLevel(int db) {
    if (db > 80) {
        cout << "\n>>> [WARNING] HIGH NOISE LEVEL (" << db << "dB) <<<" << endl;
        
        if (Logger::getInstance()) {
            // int stringe çevirmekle uğraşmamak için basit mesaj
            Logger::getInstance()->log("[SECURITY] [WARNING] High noise level detected!");
        }
    }
}