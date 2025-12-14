#include "../include/Device.h"
#include "../include/Logger.h" // Logger kullanildigi icin eklenmeli
#include "../include/Utils.h"

Device::Device(int id, string n)
    : deviceID(id), name(n), isPowered(false), isBroken(false) {}

Device::~Device() {}

int Device::getID() const { return deviceID; }

string Device::getName() const { return name; }

bool Device::getPowerStatus() const { return isPowered; }

bool Device::getBrokenStatus() const { return isBroken; }

void Device::setBroken(bool status) {
  isBroken = status;
  if (isBroken) {
    // Utils.h icindeki intToString fonksiyonunu kullaniyoruz
    string msg =
        "FAILURE: Device " + name + " (ID: " + intToString(deviceID) + ")";
    Logger::getInstance()->log(msg, "ERROR");
  }
}