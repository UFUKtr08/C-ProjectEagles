#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "Device.h"
#include <string>
#include <vector>

// --- TÜM BAŞLIK DOSYALARI BURADA OLMALI ---
#include "Alarm.h"
#include "Camera.h"
#include "ComplexDevices.h"
#include "GasDetector.h"
#include "SecuritySystem.h"
#include "SmokeDetector.h"
#include "SoundSensor.h"
#include "StandardDevices.h"

using namespace std;

class DeviceFactory {
public:
  static Device *createDevice(string type, int id, string name) {
    if (type == "Light")
      return new Light(id, name);
    else if (type == "TV")
      return new TV(id, name);
    else if (type == "Curtain")
      return new Curtain(id, name);
    else if (type == "SmartFan")
      return new SmartFan(id, name);
    else if (type == "SmartFaucet")
      return new SmartFaucet(id, name);
    else if (type == "Stove")
      return new Stove(id, name);
    else if (type == "SmokeDetector")
      return new SmokeDetector(id, name);
    else if (type == "Camera")
      return new Camera(id, name);

    else if (type == "SoundSensor")
      return new SoundSensor(id, name);

    else if (type == "Alarm")
      return new Alarm(id, name);

    else if (type == "GasDetector")
      return new GasDetector(id, name);

    else
      return nullptr;
  }

  static vector<string> getAvailableTypes() {
    return {"Light",       "TV",          "Curtain",       "SmartFan",
            "SmartFaucet", "Stove",       "SmokeDetector", "GasDetector",
            "Camera",      "SoundSensor", "Alarm"};
  }
};

#endif