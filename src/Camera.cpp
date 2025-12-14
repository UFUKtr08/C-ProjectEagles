#include "../include/Camera.h"
#include "../include/SecuritySystem.h" 
#include <iostream>

void Camera::detectMotion(SecuritySystem* sys) {
    if (isPowered) {
        cout << " [MOTION] Movement detected by " << getName() << endl;
        if (sys) sys->notifyBreach(getName(), "MOTION");
    } else {
        cout << " [X] Camera is OFF." << endl;
    }
}

// --- EKLENEN KISIM ---
vector<string> Camera::getActions() {
    vector<string> list;
    list.push_back("Trigger Motion Detect");
    return list;
}

void Camera::performAction(string actionName) {
    if (actionName == "Trigger Motion Detect") {
        cout << ">> [CAMERA] Motion Simulated!" << endl;
    }
}