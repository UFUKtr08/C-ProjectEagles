#ifndef SMOKEDETECTOR_H
#define SMOKEDETECTOR_H

#include "Device.h"
#include <iostream>

class SecuritySystem;

class SmokeDetector : public Device {
public:
  SmokeDetector(int id, string n) : Device(id, n) { isPowered = true; }
  ~SmokeDetector() {}

  void togglePower() {
    cout << " [ACCESS DENIED] Safety device cannot be turned off!" << endl;
  }

  Device *clone() const { return new SmokeDetector(*this); }

  void detectSmoke(SecuritySystem *sys);

  // EKLENEN KISIM:
  string getType() const { return "SmokeDetector"; }
};
vector<string> SmokeDetector::getActions() {
  vector<string> list;
  list.push_back("Trigger Smoke Alarm");
  return list;
}

void SmokeDetector::performAction(string actionName) {
  if (actionName == "Trigger Smoke Alarm") {
      cout << ">> [SMOKE] Sensor triggered manually! Fire suspected." << endl;
  }
}

#endif