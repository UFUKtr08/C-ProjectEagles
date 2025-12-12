#ifndef MODES_H
#define MODES_H

#include <vector>
#include <string>
#include <iostream>
#include "Device.h"
#include "Logger.h"

using namespace std;

// Interface
class IMode {
public:
    virtual ~IMode() {}
    virtual void execute(vector<Device*>& devices) = 0;
    virtual string getName() const = 0;
};

// Normal Mod
class NormalMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: NORMAL MODE");
        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            // Isiklar acik olsun
            if (n.find("Light") != string::npos) {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
            } 
            else {
                if (devices[i]->getPowerStatus()) devices[i]->togglePower();
            }
        }
    }
    string getName() const { return "Normal"; }
};

// Party Modu
class PartyMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: PARTY MODE");
        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            // Isik ve Ses acik
            if (n.find("Light") != string::npos || n.find("Sound") != string::npos) {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
            } 
            else {
                if (devices[i]->getPowerStatus()) devices[i]->togglePower();
            }
        }
    }
    string getName() const { return "Party"; }
};

// Sinema Modu
class CinemaMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: CINEMA MODE");
        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            // Sadece TV acik
            if (n.find("TV") != string::npos) {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
            } 
            else {
                if (devices[i]->getPowerStatus()) devices[i]->togglePower();
            }
        }
    }
    string getName() const { return "Cinema"; }
};

#endif