#include <iostream>
#include <string>
#include <vector>

// Header Dosyalari
#include "../include/Alarm.h"
#include "../include/DeviceManager.h"
#include "../include/IComplexControl.h"
#include "../include/InputHandler.h"
#include "../include/Logger.h"
#include "../include/MainMenu.h"
#include "../include/ModeManager.h"
#include "../include/Modes.h"
#include "../include/SecuritySystem.h"

using namespace std;

// YARDIMCI FONKSİYON: Sade Liste
void printSimpleList(vector<Device *> &devices) {
  cout << "\n--- EV DURUMU ---" << endl;
  for (size_t i = 0; i < devices.size(); ++i) {
    string status = devices[i]->getPowerStatus() ? "ON" : "OFF";
    cout << "[" << devices[i]->getID() << "] " << devices[i]->getName() << " ["
         << status << "]" << endl;
  }
}

int main() {
  Logger::getInstance()->log("--- SYSTEM BOOT SEQUENCE INITIATED ---",
                             "SYSTEM");

  MainMenu menu;
  InputHandler input;
  DeviceManager deviceMgr;
  ModeManager modeMgr;
  SecuritySystem secSystem;
  (void)secSystem;

  // Alarm sistemi kurulumu
  Alarm *mainAlarm = new Alarm(999, "Master Alarm");
  mainAlarm->togglePower();

  menu.displayWelcome();
  input.waitPressEnter();

  // --- VARSAYILAN CİHAZLAR ---
  Logger::getInstance()->log("Loading default devices...", "SYSTEM");

  deviceMgr.addDevice("Light", "Living Room Light");
  deviceMgr.addDevice("TV", "Smart TV");
  deviceMgr.addDevice("Curtain", "Balcony Curtain");
  deviceMgr.addDevice("Light", "Toilet Light");
  deviceMgr.addDevice("SmartFan", "Bathroom Fan");
  deviceMgr.addDevice("SmartFaucet", "Kitchen Faucet");
  deviceMgr.addDevice("Stove", "Kitchen Stove");

  // Güvenlik Cihazları
  deviceMgr.addDevice("SmokeDetector", "Kitchen Smoke Detector");
  deviceMgr.addDevice("Camera", "Main Door Camera");
  deviceMgr.addDevice("SoundSensor", "Saloon Noise Sensor");

  // --- GÜVENLİK BAŞLANGIÇ KONTROLÜ (GÜNCELLENDİ) ---
  // Ses Sensörü buradan çıkarıldı, sadece Kamera ve Duman Dedektörü zorla
  // açılıyor.
  vector<Device *> &allDevs = deviceMgr.getDevicesRef();
  for (size_t i = 0; i < allDevs.size(); i++) {
    string t = allDevs[i]->getType();

    // SoundSensor ARTIK BURADA YOK
    if (t == "Camera" || t == "SmokeDetector") {
      if (!allDevs[i]->getPowerStatus()) {
        allDevs[i]->togglePower();
      }
    }
  }
  // ------------------------------------

  bool isRunning = true;
  while (isRunning) {
    menu.displayOptions();

    int choice = input.getIntInput(1, 12, "\n>> Select Option: ");
    vector<Device *> &currentDevices = deviceMgr.getDevicesRef();

    switch (choice) {
    case 1:
      deviceMgr.listDevices();
      input.waitPressEnter();
      break;

    case 2: // Device Ekleme
    {
      cout << "\n--- Supported Devices ---" << endl;
      vector<string> types = DeviceFactory::getAvailableTypes();
      for (size_t i = 0; i < types.size(); i++)
        cout << "- " << types[i] << endl;

      string t = input.getStringInput("Type: ");
      string n = input.getStringInput("Name: ");
      deviceMgr.addDevice(t, n);
      input.waitPressEnter();
      break;
    }

    case 3: // Device Silme
      printSimpleList(currentDevices);
      deviceMgr.removeDevice(
          input.getIntInput(0, 1000, "Enter Device ID to Remove: "));
      input.waitPressEnter();
      break;

    case 4: // POWER ON (Cihaz Açma)
    {
      deviceMgr.listDevices();
      cout << "ACMAK istediginiz Cihaz ID (veya 0 Iptal): ";
      int id;
      if (!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        id = -1;
      }

      if (id != 0) {
        Device *d = deviceMgr.getDevice(id);
        if (d) {
          // --- POLİMORFİZM KONTROLÜ ---
          // "Bu cihaz Karmaşık Kontrol (IComplexControl) yeteneğine sahip mi?"
          IComplexControl *complexDev = dynamic_cast<IComplexControl *>(d);

          if (complexDev) {
            // EVET, KARMAŞIK CİHAZ (Örn: Stove)
            cout << "\n========================================" << endl;
            cout << "      DETAYLI ACMA KONTROLU" << endl;
            cout << "========================================" << endl;

            // 1. Önce hangi gözlerin açık/kapalı olduğunu göster
            complexDev->showSubComponents();

            cout << "\n[1] TUM gozleri AC" << endl;
            cout << "[2] Sadece belirli bir gozu AC" << endl;
            cout << "[0] Iptal" << endl;

            int subChoice = input.getIntInput(0, 2, "Seciminiz: ");

            if (subChoice == 1) {
              complexDev->toggleAll(true); // Hepsini Aç
            } else if (subChoice == 2) {
              int count = complexDev->getSubComponentCount();
              int partIdx = input.getIntInput(
                  1, count, "Hangi goz acilsin (Numara girin): ");
              complexDev->operateSubComponent(partIdx, true); // Tekli Aç
            } else {
              cout << ">> Islem iptal edildi." << endl;
            }
          } else {
            // HAYIR, STANDART CİHAZ (Örn: Light, TV)
            if (!d->getPowerStatus()) {
              d->togglePower();
              if (d->getType() == "Light")
                deviceMgr.notifyLightSwitch(true, d->getName());
              if (d->getType() == "SoundSensor")
                cout << ">> Sound Sensor ACTIVATED manually." << endl;
              // Standart mesaj cihazın kendi içinde (togglePower) veriliyor
              // olabilir, vermiyorsa buraya cout eklenebilir.
            } else
              cout << ">> " << d->getName() << " zaten ACIK." << endl;
          }
        } else
          cout << "!! Hata: Cihaz bulunamadi." << endl;
      }
      input.waitPressEnter();
      break;
    }

    case 5: // POWER OFF (Cihaz Kapatma)
    {
      deviceMgr.listDevices();
      cout << "KAPATMAK istediginiz Cihaz ID (veya 0 Iptal): ";
      int id;
      if (!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        id = -1;
      }

      if (id != 0) {
        Device *d = deviceMgr.getDevice(id);
        if (d) {
          // --- POLİMORFİZM KONTROLÜ ---
          IComplexControl *complexDev = dynamic_cast<IComplexControl *>(d);

          if (complexDev) {
            // EVET, KARMAŞIK CİHAZ
            cout << "\n========================================" << endl;
            cout << "      DETAYLI KAPATMA KONTROLU" << endl;
            cout << "========================================" << endl;

            // Anlık durumu göster
            complexDev->showSubComponents();

            cout << "\n[1] TUM gozleri KAPAT" << endl;
            cout << "[2] Sadece belirli bir gozu KAPAT" << endl;
            cout << "[0] Iptal" << endl;

            int subChoice = input.getIntInput(0, 2, "Seciminiz: ");

            if (subChoice == 1) {
              complexDev->toggleAll(false); // Hepsini Kapat
            } else if (subChoice == 2) {
              int count = complexDev->getSubComponentCount();
              int partIdx = input.getIntInput(
                  1, count, "Hangi goz kapatilsin (Numara girin): ");
              complexDev->operateSubComponent(partIdx, false); // Tekli Kapat
            } else {
              cout << ">> Islem iptal edildi." << endl;
            }
          } else {
            // STANDART CİHAZ
            if (d->getPowerStatus()) {
              d->togglePower();
              if (d->getType() == "Light")
                deviceMgr.notifyLightSwitch(false, d->getName());
              if (d->getType() == "SoundSensor")
                cout << ">> Sound Sensor DEACTIVATED manually." << endl;
            } else
              cout << ">> " << d->getName() << " zaten KAPALI." << endl;
          }
        } else
          cout << "!! Hata: Cihaz bulunamadi." << endl;
      }
      input.waitPressEnter();
      break;
    }

    case 6: // Change Mode
    {
      cout << "[1] Normal [2] Evening [3] Party [4] Cinema [5] Sleep [6] Good Neighbor" << endl;
      int m = input.getIntInput(1, 6, "Select Mode: ");

      if (m == 1)
        modeMgr.setMode(new NormalMode(), currentDevices);
      else if (m == 2)
        modeMgr.setMode(new EveningMode(), currentDevices);
      else if (m == 3)
        modeMgr.setMode(new PartyMode(), currentDevices);
      else if (m == 4)
        modeMgr.setMode(new CinemaMode(), currentDevices);
      else if (m == 5)
        modeMgr.setMode(new SleepMode(), currentDevices);
      else if (m == 6)
        modeMgr.setMode(new GoodNeighborMode(), currentDevices);

      cout << "\n>> MODE CHANGE SUCCESSFUL: " << modeMgr.getCurrentModeName()
           << " Mode Activated." << endl;

      input.waitPressEnter();
      break;
    }

    case 7:
      modeMgr.restorePreviousState(currentDevices);
      input.waitPressEnter();
      break;

    case 8: // User Manual (LLR-004)
    {
      menu.displayManual();
      input.waitPressEnter();
      break;
    }

    case 9: // ABOUT MENÜSÜ
    {
      cout << "\n========================================" << endl;
      cout << "Proje Adi: My Sweet Home (MSH) v3.0" << endl;
      cout << "========================================" << endl;
      cout << "" << endl;
      cout << "Merve Selin Umit---220201028" << endl;
      cout << "Ufuk Yilmaz     ---210201024" << endl;
      cout << "Batuhan Kayalica---210201011" << endl;
      cout << "Baran Acur      ---210201036" << endl;
      cout << "Fatih Ozcan     ---210201028" << endl;
      cout << "Ridvan Serbes   ---210201038" << endl;
      cout << "========================================" << endl;
      input.waitPressEnter();
      break;
    }

    case 10:
      isRunning = false;
      cout << "Shutting down..." << endl;
      break;

    case 11: // Wait / Update System
      deviceMgr.updateSystemLoops();
      input.waitPressEnter();
      break;

    case 12: // Manual Device Actions
    {
      cout << "\n--- AVAILABLE DEVICE ACTIONS ---" << endl;
      vector<pair<Device *, string>> actionList;
      int index = 1;

      for (size_t i = 0; i < currentDevices.size(); i++) {
        vector<string> acts = currentDevices[i]->getActions();
        for (size_t j = 0; j < acts.size(); j++) {
          cout << "[" << index << "] " << acts[j] << " ("
               << currentDevices[i]->getName() << ")" << endl;
          actionList.push_back(make_pair(currentDevices[i], acts[j]));
          index++;
        }
      }

      if (actionList.empty()) {
        cout << ">> No special actions available." << endl;
      } else {
        int sel = input.getIntInput(1, index - 1, "Select Action Number: ");
        actionList[sel - 1].first->performAction(actionList[sel - 1].second);
      }
      input.waitPressEnter();
      break;
    }
    
    default:
      cout << ">> Invalid Command. Please select 1-12." << endl;
      break;
    }
  }
  delete mainAlarm;
  return 0;
}