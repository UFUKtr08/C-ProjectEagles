#ifndef SOUNDSENSOR_H
#define SOUNDSENSOR_H

#include "Device.h"

class SecuritySystem;

class SoundSensor : public Device {
public:
    SoundSensor(int id, string n) : Device(id, n) {}
    ~SoundSensor() {}

    Device* clone() const { return new SoundSensor(*this); }

    void measureLevel(int db, SecuritySystem* sys);
};

#endif