#include "../include/StandardDevices.h"

// --- LIGHT IMPLEMENTATION ---
void Light::togglePower() {
    isPowered = !isPowered;
    // DEĞİŞİKLİK BURADA: 'id' yerine 'getID()' kullandık
    cout << "[Light] " << name << " (ID: " << getID() << ") is now " 
         << (isPowered ? "ON" : "OFF") << endl;
}

Device* Light::clone() const {
    return new Light(*this);
}

// --- TV IMPLEMENTATION ---
void TV::togglePower() {
    isPowered = !isPowered;
    // DEĞİŞİKLİK BURADA: 'id' yerine 'getID()' kullandık
    cout << "[TV] " << name << " (ID: " << getID() << ") is now " 
         << (isPowered ? "ON" : "OFF") << endl;
}

Device* TV::clone() const {
    return new TV(*this);
}

// --- CURTAIN IMPLEMENTATION ---
void Curtain::togglePower() {
    isPowered = !isPowered; // True: Open, False: Closed
    // DEĞİŞİKLİK BURADA: 'id' yerine 'getID()' kullandık
    cout << "[Curtain] " << name << " (ID: " << getID() << ") is now " 
         << (isPowered ? "OPEN" : "CLOSED") << endl;
}

Device* Curtain::clone() const {
    return new Curtain(*this);
}