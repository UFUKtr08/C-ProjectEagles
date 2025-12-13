#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

#include <string>
#include <vector>
#include "Alarm.h"

using namespace std;

class SecuritySystem {
private:
    Alarm* attachedAlarm;

public:
    SecuritySystem() : attachedAlarm(NULL) {}
    
    // Sistemi bir alarma bağlamak için
    void setAlarm(Alarm* alm) {
        attachedAlarm = alm;
    }

    // MEDIATOR: Sensörlerden gelen bildirimi alır
    void notifyBreach(string sensorName, string breachType);

    // CHAIN OF RESPONSIBILITY: Sırayla işlemleri yapar
    void triggerSequence();
};

#endif