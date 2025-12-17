#ifndef COMPLEX_DEVICES_H
#define COMPLEX_DEVICES_H

#include "Device.h"
#include "IComplexControl.h"
#include <string>
#include <vector>

class Burner {
public:
  bool isOn;
  Burner() : isOn(false) {}
  void setFire(bool status);
};

// --- SmartFan ---
class SmartFan : public Device {
private:
  bool autoModeEnabled;
  int timer;

public:
  SmartFan(int id, std::string name);

  void togglePower() override;
  Device *clone() const override;
  std::string getType() const override;

  void onLightStatusChanged(bool isLightOn);
  void updateTimer();
  void operate() override;
  std::vector<std::string> getActions() override;
  void performAction(std::string actionName) override;
  
  // LLR-046: Toggle auto-ventilation feature
  void toggleAutoMode();
  bool isAutoModeEnabled() const { return autoModeEnabled; }
};

// --- SmartFaucet ---
class SmartFaucet : public Device {
private:
  int usageDuration;
  int maxSafetyLimit;
  bool isLeaking;
  bool floodPreventionEnabled; // LLR-056: Toggleable flood prevention

public:
  SmartFaucet(int id, std::string name);

  void togglePower() override;
  Device *clone() const override;
  std::string getType() const override;

  void checkFloodRisk();
  void simulateWaterLeak();
  void operate() override;
  std::vector<std::string> getActions() override;
  void performAction(std::string actionName) override;
  
  // LLR-056: Toggle flood prevention feature
  void toggleFloodPrevention();
  bool isFloodPreventionEnabled() const { return floodPreventionEnabled; }
};

// --- Stove ---
class Stove : public Device, public IComplexControl {
private:
  std::vector<Burner> burners;
  bool gasLeakDetected; // Yeni: Gaz kaçağı durumu

public:
  Stove(int id, std::string name);
  ~Stove() override;

  void togglePower() override;
  Device *clone() const override;
  std::string getType() const override;

  void controlBurner(int index, bool status);
  void onGasDetected();
  void simulateGasLeak(); // Yeni: Simülasyon fonksiyonu

  void operate() override;
  std::vector<std::string> getActions() override;
  void performAction(std::string actionName) override;

  bool getPowerStatus() const;
  std::string getName() const;

  // IComplexControl
  void showSubComponents() override;
  void operateSubComponent(int index, bool turnOn) override;
  void toggleAll(bool turnOn) override;
  int getSubComponentCount() override;
};

#endif