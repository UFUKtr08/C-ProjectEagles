#include "../include/SecuritySystem.h"
#include <iostream>
// #include <unistd.h> // Linux/Mac'te bekleme (sleep) için
// #include <windows.h> // Windows'ta bekleme için

void SecuritySystem::notifyBreach(string sensorName, string breachType) {
    cout << "\n>>> SECURITY ALERT RECEIVED <<<" << endl;
    cout << "Source: " << sensorName << " | Type: " << breachType << endl;
    
    // Zinciri tetikle
    triggerSequence();
}

void SecuritySystem::triggerSequence() {
    cout << "1. [ACTION] Triggering Alarm..." << endl;
    if (attachedAlarm) {
        attachedAlarm->trigger();
    } else {
        cout << "   (No alarm attached!)" << endl;
    }

    // Simülasyon gereği burada bekletebilirsin ama zorunlu değil
    cout << "2. [ACTION] Turning ON all lights (Simulated)..." << endl;
    
    cout << "3. [ACTION] Calling Police (155)..." << endl;
    cout << ">>> SECURITY PROTOCOL FINISHED <<<\n" << endl;
}