#include "ComplexDevices.h"
#include "Logger.h"
#include <iostream>
#include <sstream> // String dönüşümleri için

// =======================
// Burner Implementation
// =======================
void Burner::setFire(bool status) {
    isOn = status;
}

// =======================
// Stove Implementation
// =======================
Stove::Stove(int id, std::string n) : Device(id, n) {
    // 4 tane göz (burner) oluşturuyoruz (Composition)
    for(int i=0; i<4; i++) {
        burners.push_back(new Burner(i+1));
    }
}

Stove::~Stove() {
    // Memory Management (C++98): Pointerları manuel silmeliyiz
    for(size_t i=0; i<burners.size(); i++) {
        delete burners[i];
    }
    burners.clear();
}

void Stove::togglePower() {
    // Ana güç düğmesi: Ocağı kapatırsa hepsini kapatır
    isPowered = !isPowered;
    if (!isPowered) {
        for(size_t i=0; i<burners.size(); i++) {
            burners[i]->setFire(false);
        }
        Logger::getInstance()->log(name + " main switch turned OFF. All burners extinguished.");
    } else {
        Logger::getInstance()->log(name + " main switch turned ON.");
    }
}

// Prototype Pattern: Deep Copy yapmalıyız çünkü içinde pointer vektörü var
Device* Stove::clone() const {
    Stove* newStove = new Stove(this->deviceID + 100, this->name + "_Clone");
    // Ayarları kopyalayabiliriz (Opsiyonel)
    return newStove;
}

void Stove::controlBurner(int index, bool status) {
    if (!isPowered) {
        std::cout << "Cannot operate burners while Main Stove Switch is OFF!" << std::endl;
        return;
    }
    if (index >= 0 && index < 4) {
        burners[index]->setFire(status);
        
        // Loglama için string stream (C++98 usulü)
        std::stringstream ss;
        ss << name << " Burner " << (index+1) << " is now " << (status ? "ON" : "OFF");
        Logger::getInstance()->log(ss.str());
    }
}
void Stove::operate() {
    cout << "\n--- " << getName() << " CONTROL PANEL ---" << endl;

    if (!isPowered) {
        cout << "(!) Warning: You must turn ON the device to configure it." << endl;
        return;
    }

    int burnerIndex;
    cout << "Select Burner (1-4): ";
    
    // Hatalı giriş kontrolü (sayı girilmezse döngüye girmesin)
    if (!(cin >> burnerIndex)) {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << ">> Invalid input!" << endl;
        return;
    }

    int status;
    cout << "Action (1: Ignite, 0: Extinguish): ";
    cin >> status;

    // Asıl işi yapan fonksiyonu çağırıyoruz
    controlBurner(burnerIndex - 1, (status == 1));
    
    // Buffer temizliği
    cin.ignore(10000, '\n'); 
}

// LLR-050: Gaz algılandığında acil durum!
void Stove::onGasDetected() {
    Logger::getInstance()->log("!!! EMERGENCY !!! Gas Detected near " + name + ". Auto-Shutting OFF!");
    isPowered = false;
    for(size_t i=0; i<burners.size(); i++) {
        burners[i]->setFire(false);
    }
}

// =======================
// SmartFaucet Implementation
// =======================
SmartFaucet::SmartFaucet(int id, std::string n) : Device(id, n), usageDuration(0), maxSafetyLimit(5) {}

void SmartFaucet::togglePower() {
    if (!isPowered) {
        // Açılış İsteği
        isPowered = true;
        usageDuration = 0; // Sayacı sıfırla
        Logger::getInstance()->log(name + " opened. Water is flowing.");
    } else {
        // Kapanış İsteği
        isPowered = false;
        Logger::getInstance()->log(name + " closed.");
    }
}

Device* SmartFaucet::clone() const {
    return new SmartFaucet(this->deviceID + 100, this->name + "_Clone");
}

// LLR-055: Proxy / Auto-Shutoff Logic
void SmartFaucet::checkFloodRisk() {
    if (isPowered) {
        usageDuration++;
        if (usageDuration > maxSafetyLimit) {
            isPowered = false;
            Logger::getInstance()->log("!!! FLOOD RISK !!! " + name + " exceeded safety limit. Auto-Closed.");
        }
    }
}

// =======================
// SmartFan Implementation
// =======================
SmartFan::SmartFan(int id, std::string n) : Device(id, n), autoModeEnabled(true), timer(0) {}

void SmartFan::togglePower() {
    isPowered = !isPowered;
    if(isPowered) Logger::getInstance()->log(name + " started manually.");
    else Logger::getInstance()->log(name + " stopped.");
}

Device* SmartFan::clone() const {
    return new SmartFan(this->deviceID + 100, this->name + "_Clone");
}

// LLR-044: Işık kapanınca fan açılmalı
void SmartFan::onLightStatusChanged(bool isLightOn) {
    if (!autoModeEnabled) return;

    if (!isLightOn) { // Işık kapandı (Tuvaletten çıkıldı)
        isPowered = true;
        timer = 60; // 60 saniye çalışacak (Simülasyon değeri)
        Logger::getInstance()->log(name + " Auto-Started because Light turned OFF.");
    }
}

void SmartFan::updateTimer() {
    if (isPowered && timer > 0) {
        timer--;
        if (timer == 0) {
            isPowered = false;
            Logger::getInstance()->log(name + " Auto-Stopped (Timer finished).");
        }
    }
}