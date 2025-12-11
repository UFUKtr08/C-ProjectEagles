#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>
// Arkadaşının Logger yapısını koruyoruz
//#include "Logger.h" 

using namespace std;

class Device {
protected:
    // --- ARKADAŞININ DEĞİŞKENLERİ (DOKUNULMADI) ---
    int deviceID;   // Senin kodunda 'id' idi, burada arkadaşınınkini (deviceID) kullanacağız.
    string name;
    bool isPowered;
    bool isBroken;

    // --- SENİN EKLEMEN (MERGE) 1: DEFAULT CONSTRUCTOR ---
    // Factory Pattern (new Light()) parametresiz üretim yaptığı için bu ZORUNLU.
    // Protected yaptık ki sadece alt sınıflar kullanabilsin.
    Device() : deviceID(0), name("Unknown"), isPowered(false), isBroken(false) {}

public:
    // --- ARKADAŞININ CONSTRUCTOR'I (DOKUNULMADI) ---
    Device(int id, string n) : deviceID(id), name(n), isPowered(false), isBroken(false) {}
    
    virtual ~Device() {}

    // --- SENİN EKLEMEN (MERGE) 2: SETTERLAR ---
    // DeviceManager nesneyi yarattıktan sonra ID ve İsim atamak zorunda.
    void setID(int id) { deviceID = id; }
    void setName(string n) { name = n; }

    // --- ORTAK GETTERLAR (Arkadaşınınkiler + Inline Implementation) ---
    // Linker hatası almamak için gövdelerini {} buraya yazdım.
    int getID() const { return deviceID; }
    string getName() const { return name; }
    bool getPowerStatus() const { return isPowered; }
    
    // Arkadaşının eklediği özellikler
    bool getBrokenStatus() const { return isBroken; }
    void setBroken(bool status) { isBroken = status; }

    // --- ORTAK SANAL FONKSİYONLAR ---
    // Prototype ve Polimorfizm için gerekli
    virtual void togglePower() = 0;
    virtual Device* clone() const = 0;

    // --- SENİN EKLEMEN 3: TÜR BİLGİSİ ---
    // Listeleme yaparken "Light", "TV" yazdırmak için gerekli
    virtual string getType() const = 0;
};

#endif