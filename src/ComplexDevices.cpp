#include "../include/ComplexDevices.h"
#include <iostream>

using namespace std;

// --- Burner Implementation ---
void Burner::setFire(bool status) { isOn = status; }

// --- Stove Implementation ---
Stove::Stove(int id, std::string n) : Device(id, n), gasLeakDetected(false) {
  for (int i = 0; i < 4; i++) {
    burners.push_back(Burner());
  }
}

Stove::~Stove() {}

void Stove::togglePower() {
  if (gasLeakDetected) {
    cout << "[SAFETY LOCK] Cannot turn on Stove while gas leak is detected!"
         << endl;
    return;
  }
  cout << "Stove power toggled." << endl;
}

Device *Stove::clone() const {
  return new Stove(deviceID + 100, name + "_Clone");
}

string Stove::getType() const { return "Stove"; }

void Stove::controlBurner(int index, bool status) {
  if (gasLeakDetected && status == true) {
    cout << "[DANGER] Cannot ignite burner during Gas Leak!" << endl;
    return;
  }

  if (index >= 0 && index < burners.size()) {
    burners[index].setFire(status);
    cout << "Burner " << index + 1 << " is now " << (status ? "ON" : "OFF")
         << endl;
  }
}

void Stove::onGasDetected() {
  gasLeakDetected = true;
  cout << "\n!!! CRITICAL ALERT: GAS LEAK DETECTED at " << name << " !!!"
       << endl;
  cout << "-> Initiating Emergency Shutdown..." << endl;
  toggleAll(false); // Tüm ocakları kapat
}

void Stove::simulateGasLeak() {
  cout << ">> SIMULATION: Injecting Gas Leak Event..." << endl;
  onGasDetected();
}

void Stove::operate() {
  if (gasLeakDetected) {
    cout << "[ALERT] Stove is in SAFETY LOCKOUT mode due to Gas Leak." << endl;
  } else {
    cout << "Stove is operating normally." << endl;
  }
}

vector<string> Stove::getActions() {
  return {"Toggle Power", "Ignite Burner 1", "Shut Down All",
          "SIMULATE GAS LEAK"};
}

void Stove::performAction(string actionName) {
  if (actionName == "Toggle Power")
    togglePower();
  else if (actionName == "Shut Down All")
    toggleAll(false);
  else if (actionName == "Ignite Burner 1")
    controlBurner(0, true);
  else if (actionName == "SIMULATE GAS LEAK")
    simulateGasLeak();
}

bool Stove::getPowerStatus() const { return true; }

string Stove::getName() const { return name; }

// --- IComplexControl IMPLEMENTASYONU ---
void Stove::showSubComponents() {
  cout << "--- Stove Burners Status ---" << endl;
  for (size_t i = 0; i < burners.size(); ++i) {
    cout << "Burner " << i + 1 << ": " << (burners[i].isOn ? "[ON]" : "[OFF]")
         << endl;
  }
}

void Stove::operateSubComponent(int index, bool turnOn) {
  controlBurner(index - 1, turnOn);
}

void Stove::toggleAll(bool turnOn) {
  for (auto &burner : burners) {
    burner.setFire(turnOn);
  }
  cout << "All burners turned " << (turnOn ? "ON" : "OFF") << endl;
}

int Stove::getSubComponentCount() { return burners.size(); }

// --- SmartFaucet Implementation ---
SmartFaucet::SmartFaucet(int id, std::string n)
    : Device(id, n), usageDuration(0), maxSafetyLimit(5), isLeaking(false), floodPreventionEnabled(true) {}

void SmartFaucet::togglePower() {
  if (isLeaking) {
    cout << "[SAFETY] Fixing leak before turning on..." << endl;
    isLeaking = false;
    usageDuration = 0;
  }
  cout << "Faucet toggled. Water is flowing." << endl;
  usageDuration = 1; // Başlat
}

Device *SmartFaucet::clone() const {
  return new SmartFaucet(deviceID + 100, name + "_Clone");
}

string SmartFaucet::getType() const { return "SmartFaucet"; }

void SmartFaucet::checkFloodRisk() {
  if (!floodPreventionEnabled) {
    return; // Feature disabled
  }
  
  // Risk 1: Süre aşımı
  if (usageDuration > maxSafetyLimit) {
    cout << "\n!!! FLOOD ALERT: Faucet running too long! Duration: "
         << usageDuration << endl;
    cout << "-> Auto-shutting off water." << endl;
    usageDuration = 0; // Kapat
  }
  // Risk 2: Fiziksel Sızıntı Simülasyonu
  else if (isLeaking) {
    cout << "\n!!! FLOOD ALERT: Physical Leak Detected!" << endl;
    cout << "-> Emergency Shutoff Triggered." << endl;
    usageDuration = 0;
  }
}

void SmartFaucet::toggleFloodPrevention() {
  floodPreventionEnabled = !floodPreventionEnabled;
  cout << ">> Flood Prevention is now " << (floodPreventionEnabled ? "ENABLED" : "DISABLED") << endl;
}

void SmartFaucet::simulateWaterLeak() {
  cout << ">> SIMULATION: Burst Pipe / Leak Event triggered!" << endl;
  isLeaking = true;
  checkFloodRisk();
}

void SmartFaucet::operate() {
  // Eğer musluk açıksa süreyi artır
  if (usageDuration > 0) {
    usageDuration++;
    cout << "Faucet is running... Duration: " << usageDuration << "/"
         << maxSafetyLimit << endl;
    checkFloodRisk();
  } else {
    cout << "Faucet is currently off." << endl;
  }
}

vector<string> SmartFaucet::getActions() {
  return {"Toggle", "Check Risk", "Toggle Flood Prevention", "SIMULATE FLOOD"};
}

void SmartFaucet::performAction(string actionName) {
  if (actionName == "Toggle")
    togglePower();
  else if (actionName == "Toggle Flood Prevention")
    toggleFloodPrevention();
  else if (actionName == "SIMULATE FLOOD")
    simulateWaterLeak();
  else if (actionName == "Check Risk")
    checkFloodRisk();
}

// --- SmartFan Implementation ---
SmartFan::SmartFan(int id, std::string n)
    : Device(id, n), autoModeEnabled(true), timer(0) {}

void SmartFan::togglePower() {
  isPowered = !isPowered;
  cout << ">> Fan is now " << (isPowered ? "ON" : "OFF") << endl;
}

Device *SmartFan::clone() const {
  return new SmartFan(deviceID + 100, name + "_Clone");
}

string SmartFan::getType() const { return "SmartFan"; }

void SmartFan::onLightStatusChanged(bool isLightOn) {
  if (autoModeEnabled && isLightOn) {
    cout << "Light is on, Fan starting..." << endl;
  }
}

void SmartFan::updateTimer() { timer++; }

void SmartFan::operate() { updateTimer(); }

void SmartFan::toggleAutoMode() {
  autoModeEnabled = !autoModeEnabled;
  cout << ">> Auto-Ventilation is now " << (autoModeEnabled ? "ENABLED" : "DISABLED") << endl;
}

vector<string> SmartFan::getActions() { return {"Toggle Power", "Toggle Auto-Ventilation"}; }

void SmartFan::performAction(string actionName) {
  if (actionName == "Toggle Power")
    togglePower();
  else if (actionName == "Toggle Auto-Ventilation")
    toggleAutoMode();
}