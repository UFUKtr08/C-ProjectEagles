#ifndef DEVICEMEMENTO_H
#define DEVICEMEMENTO_H

// Cihazın o anki durumunu saklar
class DeviceMemento {
private:
    int deviceID;
    bool isPowered;

public:
    DeviceMemento(int id, bool power) : deviceID(id), isPowered(power) {}

    int getID() const { return deviceID; }
    bool getPowerStatus() const { return isPowered; }
};

#endif