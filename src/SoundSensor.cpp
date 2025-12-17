#include "../include/SoundSensor.h"
#include "../include/SecuritySystem.h" // SecuritySystem ile konuştuğu için şart!
#include <iostream>

using namespace std;

// --- CONSTRUCTOR ---
SoundSensor::SoundSensor(int id, string n) : Device(id, n) {}

// --- TEMEL DEVICE METODLARI ---
void SoundSensor::togglePower() {
  isPowered = !isPowered;
  cout << ">> Sound Sensor is now " << (isPowered ? "ON" : "OFF") << endl;
}

Device *SoundSensor::clone() const { return new SoundSensor(deviceID, name); }

string SoundSensor::getType() const { return "SoundSensor"; }

// --- ÖZEL METODLAR ---
void SoundSensor::measureLevel(int db, SecuritySystem *sys) {
  cout << "Measuring noise level: " << db << "dB" << endl;
  // Eğer bir güvenlik sistemi bağlıysa ona rapor ver
  if (sys) {
    sys->checkNoiseLevel(db);
  }
}

// --- AKSİYON METODLARI ---
vector<string> SoundSensor::getActions() {
  return {"Toggle Power", "SIMULATE NOISE"};
}

void SoundSensor::performAction(string actionName) {
  if (actionName == "Toggle Power") {
    togglePower();
  } else if (actionName == "SIMULATE NOISE") {
    // Test amaçlı yüksek ses simüle ediyoruz
    measureLevel(85, nullptr);
  }
}