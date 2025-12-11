// src/main.cpp (TEST İÇİN)
#include "../include/DeviceManager.h"

int main() {
    DeviceManager mgr;

    // 1. Factory Testi: Yeni cihazlar ekle
    mgr.addDevice("Light", "Living Room Light");
    mgr.addDevice("TV", "Samsung Smart TV");
    mgr.addDevice("Curtain", "Bedroom Curtain");

    // 2. Operasyon Testi: Cihazları aç/kapa
    Device* d1 = mgr.getDevice(1);
    if(d1) d1->togglePower(); // Işığı aç

    // 3. Prototype Testi: Odaya bir ışık daha ekle (Klonlama)
    // ID 1'deki cihazın aynısından üretmeli
    mgr.addClone(1, "Living Room Light 2");

    mgr.listDevices();

    // 4. Silme Testi
    mgr.removeDevice(2); // TV'yi sil

    mgr.listDevices();

    return 0;
}