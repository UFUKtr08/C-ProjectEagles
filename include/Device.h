#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>
#include <vector> // Bu kütüphane şart

using namespace std;

// Abstract Base Class
class Device {
protected:
  int deviceID;
  string name;
  bool isPowered;
  bool isBroken;

public:
  Device(int id, string n);
  virtual ~Device();
  
  virtual void operate() {
    cout << ">> No manual configuration available for " << getName() << "." << endl;
  }

  int getID() const;
  string getName() const;
  bool getPowerStatus() const;
  bool getBrokenStatus() const;
  void setBroken(bool status);
  void setID(int id) { deviceID = id; }
  void setName(string n) { name = n; }

  // Pure Virtual Functions
  virtual void togglePower() = 0;
  virtual Device *clone() const = 0;
  virtual string getType() const = 0;

  // --- OTO-MENÜ SİSTEMİ ---
  // (Sadece tek bir tanım olmalı!)

  virtual vector<string> getActions() {
      return vector<string>(); // Varsayılan boş liste
  }

  virtual void performAction(string actionName) {
      cout << ">> " << getName() << ": Action not defined." << endl;
  }
};

#endif