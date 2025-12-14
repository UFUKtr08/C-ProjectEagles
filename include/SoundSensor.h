#ifndef SOUNDSENSOR_H
#define SOUNDSENSOR_H

#include "Device.h"
#include <iostream>

class SecuritySystem;

class SoundSensor : public Device {
public:
  SoundSensor(int id, string n) : Device(id, n) {}
  ~SoundSensor() {}

  // EKSİK OLAN PARÇA BU:
  void togglePower() {
    isPowered = !isPowered;
    cout << getName() << (isPowered ? " is now ON." : " is now OFF.") << endl;
  }

  Device *clone() const { return new SoundSensor(*this); }

  void measureLevel(int db, SecuritySystem *sys);
  string getType() const { return "SoundSensor"; }
};

#endif