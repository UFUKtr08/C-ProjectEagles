#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "Device.h"
#include "DeviceFactory.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread> // Bekleme süreleri için
#include <chrono> // Zaman birimleri için

using namespace std;

class DeviceManager {
private:
    vector<Device*> devices;

public:
    ~DeviceManager() {
        for (Device* d : devices) delete d;
        devices.clear();
    }

    void addDevice(string type, string name) {
        Device* newDevice = DeviceFactory::createDevice(type, devices.size() + 1, name);
        if (newDevice) {
            devices.push_back(newDevice);
            cout << ">> Device Added: " << name << endl;
        }
    }

    void removeDevice(int id) {
        for (auto it = devices.begin(); it != devices.end(); ++it) {
            if ((*it)->getID() == id) {
                cout << ">> Device Removed: " << (*it)->getName() << endl;
                delete *it;
                devices.erase(it);
                return;
            }
        }
        cout << "!! Device ID not found." << endl;
    }

    Device* getDevice(int id) {
        for (Device* d : devices) {
            if (d->getID() == id) return d;
        }
        return nullptr;
    }
    
    Device* getDeviceByName(string namePart) {
        for (Device* d : devices) {
            if (d->getName().find(namePart) != string::npos) return d;
        }
        return nullptr;
    }

    vector<Device*>& getDevicesRef() {
        return devices;
    }

    void listDevices() {
        cout << "\n--- CONNECTED DEVICES ---" << endl;
        for (const auto& device : devices) {
            device->displayStatus();
        }
    }

    // --- OTOMASYON MERKEZİ ---
    void notifyLightSwitch(bool isTurningOn, string lightName) {
        
        // Sadece "Toilet Light" için çalışır
        if (lightName.find("Toilet Light") != string::npos) {
            
            Device* fan = getDeviceByName("Bathroom Fan");
            
            if (fan) {
                if (isTurningOn) {
                    // SENARYO 1: Işık AÇILDI -> Fan Açıksa Kapat (Sessizlik Modu)
                    if (fan->getPowerStatus()) {
                        fan->togglePower();
                        // İSTEDİĞİN BİLDİRİM MESAJI BURADA:
                        cout << "\n>> [OTOMASYON] Tuvalet isigi ACILDI -> Fan sessizlik icin DURDURULDU." << endl;
                    }
                } 
                else {
                    // SENARYO 2: Işık KAPANDI -> Fan 1 DK (3 sn) Çalışsın
                    cout << "\n>> [OTOMASYON] Tuvalet isigi KAPANDI -> Fan havalandirma icin calistiriliyor..." << endl;
                    
                    if (!fan->getPowerStatus()) {
                        fan->togglePower(); // Fanı aç
                    }

                    cout << "   (Fan 1 dakika boyunca calisiyor... Lutfen bekleyin)" << endl;
                    
                    // Programı dondurarak bekletme (Test için 3 saniye)
                    this_thread::sleep_for(chrono::seconds(3));
                    
                    if (fan->getPowerStatus()) {
                        fan->togglePower(); // Fanı kapat
                        cout << ">> [OTOMASYON] Sure doldu -> Fan otomatik KAPATILDI." << endl;
                    }
                }
            } else {
                cout << "!! Uyari: Otomasyon icin 'Bathroom Fan' bulunamadi." << endl;
            }
        }
    }

    void notifySensorTrigger(string sensorType, string location) {
        // Sensör tetiklenmeleri buraya
    }
    
    void updateSystemLoops() {
        cout << ">> System loops updated based on active sensors..." << endl;
    }
};

#endif