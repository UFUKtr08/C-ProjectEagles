#include "../include/Alarm.h"
#include <iostream>

using namespace std;

// --- CONSTRUCTOR (Eksikti, eklendi) ---
Alarm::Alarm(int id, string n)
    : Device(id, n), isTriggered(false), pinCode("1234") {}

// --- DEVICE OVERRIDES ---
void Alarm::togglePower() {
  if (isTriggered) {
    cout << "[ACCESS DENIED] Alarm is TRIGGERED! Cannot turn off without PIN "
            "reset."
         << endl;
  } else {
    // LLR-016: Critical devices cannot be turned OFF by user
    cout << "[SAFETY] Alarm system cannot be turned off manually for security reasons!"
         << endl;
  }
}

Device *Alarm::clone() const { return new Alarm(deviceID, name); }

string Alarm::getType() const { return "Alarm"; }

// --- ÖZEL METODLAR ---
void Alarm::triggerAlarm() {
  if (!isTriggered) {
    isTriggered = true;
    cout << "\n!!! WEE-WOO-WEE-WOO !!!" << endl;
    cout << "!!! SECURITY ALERT !!!" << endl;
  }
}

void Alarm::resetAlarm(string pin) {
  if (pin == pinCode) {
    isTriggered = false;
    cout << "[SYSTEM] PIN Accepted. Alarm reset." << endl;
  } else {
    cout << "[ERROR] Invalid PIN!" << endl;
  }
}

bool Alarm::getTriggerStatus() const { return isTriggered; }

// --- ACTION HANDLING ---
vector<string> Alarm::getActions() {
  return {"Trigger (Test)", "Reset (Enter PIN)", "Toggle Power"};
}

void Alarm::performAction(string actionName) {
  if (actionName == "Trigger (Test)")
    triggerAlarm();
  else if (actionName == "Reset (Enter PIN)") {
    cout << "Enter PIN (Simulated: 1234): ";
    resetAlarm("1234");
  } else if (actionName == "Toggle Power")
    togglePower();
}