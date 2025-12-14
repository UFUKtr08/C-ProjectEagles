#ifndef ALARM_H
#define ALARM_H

#include "Device.h"
#include "Logger.h"
#include <iostream>

class Alarm : public Device {
public:
  Alarm(int id, string n) : Device(id, n) {}
  ~Alarm() {}

  void trigger() {
    if (isPowered) {
      Logger::getInstance()->log("!!! ALARM TRIGGERED !!! (" + getName() + ")",
                                 "ALARM");
      cout << "\n>>> WEE-WOO WEE-WOO! <<<\n" << endl;
    } else {
      Logger::getInstance()->log("Alarm signal received but DISARMED.",
                                 "WARNING");
    }
  }

  void togglePower() {
    isPowered = !isPowered;
    string status = isPowered ? "ARMED" : "DISARMED";
    Logger::getInstance()->log("[Alarm] " + getName() + " is now " + status);
  }

  Device *clone() const { return new Alarm(*this); }

  // EKLENEN KISIM:
  string getType() const { return "Alarm"; }
};

#endif