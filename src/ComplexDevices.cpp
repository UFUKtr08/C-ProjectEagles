#include "../include/ComplexDevices.h"
#include "../include/Logger.h"
#include <iostream>
#include <sstream>

// =======================
// Burner Implementation
// =======================
void Burner::setFire(bool status) { isOn = status; }

// =======================
// Stove Implementation
// =======================
Stove::Stove(int id, std::string n) : Device(id, n) {
    for(int i=0; i<4; i++) burners.push_back(new Burner(i+1));
}
Stove::~Stove() {
    for(size_t i=0; i<burners.size(); i++) delete burners[i];
    burners.clear();
}
void Stove::togglePower() {
    isPowered = !isPowered;
    if (!isPowered) {
        for(size_t i=0; i<burners.size(); i++) burners[i]->setFire(false);
        Logger::getInstance()->log(name + " main switch turned OFF.");
    } else {
        Logger::getInstance()->log(name + " main switch turned ON.");
    }
}
Device* Stove::clone() const { return new Stove(deviceID + 100, name + "_Clone"); }

void Stove::controlBurner(int index, bool status) {
    if (!isPowered) {
        std::cout << "Cannot operate burners while Main Stove Switch is OFF!" << std::endl;
        return;
    }
    if (index >= 0 && index < 4) {
        burners[index]->setFire(status);
        std::stringstream ss;
        ss << name << " Burner " << (index+1) << " is now " << (status ? "ON" : "OFF");
        Logger::getInstance()->log(ss.str());
    }
}
void Stove::onGasDetected() {
    Logger::getInstance()->log("!!! EMERGENCY !!! Gas Detected near " + name + ". Auto-Shutting OFF!");
    isPowered = false;
    for(size_t i=0; i<burners.size(); i++) burners[i]->setFire(false);
}
void Stove::operate() {
    // Manuel menü (Eski usül, şimdilik kalabilir)
    cout << ">> Use 'Simulations' menu for advanced control." << endl;
}

// --- STOVE OTO-MENÜ ENTEGRASYONU ---
vector<string> Stove::getActions() {
    vector<string> list;
    list.push_back("Simulate Gas Leak");
    return list;
}
void Stove::performAction(string actionName) {
    if (actionName == "Simulate Gas Leak") onGasDetected();
}

// =======================
// SmartFaucet Implementation
// =======================
SmartFaucet::SmartFaucet(int id, std::string n) : Device(id, n), usageDuration(0), maxSafetyLimit(5) {}

void SmartFaucet::togglePower() {
    if (!isPowered) {
        isPowered = true; usageDuration = 0;
        Logger::getInstance()->log(name + " opened. Water is flowing.");
    } else {
        isPowered = false;
        Logger::getInstance()->log(name + " closed.");
    }
}
Device* SmartFaucet::clone() const { return new SmartFaucet(deviceID + 100, name + "_Clone"); }

void SmartFaucet::checkFloodRisk() {
    if (isPowered) {
        usageDuration++;
        if (usageDuration > maxSafetyLimit) {
            isPowered = false;
            Logger::getInstance()->log("!!! FLOOD RISK !!! " + name + " exceeded safety limit. Auto-Closed.");
        }
    }
}

// --- SMART FAUCET OTO-MENÜ ---
vector<string> SmartFaucet::getActions() {
    vector<string> list;
    list.push_back("Simulate Flood Risk");
    return list;
}
void SmartFaucet::performAction(string actionName) {
    if (actionName == "Simulate Flood Risk") checkFloodRisk();
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
Device* SmartFan::clone() const { return new SmartFan(deviceID + 100, name + "_Clone"); }

void SmartFan::onLightStatusChanged(bool isLightOn) {
    if (!autoModeEnabled) return;
    if (!isLightOn) { 
        isPowered = true; timer = 60; 
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

// --- SMART FAN OTO-MENÜ ---
vector<string> SmartFan::getActions() {
    vector<string> list;
    list.push_back("Toggle Auto Mode");
    return list;
}
void SmartFan::performAction(string actionName) {
    if (actionName == "Toggle Auto Mode") {
        autoModeEnabled = !autoModeEnabled;
        cout << ">> Auto Mode: " << (autoModeEnabled ? "ON" : "OFF") << endl;
    }
}