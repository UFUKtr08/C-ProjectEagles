#include <iostream>
#include <string>
#include <vector>

// Header Dosyalari
#include "../include/Alarm.h"
#include "../include/DeviceManager.h"
#include "../include/InputHandler.h"
#include "../include/Logger.h"
#include "../include/MainMenu.h"
#include "../include/ModeManager.h"
#include "../include/Modes.h" // PartyMode, CinemaMode vb. icin
#include "../include/SecuritySystem.h"

using namespace std;

int main() {
  // 1. SISTEM BASLATMA
  Logger::getInstance()->log("--- SYSTEM BOOT SEQUENCE INITIATED ---",
                             "SYSTEM");

  MainMenu menu;
  InputHandler input;
  DeviceManager deviceMgr;
  ModeManager modeMgr;
  SecuritySystem secSystem;

  // Alarm Kurulumu
  Alarm *mainAlarm = new Alarm(999, "Master Alarm");
  mainAlarm->togglePower(); // Alarmi 'ARMED' yap
  secSystem.setAlarm(mainAlarm);

  menu.displayWelcome();
  input.waitPressEnter();

  // Varsayılan Cihazları Ekle
  Logger::getInstance()->log("Loading default devices...", "SYSTEM");
  deviceMgr.addDevice("Light", "Living Room Light");
  deviceMgr.addDevice("TV", "Smart TV");
  deviceMgr.addDevice("Curtain", "Balcony Curtain");

  bool isRunning = true;
  while (isRunning) {
    menu.displayOptions();

    int choice = input.getIntInput(1, 10, "\n>> Select Option: ");

    // Not: DeviceManager.h icine getDevicesRef() ekledigini varsayiyoruz.
    // Eger hata verirse include/DeviceManager.h'a sunu ekle:
    // std::vector<Device*>& getDevicesRef() { return devices; }
    vector<Device *> &currentDevices = deviceMgr.getDevicesRef();

    switch (choice) {
    case 1: // Get Home Status
      deviceMgr.listDevices();
      input.waitPressEnter();
      break;

    case 2: // Add Device
    { // <--- SÜSLÜ PARANTEZ ŞART (Değişken tanımladığımız için)
      string type =
          input.getStringInput("Enter Device Type (Light/TV/Curtain): ");
      string name = input.getStringInput("Enter Device Name: ");
      deviceMgr.addDevice(type, name);
      input.waitPressEnter();
      break;
    }

    case 3: // Remove Device
    {
      int id = input.getIntInput(0, 1000, "Enter Device ID to remove: ");
      deviceMgr.removeDevice(id);
      input.waitPressEnter();
      break;
    }

    case 4: // Power ON
    {
      int id = input.getIntInput(0, 1000, "Enter Device ID to turn ON: ");
      Device *d = deviceMgr.getDevice(id);
      if (d && !d->getPowerStatus())
        d->togglePower();
      else
        cout << "!! Device not found or already ON." << endl;
      input.waitPressEnter();
      break;
    }

    case 5: // Power OFF
    {
      int id = input.getIntInput(0, 1000, "Enter Device ID to turn OFF: ");
      Device *d = deviceMgr.getDevice(id);
      if (d && d->getPowerStatus())
        d->togglePower();
      else
        cout << "!! Device not found or already OFF." << endl;
      input.waitPressEnter();
      break;
    }

    case 6: // Change Mode
    {       // <--- BURAYA DA EKLEDIK
      cout << "\n[1] Normal Mode\n[2] Party Mode\n[3] Cinema Mode" << endl;
      int modeChoice = input.getIntInput(1, 3, "Select Mode: ");

      IMode *newMode = NULL;
      if (modeChoice == 1)
        newMode = new NormalMode();
      else if (modeChoice == 2)
        newMode = new PartyMode();
      else if (modeChoice == 3)
        newMode = new CinemaMode();

      if (newMode) {
        modeMgr.setMode(newMode, currentDevices);
      }
      input.waitPressEnter();
      break;
    }

    case 7: // Undo / Previous State
      modeMgr.restorePreviousState(currentDevices);
      input.waitPressEnter();
      break;

    case 8: // Manual / Sensor Test
    {       // <--- HATA VEREN YER BURASIYDI, PARANTEZLERI EKLEDIK
      cout << "\n--- SENSOR SIMULATION ---" << endl;
      cout << "[1] Trigger Motion (Camera)" << endl;
      cout << "[2] Trigger Smoke (Smoke Detector)" << endl;
      cout << "[3] Trigger Flood/Leak (Smart Faucet)"
           << endl; // <--- YENİ EKLENEN

      int simChoice = input.getIntInput(1, 3, "Select Simulation: ");

      if (simChoice == 1) {
        secSystem.notifyBreach("Hallway Camera", "MOTION");
      } else if (simChoice == 2) {
        secSystem.notifyBreach("Kitchen Detector", "FIRE");
      } else if (simChoice == 3) {
        // YENİ: Su taşma senaryosu
        secSystem.notifyBreach("Bathroom Faucet", "FLOOD");
      }

      input.waitPressEnter();
      break;
    }

    case 9: // About
      cout << "\nMy Sweet Home (MSH) v1.0" << endl;
      cout << "Developers: [Senin Adın] & Gemini" << endl;
      input.waitPressEnter();
      break;

    case 10: // Shutdown
      Logger::getInstance()->log("System Shutdown Requested.", "SYSTEM");
      isRunning = false;
      cout << "Goodbye!" << endl;
      break;
    }
  }

  delete mainAlarm;
  return 0;
}