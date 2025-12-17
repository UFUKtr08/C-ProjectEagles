#ifndef ALARM_H
#define ALARM_H

#include "Device.h"
#include <string>
#include <vector>

class Alarm : public Device {
private:
  bool isTriggered;
  std::string pinCode;

public:
  // Constructor
  Alarm(int id, std::string n);

  // Override Metodlar (Sadece Tanım)
  void togglePower() override;
  Device *clone() const override;
  std::string getType() const override;
  std::vector<std::string> getActions() override;
  void performAction(std::string actionName) override;

  // Özel Metodlar (Sadece Tanım)
  void triggerAlarm();
  void resetAlarm(std::string pin);

  // Hata veren "no declaration matches" kısmı buydu, buraya ekledik:
  bool getTriggerStatus() const;
};

#endif