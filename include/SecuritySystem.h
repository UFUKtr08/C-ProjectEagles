#ifndef SECURITY_SYSTEM_H
#define SECURITY_SYSTEM_H

#include "Device.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// Forward Declarations
class Camera;
class Alarm;

// Chain of Responsibility - Base Handler (LLR-031)
class SecurityHandler {
public:
  SecurityHandler *nextHandler;

  SecurityHandler() : nextHandler(nullptr) {}
  virtual ~SecurityHandler() {}

  void setNext(SecurityHandler *next) { nextHandler = next; }

  virtual void handle(std::string breachType) {
    if (nextHandler) {
      nextHandler->handle(breachType);
    }
  }
};

// Handler 1: Trigger Alarm (LLR-031)
class AlarmHandler : public SecurityHandler {
public:
  void handle(std::string breachType) override {
    std::cout << "\n>> [STEP 1] ALARM TRIGGERED!" << std::endl;
    std::cout << "   !!! WEE-WOO-WEE-WOO !!!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    SecurityHandler::handle(breachType);
  }
};

// Handler 2: Turn on Lights (LLR-031)
class LightsHandler : public SecurityHandler {
public:
  void handle(std::string breachType) override {
    std::cout << ">> [STEP 2] All lights turning ON for visibility..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    SecurityHandler::handle(breachType);
  }
};

// Handler 3: Call Police/Fire Station (LLR-031, LLR-036)
class EmergencyCallHandler : public SecurityHandler {
public:
  void handle(std::string breachType) override {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (breachType == "FIRE_DETECTED" || breachType == "GAS_DETECTED") {
      std::cout << ">> [STEP 3] CALLING FIRE STATION... 110" << std::endl;
    } else {
      std::cout << ">> [STEP 3] CALLING POLICE... 155" << std::endl;
    }
    std::cout << ">> Emergency services notified!" << std::endl;
  }
};

class SecuritySystem {
private:
  SecurityHandler *chainHead;
  bool alarmAcknowledged;

public:
  SecuritySystem() : alarmAcknowledged(false) {
    // Build Chain of Responsibility: Alarm -> Lights -> Emergency Call
    AlarmHandler *alarm = new AlarmHandler();
    LightsHandler *lights = new LightsHandler();
    EmergencyCallHandler *emergency = new EmergencyCallHandler();

    alarm->setNext(lights);
    lights->setNext(emergency);

    chainHead = alarm;
  }

  ~SecuritySystem() {
    // Clean up entire chain properly
    SecurityHandler *current = chainHead;
    while (current) {
      SecurityHandler *next = current->nextHandler;
      current->nextHandler = nullptr;
      delete current;
      current = next;
    }
  }

  void acknowledgeAlarm() {
    alarmAcknowledged = true;
    std::cout << ">> Alarm acknowledged by user." << std::endl;
  }

  void resetAcknowledgement() { alarmAcknowledged = false; }

  // Main breach notification with Chain of Responsibility (LLR-031, LLR-032)
  void notifyBreach(std::string deviceName, std::string breachType) {
    std::cout << "\n!!! SECURITY ALERT !!!" << std::endl;
    std::cout << "Source: " << deviceName << " | Type: " << breachType
              << std::endl;
    std::cout << ">> System is taking emergency actions..." << std::endl;
    std::cout << ">> (Press Enter to acknowledge alarm during sequence)"
              << std::endl;

    // Execute Chain of Responsibility with time delays (LLR-032)
    if (chainHead) {
      chainHead->handle(breachType);
    }
  }

  // Noise level check for Good Neighbor Mode (LLR-053)
  void checkNoiseLevel(int db) {
    if (db > 70) {
      std::cout << "\n>> HIGH NOISE LEVEL DETECTED (" << db << "dB)!"
                << std::endl;
      std::cout << ">> WARNING: Please reduce noise levels for neighbors!"
                << std::endl;
    }
  }
};

#endif
