#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>

using namespace std;

// Abstract Base Class
class Device {
protected:
  int deviceID;
  string name;
  bool isPowered;
  bool isBroken;

public:
  // Sadece tanımlar (Implementation .cpp dosyasında)
  Device(int id, string n);
  virtual ~Device();

  int getID() const;
  string getName() const;
  bool getPowerStatus() const;
  bool getBrokenStatus() const;
  void setBroken(bool status); // Setter

  // SetID ve SetName eklenmeli (DeviceManager kullaniyor)
  void setID(int id) { deviceID = id; }
  void setName(string n) { name = n; }

  // Pure Virtual Functions
  virtual void togglePower() = 0;
  virtual Device *clone() const = 0;
  virtual string getType() const = 0;
};

#endif