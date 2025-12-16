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
            if (n.find("Light") != string::npos) {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
            } 
        }
    }
    string getName() const { return "Normal"; }
};

// --- PARTİ MODU (GÜNCELLENDİ) ---
class PartyMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: PARTY MODE");
        cout << "\n>> [PARTY MODE] Ortam ayarlaniyor..." << endl;

        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            string t = devices[i]->getType();

            // --- 1. ÖZEL KURAL: SALOON NOISE SENSOR KAPATILSIN ---
            // Parti gürültülü olacağı için bu sensörü özellikle kapatıyoruz.
            bool isNoiseSensor = (n == "Saloon Noise Sensor") || 
                                 (t == "SoundSensor") || 
                                 (n.find("Noise Sensor") != string::npos);

            if (isNoiseSensor) {
                if (devices[i]->getPowerStatus()) { // Eğer cihaz AÇIK ise
                    devices[i]->togglePower();      // KAPAT
                    cout << "   -> [Auto-OFF] " << n << " (Parti gürültüsü nedeniyle kapatildi)" << endl;
                }
                continue; // Bu cihazla işimiz bitti, sonraki cihaza geç
            }

            // 2. DİĞER GÜVENLİK CİHAZLARI (Kamera, Alarm, Duman) - AÇIK KALSIN
            if (t == "Camera" || t == "SmokeDetector" || t == "Alarm") {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
                continue;
            }

            // 3. EĞLENCE CİHAZLARI (Işıklar ve Hoparlörler AÇILSIN)
            if (n.find("Light") != string::npos || n.find("Sound") != string::npos) {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
            } 
            // 4. DİĞER CİHAZLAR KAPANSIN
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
            string t = devices[i]->getType();

            // Güvenlik cihazlarını koru (Ses Sensörü hariç, kullanıcı manuel kontrol istiyor)
            if (t == "Camera" || t == "SmokeDetector" || t == "Alarm") {
                 if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
                 continue; 
            }

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

// Uyku Modu
class SleepMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: SLEEP MODE");
        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            string t = devices[i]->getType(); 
            
            // Güvenlik cihazlarını koru
            if (t == "Camera" || t == "SmokeDetector" || t == "Alarm") {
                if (!devices[i]->getPowerStatus()) {
                    devices[i]->togglePower();
                }
                continue; 
            }

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