/*
    Dosya Adi: include/Alarm.h
    Aciklama: SecuritySystem tarafindan tetiklenen Alarm cihazinin tanimi.
*/

#ifndef ALARM_H
#define ALARM_H

#include "Device.h"
#include "Logger.h"
#include <iostream>
#include <string>

using namespace std;

class Alarm : public Device {
public:
    // Constructor: ID ve Isim alip Device constructori'na paslar
    Alarm(int id, string n) : Device(id, n) {}
    
    virtual ~Alarm() {}

    // SecuritySystem::triggerSequence() tarafindan cagirilan fonksiyon
    // Virtual yapiyoruz ki ilerde "SessizAlarm", "PolisAlarmi" gibi turler turetebilesin.
    virtual void trigger() {
        if (isPowered) {
            // Alarm aciksa (Powered ON) calisir
            Logger::getInstance()->log("!!! ALARM TRIGGERED !!! (" + getName() + ")", "ALARM");
            cout << "\n**************************************" << endl;
            cout << ">>> ALARM SOUNDING: WEE-WOO WEE-WOO! <<<" << endl;
            cout << "**************************************\n" << endl;
        } else {
            // Alarm kapaliysa sadece log dusurur
            Logger::getInstance()->log("Alarm signal received but device is OFF (Disarmed).", "WARNING");
            cout << ">>> Alarm signal received, but Alarm is DISARMED." << endl;
        }
    }

    // --- Device Sinifindan Gelen Zorunlu Fonksiyonlar ---

    void togglePower() {
        isPowered = !isPowered;
        string status = isPowered ? "ARMED (ON)" : "DISARMED (OFF)";
        Logger::getInstance()->log("[Alarm] " + getName() + " is now " + status);
    }

    Device* clone() const {
        return new Alarm(*this);
    }
};

#endif