#include "../include/SecuritySystem.h"
#include "../include/Logger.h"
#include "../include/Utils.h"
#include <iostream>

using namespace std;

SecuritySystem::SecuritySystem() { this->attachedAlarm = NULL; }

void SecuritySystem::setAlarm(Alarm *alm) { this->attachedAlarm = alm; }

void SecuritySystem::notifyBreach(string sensorName, string breachType) {
  cout << "\n>>> SECURITY ALERT: " << breachType << " detected by "
       << sensorName << " <<<" << endl;

  if (Logger::getInstance()) {
    string logMsg = "Breach Detected: " + breachType + " @ " + sensorName;
    Logger::getInstance()->log(logMsg, "SECURITY");
  }

  triggerSequence();
}

void SecuritySystem::triggerSequence() {
  cout << "--- SECURITY PROTOCOL STARTED ---" << endl;

  if (attachedAlarm) {
    attachedAlarm->trigger();
  } else {
    cout << "   (No alarm attached!)" << endl;
  }

  // Chain of Responsibility benzeri sirali islem
  cout << "2. Lights turned ON (Simulated)" << endl;
  cout << "3. Police notified (Simulated)" << endl;
}

void SecuritySystem::checkNoiseLevel(int db) {
  // 80dB uzeri gurultu supheli kabul edilir
  if (db > 80) {
    cout << "\n>>> [WARNING] HIGH NOISE LEVEL (" << db << "dB) <<<" << endl;
    if (Logger::getInstance()) {
      Logger::getInstance()->log(
          "High noise level detected: " + intToString(db) + "dB", "WARNING");
    }
  }
}