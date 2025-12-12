#include <iostream>
#include <vector>
#include "../include/Device.h"
#include "../include/Camera.h"
#include "../include/Alarm.h"
#include "../include/SecuritySystem.h"
// Logger varsa ekle, yoksa hata vermesin diye yoruma alabilirsin
// #include "../include/Logger.h" 

using namespace std;

void testSecurityScenario() {
    cout << "\n========================================" << endl;
    cout << "   TEST: SECURITY & SENSORS MODULE" << endl;
    cout << "========================================" << endl;

    // 1. Güvenlik Sistemini (Beyni) Oluştur
    cout << "[1] Initializing Security System..." << endl;
    SecuritySystem mySecuritySystem;

    // 2. Cihazları Oluştur (Pointer ile - Factory mantığına hazırlık)
    cout << "[2] Creating Devices..." << endl;
    Alarm* mainAlarm = new Alarm(101, "Master Alarm");
    Camera* hallCam   = new Camera(201, "Hallway Camera");

    // 3. Alarmı Sisteme Bağla
    cout << "[3] Connecting Alarm to System..." << endl;
    mySecuritySystem.setAlarm(mainAlarm);

    // 4. Kamerayı Aç (Kapalıysa hareket algılamaz)
    cout << "[4] Powering ON Camera..." << endl;
    hallCam->togglePower(); // Kamerayı açar

    // 5. SENARYO: Hareket Algıla!
    // Kameraya diyoruz ki: "Hareket gördün, bu sisteme haber ver"
    cout << "\n>> SCENARIO START: Intruder Detected!" << endl;
    hallCam->detectMotion(&mySecuritySystem);

    // 6. Temizlik (Memory Management - C++98)
    cout << "\n[6] Cleaning up memory..." << endl;
    delete mainAlarm;
    delete hallCam;

    cout << "========================================" << endl;
    cout << "   TEST COMPLETED SUCCESSFULLY" << endl;
    cout << "========================================" << endl;
}

int main() {
    // Doğrudan testimizi çalıştıralım
    testSecurityScenario();
    
    // Konsol hemen kapanmasın diye (Windows kullanıyorsan işe yarar)
    cout << "\nPress Enter to exit...";
    cin.get(); 

    return 0;
}