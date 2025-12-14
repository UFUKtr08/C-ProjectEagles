#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "DeviceFactory.h"
#include <vector>

class DeviceManager {
private:
  std::vector<Device *> devices;
  int nextID; // Otomatik ID vermek için

public:
  DeviceManager();
  ~DeviceManager(); // Memory cleanup şart!
  std::vector<Device *> &getDevicesRef() { return devices; }
  void addDevice(string type, string name);
  void addClone(int targetID, string newName); // PROTOTYPE PATTERN BURADA
  void removeDevice(int targetID);
  void listDevices();
  Device *getDevice(int id);
};

#endif