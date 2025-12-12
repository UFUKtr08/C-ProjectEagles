#include <iostream>
#include <vector>
#include "../include/Logger.h"
#include "../include/Device.h"
#include "../include/ModeManager.h"

using namespace std;

// --- TEST İÇİN GEÇİCİ CİHAZ SINIFLARI (Mock Objects) ---
class Light : public Device {
public:
    Light(int id, string n) : Device(id, n) {}
    void togglePower() {
        isPowered = !isPowered;
        string status = isPowered ? "ON" : "OFF";
        Logger::getInstance()->log("Light (" + name + ") toggled " + status);
    }
    Device* clone() const { return new Light(*this); }
};

class TV : public Device {
public:
    TV(int id, string n) : Device(id, n) {}
    void togglePower() {
        isPowered = !isPowered;
        string status = isPowered ? "ON" : "OFF";
        Logger::getInstance()->log("TV (" + name + ") toggled " + status);
    }
    Device* clone() const { return new TV(*this); }
};

// --- ANA PROGRAM ---
int main() {
    Logger::getInstance()->log("--- MODULE 5 TEST STARTED ---");

    // 1. Cihazları Oluştur
    vector<Device*> myDevices;
    myDevices.push_back(new Light(1, "Living Room Light"));
    myDevices.push_back(new TV(2, "Main TV"));
    myDevices.push_back(new Light(3, "Kitchen Light"));

    // 2. Mode Manager'ı Başlat
    ModeManager* modeMgr = new ModeManager();
    
    cout << "Current Mode: " << modeMgr->getCurrentModeName() << endl; // Normal
    
    // TEST: Sinema Moduna Geç
    cout << "\n--- Switching to Cinema Mode ---" << endl;
    modeMgr->setMode(new CinemaMode(), myDevices);

    // TEST: Geri Al (Undo) -> Normal Moda dönmeli
    cout << "\n--- Restoring Previous State ---" << endl;
    modeMgr->restorePreviousState(myDevices);

    // Temizlik
    for(size_t i=0; i<myDevices.size(); ++i) delete myDevices[i];
    delete modeMgr;

    return 0;
}