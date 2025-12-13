#include "../include/SmokeDetector.h"
#include "../include/SecuritySystem.h"
#include <iostream>

void SmokeDetector::detectSmoke(SecuritySystem* sys) {
    cout << " [DANGER] SMOKE detected by " << getName() << "!" << endl;
    // Yangın alarmı gönder
    if (sys) sys->notifyBreach(getName(), "FIRE");
}