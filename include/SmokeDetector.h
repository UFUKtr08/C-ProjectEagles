#ifndef SMOKE_DETECTOR_H
#define SMOKE_DETECTOR_H

#include "Device.h"
#include <iostream>
#include <string>
#include <vector>

// SecuritySystem sınıfını önceden bildiriyoruz ki hata vermesin
class SecuritySystem;

class SmokeDetector : public Device {
public:
  SmokeDetector(int id, std::string n) : Device(id, n) {
    isPowered = true; // Always on by default
  }

  void togglePower() override {
    // LLR-016: Critical devices cannot be turned OFF by user
    std::cout << "[SAFETY] Smoke Detector cannot be turned off manually!"
              << std::endl;
    // Force power to stay on
    isPowered = true;
  }
  
  bool getPowerStatus() const { return true; } // Always report as ON

  Device *clone() const override { return new SmokeDetector(deviceID, name); }
  std::string getType() const override { return "SmokeDetector"; }

  // Entegrasyon burada yapılıyor: SecuritySystem pointer'ı alıyor
  void detectSmoke(SecuritySystem *sys);

  std::vector<std::string> getActions() override {
    return {"Check Status", "SIMULATE SMOKE"};
  }

  void performAction(std::string actionName) override;
};

#endif