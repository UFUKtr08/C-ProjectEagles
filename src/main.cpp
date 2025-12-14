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
#include "../include/Modes.h"
#include "../include/SecuritySystem.h"

using namespace std;

int main() {
  Logger::getInstance()->log("--- SYSTEM BOOT SEQUENCE INITIATED ---", "SYSTEM");

  MainMenu menu;
  InputHandler input;
  DeviceManager deviceMgr;
  ModeManager modeMgr;
  SecuritySystem secSystem;

  // Alarm sistemi kurulumu
  Alarm *mainAlarm = new Alarm(999, "Master Alarm");
  mainAlarm->togglePower(); 
  secSystem.setAlarm(mainAlarm);

  menu.displayWelcome();
  input.waitPressEnter();

  // --- VARSAYILAN CİHAZLAR ---
  Logger::getInstance()->log("Loading default devices...", "SYSTEM");
  deviceMgr.addDevice("Light", "Living Room Light");
  deviceMgr.addDevice("TV", "Smart TV");
  deviceMgr.addDevice("Curtain", "Balcony Curtain");
  deviceMgr.addDevice("Light", "Toilet Light");      
  deviceMgr.addDevice("SmartFan", "Bathroom Fan");   
  deviceMgr.addDevice("Stove", "Kitchen Stove");     

  bool isRunning = true;
  while (isRunning) {
    menu.displayOptions();
    cout << "[11] Wait / Pass Time (Trigger Automations)" << endl;

    int choice = input.getIntInput(1, 11, "\n>> Select Option: ");
    vector<Device *> &currentDevices = deviceMgr.getDevicesRef();

    switch (choice) {
    case 1: 
        // Zaten listeyi gosteriyor
        deviceMgr.listDevices(); 
        input.waitPressEnter(); 
        break;

    case 2: // Device Ekleme
    { 
        cout << "\n--- Supported Devices ---" << endl;
        vector<string> types = DeviceFactory::getAvailableTypes();
        for(size_t i=0; i<types.size(); i++) cout << "- " << types[i] << endl;
        
        string t = input.getStringInput("Type: ");
        string n = input.getStringInput("Name: ");
        deviceMgr.addDevice(t, n);
        input.waitPressEnter();
        break;
    }

    case 3: // Device Silme
        // Silmeden once de neyi silecegimizi gormek isteriz
        deviceMgr.listDevices(); 
        deviceMgr.removeDevice(input.getIntInput(0, 1000, "Enter Device ID to Remove: ")); 
        input.waitPressEnter(); 
        break;

    case 4: // POWER ON (DUZELTİLDİ)
    {
        // 1. ADIM: Önce listeyi ekrana basıyoruz (Prototipindeki gibi)
        deviceMgr.listDevices();
        
        // 2. ADIM: Sonra ID istiyoruz
        int id = input.getIntInput(0, 1000, "Enter Device ID to turn ON: ");
        Device* d = deviceMgr.getDevice(id);
        
        if(d) {
            if (!d->getPowerStatus()) {
                d->togglePower();
                // Otomasyon kontrolü
                if(d->getType() == "Light") deviceMgr.notifyLightSwitch(true, d->getName());
            } else {
                cout << ">> Info: Device is already ON." << endl;
            }
        } else {
            cout << "!! Error: Device not found." << endl;
        }
        input.waitPressEnter(); 
        break;
    }

    case 5: // POWER OFF (DUZELTİLDİ)
    {
        // Burada da aynısını yapıyoruz
        deviceMgr.listDevices();
        
        int id = input.getIntInput(0, 1000, "Enter Device ID to turn OFF: ");
        Device* d = deviceMgr.getDevice(id);
        
        if(d) {
            if (d->getPowerStatus()) {
                d->togglePower();
                // Otomasyon kontrolü
                if(d->getType() == "Light") deviceMgr.notifyLightSwitch(false, d->getName());
            } else {
                cout << ">> Info: Device is already OFF." << endl;
            }
        } else {
            cout << "!! Error: Device not found." << endl;
        }
        input.waitPressEnter(); 
        break;
    }

    case 6: // Change Mode
    {
        cout << "[1] Normal [2] Party [3] Cinema" << endl;
        int m = input.getIntInput(1, 3, "Select Mode: ");
        if(m==1) modeMgr.setMode(new NormalMode(), currentDevices);
        else if(m==2) modeMgr.setMode(new PartyMode(), currentDevices);
        else if(m==3) modeMgr.setMode(new CinemaMode(), currentDevices);
        input.waitPressEnter(); break;
    }

    case 7: 
        modeMgr.restorePreviousState(currentDevices); 
        input.waitPressEnter(); 
        break;

    case 8: // Manual / Simulation Actions
    {
        cout << "\n--- AVAILABLE ACTIONS ---" << endl;
        vector< pair<Device*, string> > actionList;
        int index = 1;

        for(size_t i=0; i<currentDevices.size(); i++) {
            vector<string> acts = currentDevices[i]->getActions();
            for(size_t j=0; j<acts.size(); j++) {
                cout << "[" << index << "] " << acts[j] << " (" << currentDevices[i]->getName() << ")" << endl;
                actionList.push_back(make_pair(currentDevices[i], acts[j]));
                index++;
            }
        }

        if(actionList.empty()) {
            cout << ">> No special actions available." << endl;
        } else {
            int sel = input.getIntInput(1, index-1, "Select Action Number: ");
            actionList[sel-1].first->performAction(actionList[sel-1].second);
        }
        input.waitPressEnter(); break;
    }

    case 9: cout << "MSH v3.0 - C++98 Edition" << endl; input.waitPressEnter(); break;
    case 10: isRunning = false; cout << "Shutting down..." << endl; break;
    
    case 11: 
        deviceMgr.updateSystemLoops();
        input.waitPressEnter();
        break;
    }
  }
  delete mainAlarm;
  return 0;
}