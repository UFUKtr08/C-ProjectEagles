#include "../include/DeviceManager.h"
#include "../include/ComplexDevices.h" // Bu include ŞART!

DeviceManager::DeviceManager() : nextID(1) {}

DeviceManager::~DeviceManager() {
    for (size_t i = 0; i < devices.size(); ++i) delete devices[i];
    devices.clear();
}

void DeviceManager::addDevice(string type, string name) {
    Device* newDevice = DeviceFactory::createDevice(type);
    if (newDevice) {
        newDevice->setID(nextID++);
        newDevice->setName(name);
        devices.push_back(newDevice);
        cout << ">> Device Added: " << name << " (" << type << ")" << endl;
    } else {
        cout << "!! Error: Unknown device type." << endl;
    }
}

void DeviceManager::addClone(int targetID, string newName) {
    Device* target = getDevice(targetID);
    if (target) {
        Device* clonedDevice = target->clone();
        clonedDevice->setID(nextID++);
        clonedDevice->setName(newName);
        devices.push_back(clonedDevice);
        cout << ">> Device Cloned: " << newName << endl;
    }
}

void DeviceManager::removeDevice(int targetID) {
    for (std::vector<Device*>::iterator it = devices.begin(); it != devices.end(); ++it) {
        if ((*it)->getID() == targetID) {
            delete *it;
            devices.erase(it);
            cout << ">> Device Removed: ID " << targetID << endl;
            return;
        }
    }
}

void DeviceManager::listDevices() {
    cout << "\n--- Connected Devices ---" << endl;
    for (size_t i = 0; i < devices.size(); ++i) {
        cout << "ID: " << devices[i]->getID() 
             << " | Type: " << devices[i]->getType()
             << " | Name: " << devices[i]->getName()
             << " | Power: " << (devices[i]->getPowerStatus() ? "ON" : "OFF") 
             << endl;
    }
    cout << "-------------------------\n" << endl;
}

Device* DeviceManager::getDevice(int id) {
    for (size_t i = 0; i < devices.size(); ++i) {
        if (devices[i]->getID() == id) return devices[i];
    }
    return NULL;
}

// --- OTOMASYON MANTIĞI BURADA ---

void DeviceManager::notifyLightSwitch(bool isLightOn, string lightName) {
    // SADECE "Toilet" veya "Tuvalet" isminde geçen ışıklar fanı tetikler
    if (lightName.find("Toilet") == string::npos && lightName.find("Tuvalet") == string::npos) {
        return; 
    }

    cout << ">> [Automation] Toilet light toggled. Checking fans..." << endl;

    for (size_t i = 0; i < devices.size(); ++i) {
        if (devices[i]->getType() == "SmartFan") {
            // SmartFan'ın kendi fonksiyonunu çağırıyoruz
            ((SmartFan*)devices[i])->onLightStatusChanged(isLightOn);
        }
    }
}

void DeviceManager::updateSystemLoops() {
    cout << "\n--- System Update (Time Passing) ---" << endl;
    for (size_t i = 0; i < devices.size(); ++i) {
        
        // Musluk açık mı unutuldu? Kontrol et.
        if (devices[i]->getType() == "SmartFaucet") {
            ((SmartFaucet*)devices[i])->checkFloodRisk();
        }
        
        // Fanın süresi doldu mu? Kontrol et.
        else if (devices[i]->getType() == "SmartFan") {
            ((SmartFan*)devices[i])->updateTimer();
        }
    }
}