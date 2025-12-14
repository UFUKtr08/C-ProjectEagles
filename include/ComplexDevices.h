#ifndef COMPLEX_DEVICES_H
#define COMPLEX_DEVICES_H

#include "Device.h"
#include <string>
#include <vector>

// --- BURNER CLASS (Ocak Gözü) ---
class Burner {
private:
  int id;
  bool isOn;

public:
  Burner(int i) : id(i), isOn(false) {}
  void setFire(bool status);
  bool getStatus() const { return isOn; }
  
};

// --- STOVE CLASS (Ocak) ---
class Stove : public Device {
private:
  std::vector<Burner *> burners;

public:
  Stove(int id, std::string n);
  ~Stove();

  void togglePower();
  Device *clone() const;
  void controlBurner(int index, bool status);
  void onGasDetected();
  void operate();
  // EKSİK OLAN BUYDU:
  std::string getType() const { return "Stove"; }
};

// --- SMART FAUCET (Akıllı Musluk) ---
class SmartFaucet : public Device {
private:
  int usageDuration;
  int maxSafetyLimit;

public:
  SmartFaucet(int id, std::string n);
  void togglePower();
  Device *clone() const;
  void checkFloodRisk();
  void operate();

  // EKSİK OLAN BUYDU:
  std::string getType() const { return "SmartFaucet"; }
};

// --- SMART FAN (Akıllı Fan) ---
class SmartFan : public Device {
private:
  bool autoModeEnabled;
  int timer;

public:
  SmartFan(int id, std::string n);
  void togglePower();
  Device *clone() const;
  void onLightStatusChanged(bool isLightOn);
  void updateTimer();
  void operate();

  // EKSİK OLAN BUYDU:
  std::string getType() const { return "SmartFan"; }
};

#endif