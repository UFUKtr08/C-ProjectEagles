#ifndef GAS_DETECTOR_H
#define GAS_DETECTOR_H

#include "Device.h"
#include <iostream>
#include <string>
#include <vector>

class SecuritySystem;

class GasDetector : public Device {
public:
  GasDetector(int id, std::string n) : Device(id, n) {
    isPowered = true; // Always on by default
  }

  void togglePower() override {
    // LLR-016: Critical devices cannot be turned OFF by user
    std::cout << "[SAFETY] Gas Detector cannot be turned off manually!"
              << std::endl;
    isPowered = true; // Force power to stay on
  }
  
  bool getPowerStatus() const { return true; } // Always report as ON

  Device *clone() const override { return new GasDetector(deviceID, name); }
  std::string getType() const override { return "GasDetector"; }

  void detectGas(SecuritySystem *sys);

  std::vector<std::string> getActions() override {
    return {"Check Status", "SIMULATE GAS LEAK"};
  }

  void performAction(std::string actionName) override;
};

#endif
