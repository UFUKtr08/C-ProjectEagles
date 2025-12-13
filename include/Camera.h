#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h"
#include <iostream>

class SecuritySystem; // Forward Declaration

class Camera : public Device {
public:
    Camera(int id, string n) : Device(id, n) {}
    ~Camera() {}

    // EKSİK OLAN PARÇA BU:
    void togglePower() {
        isPowered = !isPowered;
        cout << getName() << (isPowered ? " is now ON." : " is now OFF.") << endl;
    }

    Device* clone() const { return new Camera(*this); }

    void detectMotion(SecuritySystem* sys);
};

#endif