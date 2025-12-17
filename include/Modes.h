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

// Normal Mode (LLR-020: Light: ON, TV: OFF, Music: OFF)
class NormalMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: NORMAL MODE");
        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            string t = devices[i]->getType();
            
            // Security devices stay on
            if (t == "Camera" || t == "SmokeDetector" || t == "GasDetector" || t == "Alarm") {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
                continue;
            }
            
            // Lights ON
            if (n.find("Light") != string::npos) {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
            }
            // TV OFF
            else if (n.find("TV") != string::npos) {
                if (devices[i]->getPowerStatus()) devices[i]->togglePower();
            }
            // Sound/Music OFF
            else if (n.find("Sound") != string::npos || t == "SoundSensor") {
                if (devices[i]->getPowerStatus()) devices[i]->togglePower();
            }
        }
    }
    string getName() const { return "Normal"; }
};

// Evening Mode (LLR-021: Lights: OFF, TV: OFF)
class EveningMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: EVENING MODE");
        cout << "\n>> [EVENING MODE] Preparing for evening..." << endl;
        
        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            string t = devices[i]->getType();
            
            // Security devices stay on
            if (t == "Camera" || t == "SmokeDetector" || t == "GasDetector" || t == "Alarm") {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
                continue;
            }
            
            // Lights OFF
            if (n.find("Light") != string::npos) {
                if (devices[i]->getPowerStatus()) devices[i]->togglePower();
            }
            // TV OFF
            else if (n.find("TV") != string::npos) {
                if (devices[i]->getPowerStatus()) devices[i]->togglePower();
            }
        }
    }
    string getName() const { return "Evening"; }
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

// Good Neighbor Mode (LLR-052: Monitors SoundSensor input)
class GoodNeighborMode : public IMode {
public:
    void execute(vector<Device*>& devices) {
        Logger::getInstance()->log("Mode executing: GOOD NEIGHBOR MODE");
        cout << "\n>> [GOOD NEIGHBOR MODE] Activating noise monitoring..." << endl;
        
        for (size_t i = 0; i < devices.size(); ++i) {
            string n = devices[i]->getName();
            string t = devices[i]->getType();
            
            // Security devices stay on
            if (t == "Camera" || t == "SmokeDetector" || t == "GasDetector" || t == "Alarm") {
                if (!devices[i]->getPowerStatus()) devices[i]->togglePower();
                continue;
            }
            
            // SoundSensor MUST be ON for monitoring
            if (t == "SoundSensor") {
                if (!devices[i]->getPowerStatus()) {
                    devices[i]->togglePower();
                    cout << "   -> [Auto-ON] " << n << " (Noise monitoring activated)" << endl;
                }
            }
            // Turn off loud devices
            else if (n.find("TV") != string::npos || n.find("Sound") != string::npos) {
                if (devices[i]->getPowerStatus()) {
                    devices[i]->togglePower();
                    cout << "   -> [Auto-OFF] " << n << " (Reducing noise for neighbors)" << endl;
                }
            }
        }
        cout << ">> Good Neighbor Mode: Noise levels will be monitored. High dB triggers warning." << endl;
    }
    string getName() const { return "GoodNeighbor"; }
};

#endif