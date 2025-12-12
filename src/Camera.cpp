#include "../include/Camera.h"
#include "../include/SecuritySystem.h" // Tam tanım burada lazım
#include <iostream>

void Camera::detectMotion(SecuritySystem* sys) {
    if (isPowered) {
        cout << " [MOTION] Movement detected by " << getName() << endl;
        // Sistemi uyar
        if (sys) sys->notifyBreach(getName(), "MOTION");
    } else {
        cout << " [X] Camera is OFF. Cannot detect motion." << endl;
    }
}