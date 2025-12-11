#ifndef STANDARD_DEVICES_H
#define STANDARD_DEVICES_H

#include "Device.h"

// --- LIGHT CLASS ---
class Light : public Device {
public:
    void togglePower();
    Device* clone() const; // Prototype Pattern Implementation
    string getType() const { return "Light"; }
};

// --- TV CLASS ---
class TV : public Device {
public:
    void togglePower();
    Device* clone() const;
    string getType() const { return "TV"; }
};

// --- CURTAIN CLASS (Yeni eklenen özellik) ---
class Curtain : public Device {
public:
    void togglePower(); // Open/Close mantığı
    Device* clone() const;
    string getType() const { return "Curtain"; }
};

#endif