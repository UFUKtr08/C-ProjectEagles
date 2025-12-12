#include "../include/SoundSensor.h"
#include "../include/SecuritySystem.h"
#include <iostream>

void SoundSensor::measureLevel(int db, SecuritySystem* sys) {
    cout << " [INFO] " << getName() << " measured: " << db << "dB" << endl;
    // Ölçümü sisteme bildir, kararı sistem verir
    if (sys) sys->checkNoiseLevel(db);
}