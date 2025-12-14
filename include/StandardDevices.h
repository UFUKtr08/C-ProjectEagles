#ifndef STANDARD_DEVICES_H
#define STANDARD_DEVICES_H

#include "Device.h"
#include <vector> // vector kütüphanesi eklendi

// --- LIGHT CLASS ---
class Light : public Device {
public:
  Light() : Device(0, "Generic Light") {}
  Light(int id, string n) : Device(id, n) {}

  void togglePower();
  Device *clone() const;
  string getType() const { return "Light"; }

  // Oto-Menü Entegrasyonu
  vector<string> getActions();
  void performAction(string actionName);
};

// --- TV CLASS ---
class TV : public Device {
public:
  TV() : Device(0, "Generic TV") {}
  TV(int id, string n) : Device(id, n) {}

  void togglePower();
  Device *clone() const;
  string getType() const { return "TV"; }

  // Oto-Menü Entegrasyonu
  vector<string> getActions();
  void performAction(string actionName);
};

// --- CURTAIN CLASS ---
class Curtain : public Device {
public:
  Curtain() : Device(0, "Generic Curtain") {}
  Curtain(int id, string n) : Device(id, n) {}

  void togglePower();
  Device *clone() const;
  string getType() const { return "Curtain"; }

  // Oto-Menü Entegrasyonu
  vector<string> getActions();
  void performAction(string actionName);
};

#endif