#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H

#include "Device.h"
#include <string>
#include <vector>

// SecuritySystem'i sadece ismen tanıyoruz (Forward Declaration)
class SecuritySystem;

class SoundSensor : public Device {
public:
  SoundSensor(int id, std::string n);

  // Override Metodlar
  void togglePower() override;
  Device *clone() const override;
  std::string getType() const override;
  std::vector<std::string> getActions() override;
  void performAction(std::string actionName) override;

  // Özel Metod
  void measureLevel(int db, SecuritySystem *sys);
};

#endif