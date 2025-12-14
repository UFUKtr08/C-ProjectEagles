#ifndef STANDARD_DEVICES_H
#define STANDARD_DEVICES_H

#include "Device.h"

// --- LIGHT CLASS ---
class Light : public Device {
public:
  // 1. Parametresiz Kurucu (Factory icin)
  Light() : Device(0, "Generic Light") {}
  // 2. Parametreli Kurucu (Main/Test icin)
  Light(int id, string n) : Device(id, n) {}

  void togglePower();
  Device *clone() const;
  string getType() const { return "Light"; }
};

// --- TV CLASS ---
class TV : public Device {
public:
  TV() : Device(0, "Generic TV") {}
  TV(int id, string n) : Device(id, n) {}

  void togglePower();
  Device *clone() const;
  string getType() const { return "TV"; }
};

// --- CURTAIN CLASS ---
class Curtain : public Device {
public:
  Curtain() : Device(0, "Generic Curtain") {}
  Curtain(int id, string n) : Device(id, n) {}

  void togglePower();
  Device *clone() const;
  string getType() const { return "Curtain"; }
};

#endif