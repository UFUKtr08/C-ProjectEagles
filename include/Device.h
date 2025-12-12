#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>
#include "Logger.h" // Aynı klasörde oldukları için direkt ismiyle çağırır

using namespace std;

class Device {
protected:
    int deviceID;
    string name;
    bool isPowered;
    bool isBroken;

public:
    Device(int id, string n);
    virtual ~Device();

    int getID() const;
    string getName() const;
    bool getPowerStatus() const;
    bool getBrokenStatus() const;
    
    void setBroken(bool status);

    // Saf Sanal Fonksiyonlar (Abstract)
    virtual void togglePower() = 0;
    virtual Device* clone() const = 0;
};

#endif