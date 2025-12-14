#include "../include/SmokeDetector.h"
#include "../include/SecuritySystem.h"
#include <iostream>

void SmokeDetector::detectSmoke(SecuritySystem* sys) {
    cout << " [DANGER] SMOKE detected by " << getName() << "!" << endl;
    // Yangın alarmı gönder
    if (sys) sys->notifyBreach(getName(), "FIRE");
}
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
