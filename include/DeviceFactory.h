#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "StandardDevices.h"
#include "ComplexDevices.h"
#include "Camera.h"
#include "SmokeDetector.h"
#include "SoundSensor.h"
#include "Alarm.h"
#include <vector>
#include <string>

class DeviceFactory {
public:
    // Cihaz oluşturma metodu (Aynı kalıyor)
    static Device* createDevice(const string& type) {
        if (type == "Light") return new Light();
        else if (type == "TV") return new TV();
        else if (type == "Curtain") return new Curtain();
        else if (type == "Stove") return new Stove(0, "Kitchen Stove");
        else if (type == "SmartFaucet") return new SmartFaucet(0, "Kitchen Faucet");
        else if (type == "SmartFan") return new SmartFan(0, "Vent Fan");
        else if (type == "Camera") return new Camera(0, "Security Camera");
        else if (type == "SmokeDetector") return new SmokeDetector(0, "Smoke Sensor");
        else if (type == "SoundSensor") return new SoundSensor(0, "Noise Sensor");
        else if (type == "Alarm") return new Alarm(0, "Extra Alarm");
        
        return NULL;
    }

    // YENİ EKLENEN METOT: Mevcut cihaz türlerini listeler
    static vector<string> getAvailableTypes() {
        vector<string> types;
        // C++98'de initializer list olmadığı için push_back kullanıyoruz
        types.push_back("Light");
        types.push_back("TV");
        types.push_back("Curtain");
        types.push_back("Stove");
        types.push_back("SmartFaucet");
        types.push_back("SmartFan");
        types.push_back("Camera");
        types.push_back("SmokeDetector");
        types.push_back("SoundSensor");
        // Alarm genellikle manuel eklenir ama opsiyonel buraya da koyabiliriz
        return types;
    }
};

#endif