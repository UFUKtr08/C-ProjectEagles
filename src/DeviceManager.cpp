#include "../include/DeviceManager.h"

DeviceManager::DeviceManager() : nextID(1) {}

DeviceManager::~DeviceManager() {
    // C++98'de akıllı pointer yok, elle temizliyoruz
    for (size_t i = 0; i < devices.size(); ++i) {
        delete devices[i];
    }
    devices.clear();
}

void DeviceManager::addDevice(string type, string name) {
    // FACTORY METHOD Kullanımı
    Device* newDevice = DeviceFactory::createDevice(type);
    
    if (newDevice) {
        newDevice->setID(nextID++);
        newDevice->setName(name);
        devices.push_back(newDevice);
        cout << ">> Device Added: " << name << " (" << type << ")" << endl;
    } else {
        cout << "!! Error: Unknown device type: " << type << endl;
    }
}

void DeviceManager::addClone(int targetID, string newName) {
    Device* target = getDevice(targetID);
    if (target) {
        // PROTOTYPE PATTERN Kullanımı
        Device* clonedDevice = target->clone();
        
        // Kopyalanan cihazın kimliğini değiştiriyoruz
        clonedDevice->setID(nextID++);
        clonedDevice->setName(newName);
        
        devices.push_back(clonedDevice);
        cout << ">> Device Cloned: " << newName << " from ID " << targetID << endl;
    } else {
        cout << "!! Error: Device with ID " << targetID << " not found." << endl;
    }
}

void DeviceManager::removeDevice(int targetID) {
    for (std::vector<Device*>::iterator it = devices.begin(); it != devices.end(); ++it) {
        if ((*it)->getID() == targetID) {
            delete *it; // Hafızadan sil
            devices.erase(it); // Listeden sil
            cout << ">> Device Removed: ID " << targetID << endl;
            return;
        }
    }
    cout << "!! Error: Device not found." << endl;
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
        if (devices[i]->getID() == id) {
            return devices[i];
        }
    }
    return NULL;
}