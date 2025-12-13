#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "StandardDevices.h"

class DeviceFactory {
public:
    // Statik metod: Nesne oluşturmadan çağrılabilir
    static Device* createDevice(const string& type) {
        if (type == "Light") return new Light();
        else if (type == "TV") return new TV();
        else if (type == "Curtain") return new Curtain();
        // İleride buraya Stove, Camera eklenecek
        return NULL;
    }
};

#endif