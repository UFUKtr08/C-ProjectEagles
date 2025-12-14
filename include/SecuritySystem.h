#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

#include "Alarm.h"
#include <string>
#include <vector>
using namespace std;

class SecuritySystem {
private:
  Alarm *attachedAlarm;

public:
  SecuritySystem(); // Gövdeyi cpp'ye taşıdık

  void setAlarm(Alarm *alm); // Gövdeyi cpp'ye taşıdık
  void notifyBreach(string sensorName, string breachType);
  void triggerSequence();
  void checkNoiseLevel(int db);
};

#endif