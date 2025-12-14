#ifndef COMPLEX_DEVICES_H
#define COMPLEX_DEVICES_H

#include "Device.h"
#include <vector>

// ==========================================
// FEATURE 1: STOVE & BURNERS (Composite Pattern)
// ==========================================

// Yardımcı Sınıf (Parça)
class Burner {
private:
    int id;
    bool isOn;
public:
    Burner(int burnerID) : id(burnerID), isOn(false) {}
    void setFire(bool status);
    bool getStatus() const { return isOn; }
};

// Ana Sınıf (Bütün)
class Stove : public Device {
private:
    std::vector<Burner*> burners; // Composition: Ocak brülörlerden oluşur

public:
    Stove(int id, std::string n);
    ~Stove(); // Destructor önemli: Burner'ları temizlemeli

    void togglePower(); // Tüm ocağı kapatır/açar
    Device* clone() const; // Prototype Pattern

    // Brülörleri tek tek kontrol etme (LLR-048)
    void controlBurner(int index, bool status);

    // Observer Pattern: Gaz Dedektörü tetiklerse burası çağrılır (LLR-050)
    void onGasDetected();
};

// ==========================================
// FEATURE 2: SMART FAUCET (Proxy Logic)
// ==========================================
class SmartFaucet : public Device {
private:
    int usageDuration; // Ne kadar süredir açık (simülasyon tick'i)
    int maxSafetyLimit; // LLR-055 (Örn: 5 birim)

public:
    SmartFaucet(int id, std::string n);
    
    void togglePower(); // Açmaya çalışırken Proxy kontrolü yapar
    Device* clone() const;

    // Su taşkın kontrolü (Periyodik çağrılacak)
    void checkFloodRisk();
};

// ==========================================
// FEATURE 3: SMART FAN (Observer Logic)
// ==========================================
class SmartFan : public Device {
private:
    bool autoModeEnabled;
    int timer; 

public:
    SmartFan(int id, std::string n);

    void togglePower();
    Device* clone() const;

    // Observer Pattern: Işık durumu değişince burası çağrılır (LLR-044)
    // Not: Light sınıfını include etmedik, bağımlılığı kestik. 
    // Sadece bool durum alıyoruz.
    void onLightStatusChanged(bool isLightOn);
    
    void updateTimer(); // Fanın çalışıp kapanmasını sayar
};

#endif