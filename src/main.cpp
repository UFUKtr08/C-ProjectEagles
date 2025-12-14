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

  Alarm *mainAlarm = new Alarm(999, "Master Alarm");
  mainAlarm->togglePower(); 
  secSystem.setAlarm(mainAlarm);

  menu.displayWelcome();
  input.waitPressEnter();

  // --- VARSAYILAN CİHAZLAR (KORUNDU) ---
  Logger::getInstance()->log("Loading default devices...", "SYSTEM");
  deviceMgr.addDevice("Light", "Living Room Light");
  deviceMgr.addDevice("TV", "Smart TV");
  deviceMgr.addDevice("Curtain", "Balcony Curtain");
  deviceMgr.addDevice("Light", "Toilet Light");      // Fan bunu dinleyecek
  deviceMgr.addDevice("SmartFan", "Bathroom Fan");   // Otomatik fan
  
  // Test etmen için bir de "Yetenekli" cihaz ekleyelim:
  deviceMgr.addDevice("Stove", "Kitchen Stove");     // Gaz kaçağı testi için

  bool isRunning = true;
  while (isRunning) {
    menu.displayOptions();
    // Ekstra dinamik seçenekleri elle gösterelim (Menü classını değiştirmeden)
    cout << "[11] Wait / Pass Time (Trigger Automations)" << endl;

    int choice = input.getIntInput(1, 11, "\n>> Select Option: ");
    vector<Device *> &currentDevices = deviceMgr.getDevicesRef();

    switch (choice) {
    case 1: deviceMgr.listDevices(); input.waitPressEnter(); break;

    case 2: // TAM OTOMATİK CİHAZ EKLEME
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

    case 3: 
        deviceMgr.removeDevice(input.getIntInput(0, 1000, "Device ID: ")); 
        input.waitPressEnter(); break;

    case 4: // POWER ON
    {
        int id = input.getIntInput(0, 1000, "ID: ");
        Device* d = deviceMgr.getDevice(id);
        if(d && !d->getPowerStatus()) {
            d->togglePower();
            // Otomasyon (Tuvalet ışığı kontrolü)
            if(d->getType() == "Light") deviceMgr.notifyLightSwitch(true, d->getName());
        } else cout << "!! Error/Already ON" << endl;
        input.waitPressEnter(); break;
    }

    case 5: // POWER OFF
    {
        int id = input.getIntInput(0, 1000, "ID: ");
        Device* d = deviceMgr.getDevice(id);
        if(d && d->getPowerStatus()) {
            d->togglePower();
            // Otomasyon (Tuvalet ışığı kontrolü)
            if(d->getType() == "Light") deviceMgr.notifyLightSwitch(false, d->getName());
        } else cout << "!! Error/Already OFF" << endl;
        input.waitPressEnter(); break;
    }

    case 6: // MODLAR
    {
        cout << "[1] Normal [2] Party [3] Cinema" << endl;
        int m = input.getIntInput(1, 3, "Mode: ");
        if(m==1) modeMgr.setMode(new NormalMode(), currentDevices);
        else if(m==2) modeMgr.setMode(new PartyMode(), currentDevices);
        else if(m==3) modeMgr.setMode(new CinemaMode(), currentDevices);
        input.waitPressEnter(); break;
    }

    case 7: modeMgr.restorePreviousState(currentDevices); input.waitPressEnter(); break;

    case 8: // --- TAM OTOMATİK SİMÜLASYON MENÜSÜ ---
    {
        cout << "\n--- AVAILABLE ACTIONS ---" << endl;
        
        // Bu liste dinamik oluşturulur: <Cihaz*, AksiyonAdı>
        vector< pair<Device*, string> > actionList;
        int index = 1;

        for(size_t i=0; i<currentDevices.size(); i++) {
            // Cihaza soruyoruz: "Neler yapabilirsin?"
            vector<string> acts = currentDevices[i]->getActions();
            for(size_t j=0; j<acts.size(); j++) {
                cout << "[" << index << "] " << acts[j] << " (" << currentDevices[i]->getName() << ")" << endl;
                // Seçeneği kaydet (C++98 uyumlu pair)
                actionList.push_back(make_pair(currentDevices[i], acts[j]));
                index++;
            }
        }

        if(actionList.empty()) {
            cout << ">> No actions available on current devices." << endl;
        } else {
            int sel = input.getIntInput(1, index-1, "Select Action: ");
            // Seçilen cihazın ilgili fonksiyonunu çalıştır
            actionList[sel-1].first->performAction(actionList[sel-1].second);
        }
        input.waitPressEnter(); break;
    }

    case 9: cout << "MSH v3.0" << endl; input.waitPressEnter(); break;
    case 10: isRunning = false; cout << "Bye!" << endl; break;
    
    case 11: // WAIT / PASS TIME
        deviceMgr.updateSystemLoops();
        input.waitPressEnter();
        break;
    }
  }
  delete mainAlarm;
  return 0;
}