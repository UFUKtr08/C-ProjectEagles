#include <iostream>
#include <vector>
#include <string>

// --- Headerlar ---
// (Dosya yollari proje yapina gore degisebilir, duzgun include ettiginden emin ol)
#include "include/Logger.h"
#include "include/SecuritySystem.h"
#include "include/Device.h"
#include "include/StandardDevices.h" // Light, TV, Curtain
#include "include/SmokeDetector.h"
#include "include/SoundSensor.h"
#include "include/ComplexDevices.h" // Stove, SmartFan vb.
#include "include/Modes.h"          // NormalMode, PartyMode, CinemaMode

using namespace std;

// --- Mock Alarm (Alarm.h tam olmadigi icin basit bir implementasyon) ---
class Siren : public Alarm {
public:
    void trigger() {
        cout << "\n!!! WEE-WOO WEE-WOO !!! (Siren Caliyor)" << endl;
        Logger::getInstance()->log("Siren triggered!", "ALARM");
    }
};

// --- YARDIMCI TEST FONKSIYONU ---
void printSeparator(string title) {
    cout << "\n----------------------------------------" << endl;
    cout << " TEST: " << title << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    // 1. Logger Baslat
    Logger::getInstance()->log("--- FULL SYSTEM TEST STARTED ---", "SYSTEM");

    // 2. Guvenlik Sistemi Kurulumu
    SecuritySystem* secSystem = new SecuritySystem();
    Siren* mySiren = new Siren();
    secSystem->setAlarm(mySiren);

    // 3. Cihazlari Olustur (Factory pattern bypass edilerek manuel olusturuldu)
    vector<Device*> evCihazlari;

    // Standart Cihazlar
    evCihazlari.push_back(new Light(101, "Salon Isigi"));
    evCihazlari.push_back(new TV(102, "Salon TV"));
    evCihazlari.push_back(new Curtain(103, "Yatak Odasi Perdesi"));

    // Sensorler
    SmokeDetector* dumanSensoru = new SmokeDetector(201, "Mutfak Duman Sensoru");
    SoundSensor* sesSensoru = new SoundSensor(202, "Koridor Ses Sensoru");
    
    // Karmaşık Cihazlar
    Stove* akilliOcak = new Stove(301, "Ankastre Ocak");
    SmartFan* akilliFan = new SmartFan(302, "Banyo Fani");

    // Listeye ekle (Yonetim kolayligi icin)
    evCihazlari.push_back(dumanSensoru);
    evCihazlari.push_back(sesSensoru);
    evCihazlari.push_back(akilliOcak);
    evCihazlari.push_back(akilliFan);

    // ---------------------------------------------------------
    
    printSeparator("TEMEL CIHAZ KONTROLU");
    // Işıkları aç, Perdeyi kapat
    evCihazlari[0]->togglePower(); // Light ON
    evCihazlari[2]->togglePower(); // Curtain OPEN/CLOSE

    printSeparator("KARMASIK CIHAZ (OCAK) TESTI");
    // Ocağı aç ve gözleri yak
    akilliOcak->togglePower(); // Ana şalter ON
    akilliOcak->controlBurner(0, true); // 1. göz ON
    akilliOcak->controlBurner(2, true); // 3. göz ON
    
    printSeparator("MODE PATTERN TESTI (Party Mode)");
    // Parti Modunu Uygula (Isiklar ve Ses sistemleri acilmali)
    IMode* currentMode = new PartyMode();
    cout << ">> Mod Degistiriliyor: " << currentMode->getName() << endl;
    currentMode->execute(evCihazlari);
    delete currentMode;

    printSeparator("MODE PATTERN TESTI (Cinema Mode)");
    // Sinema Modunu Uygula (Sadece TV acik, digerleri kapali olmali)
    currentMode = new CinemaMode();
    cout << ">> Mod Degistiriliyor: " << currentMode->getName() << endl;
    currentMode->execute(evCihazlari);
    delete currentMode;

    printSeparator("GUVENLIK VE SENSOR TESTI");
    // 1. Ses Testi
    sesSensoru->measureLevel(40, secSystem); // Normal
    sesSensoru->measureLevel(90, secSystem); // Yüksek (Uyarı vermeli)

    // 2. Yangın Testi (Kritik!)
    cout << ">> Simulasyon: Mutfakta duman algilandi..." << endl;
    dumanSensoru->detectSmoke(secSystem); 
    // Beklenen: Alarm calmasi, Logger'a yazmasi.

    // 3. Ocak Guvenlik Testi (Gaz Kacagi)
    cout << "\n>> Simulasyon: Ocakta gaz kacagi var!" << endl;
    akilliOcak->onGasDetected(); 
    // Beklenen: Ocagin kendini kapatmasi.

    printSeparator("PROTOTYPE (CLONE) TESTI");
    // Var olan bir ışıktan yeni bir tane kopyalayalım
    Device* yeniIsik = evCihazlari[0]->clone();
    // Isim private oldugu icin dogrudan degisemeyiz belki ama ID farkli olmali
    cout << "Orijinal ID: " << evCihazlari[0]->getID() << endl;
    cout << "Kopya ID: " << yeniIsik->getID() << " (Not: Clone icinde ID yonetimi manual degilse ayni gelebilir)" << endl;
    delete yeniIsik;

    // --- TEMIZLIK ---
    printSeparator("SISTEM KAPATILIYOR");
    for (size_t i = 0; i < evCihazlari.size(); ++i) {
        delete evCihazlari[i];
    }
    delete secSystem;
    delete mySiren;
    // Logger singleton oldugu icin program bitisinde destructor cagrilir veya manuel silebilirsin.
    
    return 0;
}