#include "../include/StandardDevices.h"
#include <iostream>

// --- LIGHT IMPLEMENTATION ---
void Light::togglePower() {
    isPowered = !isPowered;
    cout << "[Light] " << name << " (ID: " << getID() << ") is now " 
         << (isPowered ? "ON" : "OFF") << endl;
}

Device* Light::clone() const { return new Light(*this); }

// Işık Yetenekleri
vector<string> Light::getActions() {
    vector<string> list;
    list.push_back("Change Color");
    list.push_back("Dim Brightness");
    return list;
}

void Light::performAction(string actionName) {
    if (actionName == "Change Color") {
        cout << ">> [Light] Color changed to 'Warm White' (Simulation)" << endl;
    } else if (actionName == "Dim Brightness") {
        cout << ">> [Light] Brightness dimmed to 50%." << endl;
    }
}


// --- TV IMPLEMENTATION ---
void TV::togglePower() {
    isPowered = !isPowered;
    cout << "[TV] " << name << " (ID: " << getID() << ") is now " 
         << (isPowered ? "ON" : "OFF") << endl;
}

Device* TV::clone() const { return new TV(*this); }

// TV Yetenekleri
vector<string> TV::getActions() {
    vector<string> list;
    list.push_back("Scan Channels");
    return list;
}

void TV::performAction(string actionName) {
    if (actionName == "Scan Channels") {
        cout << ">> [TV] Scanning... Found 120 digital channels." << endl;
    }
}


// --- CURTAIN IMPLEMENTATION ---
void Curtain::togglePower() {
    isPowered = !isPowered; 
    cout << "[Curtain] " << name << " (ID: " << getID() << ") is now " 
         << (isPowered ? "OPEN" : "CLOSED") << endl;
}

Device* Curtain::clone() const { return new Curtain(*this); }

// Perde Yetenekleri
vector<string> Curtain::getActions() {
    vector<string> list;
    list.push_back("Clean Curtain");
    return list;
}

void Curtain::performAction(string actionName) {
    if (actionName == "Clean Curtain") {
        cout << ">> [Curtain] Maintenance Mode: Cleaning cycle started..." << endl;
    }
}