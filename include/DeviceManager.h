#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "DeviceFactory.h"
#include <vector>

class DeviceManager {
private:
  std::vector<Device *> devices;
  int nextID; 

public:
  DeviceManager();
  ~DeviceManager(); 
  std::vector<Device *> &getDevicesRef() { return devices; }
  
  void addDevice(string type, string name);
  void addClone(int targetID, string newName);
  void removeDevice(int targetID);
  void listDevices();
  Device *getDevice(int id);

  // --- YENİ EKLENEN FONKSİYONLAR ---
  // Işık açılıp kapanınca fanları kontrol eder
  void notifyLightSwitch(bool isLightOn, string lightName);

  // Zamanın geçmesini simüle eder (Musluk ve Fan sürelerini işler)
  void updateSystemLoops();
};

#endif