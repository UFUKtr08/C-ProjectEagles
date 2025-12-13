#ifndef SMOKEDETECTOR_H
#define SMOKEDETECTOR_H

#include "Device.h"

class SecuritySystem;

class SmokeDetector : public Device {
public:
    // Kritik cihazlar varsayılan olarak AÇIK başlar
    SmokeDetector(int id, string n) : Device(id, n) { isPowered = true; }
    ~SmokeDetector() {}

    // LLR-016: Kapatılamaz!
    void togglePower() {
        cout << " [ACCESS DENIED] Safety device cannot be turned off!" << endl;
    }

    Device* clone() const { return new SmokeDetector(*this); }

    void detectSmoke(SecuritySystem* sys);
};

#endif