#include <iostream>
#include "../include/SecuritySystem.h"
#include "../include/Alarm.h"
#include "../include/Camera.h"
#include "../include/SmokeDetector.h"
#include "../include/SoundSensor.h"
// Device.h ve Logger.h zaten diğerlerinin içinde include edildi.

using namespace std;

int main() {
    cout << "=== MSH MODULE 3: SECURITY & SENSORS TEST ===" << endl;

    // 1. Sistemi ve Alarmı Kur
    SecuritySystem sys;
    Alarm* mainAlarm = new Alarm(1, "Master Alarm");
    sys.setAlarm(mainAlarm);

    // 2. Sensörleri Oluştur
    Camera* cam = new Camera(101, "Hallway Cam");
    SmokeDetector* smoke = new SmokeDetector(102, "Kitchen Smoke Det.");
    SoundSensor* mic = new SoundSensor(103, "Living Room Mic");

    // 3. Test Senaryosu 1: Hırsız (Kamera)
    cout << "\n--- SCENARIO 1: INTRUDER ---" << endl;
    cam->togglePower(); // Kamerayı aç
    cam->detectMotion(&sys); // Hırsızı yakala

    // 4. Test Senaryosu 2: Yangın (Duman Dedektörü)
    cout << "\n--- SCENARIO 2: FIRE ---" << endl;
    smoke->togglePower(); // Kapatmayı dene (Hata vermeli)
    smoke->detectSmoke(&sys); // Dumanı algıla

    // 5. Test Senaryosu 3: Gürültü (Ses Sensörü)
    cout << "\n--- SCENARIO 3: GOOD NEIGHBOR ---" << endl;
    mic->togglePower();
    mic->measureLevel(50, &sys); // Normal ses
    mic->measureLevel(95, &sys); // Yüksek ses (Uyarı vermeli)

    // 6. Temizlik
    cout << "\n[Cleaning Up]" << endl;
    delete mainAlarm;
    delete cam;
    delete smoke;
    delete mic;

    return 0;
}