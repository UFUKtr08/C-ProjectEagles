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
            // Normalde isiklar acik olsun
            if (n.find("Light") != string::npos) {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
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
                // Diger seyler kapali olabilir (GUVENLIK HARIC)
                string t = devices[i]->getType();
                if (t != "Camera" && t != "SmokeDetector" && t != "SoundSensor" && t != "Alarm") {
                    if (devices[i]->getPowerStatus()) devices[i]->togglePower();
                }
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
            string t = devices[i]->getType();

            // GUVENLIK KONTROLU: Bunlari kapatma!
            if (t == "Camera" || t == "SmokeDetector" || t == "SoundSensor" || t == "Alarm") {
                 if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
                 continue; // Döngüyü atla, alttaki kapatma koduna girme
            }

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

// --- GÜNCELLENEN UYKU MODU (Güvenlik Korumalı) ---
class SleepMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: SLEEP MODE");
        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            string t = devices[i]->getType(); 
            
            // --- GÜVENLİK DUVARI ---
            // Eğer cihaz güvenlik cihazıysa ASLA kapatma, aksine AÇIK olduğundan emin ol.
            if (t == "Camera" || t == "SmokeDetector" || t == "SoundSensor" || t == "Alarm") {
                if (!devices[i]->getPowerStatus()) {
                    devices[i]->togglePower(); // Kapalıysa zorla aç
                    Logger::getInstance()->log("[Security] " + n + " forced ON during Sleep Mode.");
                }
                continue; // Döngünün geri kalanını atla (Kapatma komutlarına gitme)
            }
            // -----------------------

            bool shouldTurnOff = false;

            if (n.find("Light") != string::npos) shouldTurnOff = true;
            else if (n.find("Curtain") != string::npos) shouldTurnOff = true;
            else if (n.find("TV") != string::npos) shouldTurnOff = true;
            else if (n.find("Fan") != string::npos) shouldTurnOff = true;    
            else if (n.find("Stove") != string::npos) shouldTurnOff = true;  
            
            if (t == "Stove" || t == "SmartFan") shouldTurnOff = true;

            if (shouldTurnOff && devices[i]->getPowerStatus()) {
                devices[i]->togglePower();
            }
        }
    }
    string getName() const { return "Sleep"; }
};

#endif