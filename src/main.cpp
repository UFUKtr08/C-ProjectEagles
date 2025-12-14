#include <iostream>
#include <vector>
#include <string>

// Header Dosyalari (Dizin yapina gore "../include/" kullaniyoruz)
#include "../include/Logger.h"
#include "../include/SecuritySystem.h"
#include "../include/Alarm.h"
#include "../include/StandardDevices.h" // Light, TV, Curtain
#include "../include/SmokeDetector.h"
#include "../include/SoundSensor.h"
#include "../include/ComplexDevices.h" // Stove, SmartFan vb.
#include "../include/Modes.h"          // NormalMode, PartyMode, CinemaMode

using namespace std;

// Konsol ciktisini duzenlemek icin yardimci fonksiyon
void printHeader(string title) {
    cout << "\n========================================" << endl;
    cout << " TEST: " << title << endl;
    cout << "========================================" << endl;
}

int main() {
    // 1. LOGGER BASLATMA
    Logger::getInstance()->log("--- MASTER TEST STARTED ---", "SYSTEM");

    // 2. GUVENLIK SISTEMI VE ALARM KURULUMU
    SecuritySystem* secSystem = new SecuritySystem();
    
    // Artik main icinde "class Siren" tanimlamiyoruz. Gercek Alarm sinifini kullaniyoruz.
    Alarm* masterAlarm = new Alarm(999, "Ana Ev Sireni");
    
    // Alarmi "ARMED" (Acik) konuma getiriyoruz ki tetiklenince calsin
    if (!masterAlarm->getPowerStatus()) {
        masterAlarm->togglePower(); 
    }
    
    // Alarmi sisteme bagla
    secSystem->setAlarm(masterAlarm);


    // 3. CIHAZLARI OLUSTURMA (Manuel Envanter)
    vector<Device*> devices;

    // -- Standart Cihazlar --
    Light* salonIsik = new Light(101, "Salon Isigi");
    TV* salonTV = new TV(102, "Salon TV");
    Curtain* yatakPerde = new Curtain(103, "Yatak Odasi Perdesi");

    // -- Sensorler --
    SmokeDetector* dumanSensoru = new SmokeDetector(201, "Mutfak Duman Detektoru");
    SoundSensor* sesSensoru = new SoundSensor(202, "Koridor Ses Sensoru");

    // -- Karmasik Cihazlar --
    Stove* akilliOcak = new Stove(301, "Ankastre Ocak");
    SmartFan* banyoFani = new SmartFan(302, "Banyo Havalandirma");

    // Yonetim icin listeye ekle
    devices.push_back(salonIsik);
    devices.push_back(salonTV);
    devices.push_back(yatakPerde);
    devices.push_back(dumanSensoru);
    devices.push_back(sesSensoru);
    devices.push_back(akilliOcak);
    devices.push_back(banyoFani);


    // ================= TEST SENARYOLARI =================

    // SENARYO 1: TEMEL KONTROL
    printHeader("TEMEL CIHAZ KONTROLU");
    salonIsik->togglePower();    // Isik ACILDI
    yatakPerde->togglePower();   // Perde ACILDI
    salonTV->togglePower();      // TV ACILDI (Sonra kapatalim)
    salonTV->togglePower();      // TV KAPANDI


    // SENARYO 2: KARMASIK CIHAZ (OCAK)
    printHeader("KARMASIK CIHAZ (OCAK) TESTI");
    akilliOcak->togglePower();          // Ana gaz vanasini ac
    akilliOcak->controlBurner(0, true); // 1. gozu yak
    akilliOcak->controlBurner(2, true); // 3. gozu yak
    // Ocak acikken guvenlik testi (Gaz Kacagi)
    cout << ">> SIMULASYON: Gaz kacagi algilandi..." << endl;
    akilliOcak->onGasDetected();        // Otomatik kapanmali
    

    // SENARYO 3: MOD DEGISIMLERI (Design Pattern: State/Strategy)
    printHeader("MOD TESTI: PARTY MODE");
    IMode* partyMode = new PartyMode();
    partyMode->execute(devices); // Isiklar, Ses ve varsa ilgili cihazlar acilmali
    delete partyMode;

    printHeader("MOD TESTI: CINEMA MODE");
    IMode* cinemaMode = new CinemaMode();
    cinemaMode->execute(devices); // Sadece TV acik, isiklar kapanmali
    delete cinemaMode;


    // SENARYO 4: GUVENLIK VE SENSORLER (Design Pattern: Observer/Mediator)
    printHeader("GUVENLIK SISTEMI TESTI");
    
    // a) Yuksek Ses Testi
    cout << ">> Ses olculuyor (40dB)..." << endl;
    sesSensoru->measureLevel(40, secSystem); // Normal
    cout << ">> Ses olculuyor (100dB)..." << endl;
    sesSensoru->measureLevel(100, secSystem); // UYARI vermeli (Log kontrol et)

    // b) Yangin Testi
    cout << "\n>> SIMULASYON: Yangin basladi!" << endl;
    dumanSensoru->detectSmoke(secSystem); 
    // BEKLENEN: Alarm calacak, sistem polise haber verecek (konsol ciktisi)


    // SENARYO 5: PROTOTYPE (CLONE)
    printHeader("PROTOTYPE (CLONE) TESTI");
    Device* kopyaIsik = salonIsik->clone(); // Var olan isigin kopyasi
    cout << "Orijinal Isik ID: " << salonIsik->getID() << " | Isim: " << salonIsik->getName() << endl;
    cout << "Kopya Isik ID:    " << kopyaIsik->getID() << " | Isim: " << kopyaIsik->getName() << endl;
    delete kopyaIsik; // Kopyayi temizle


    // ================= TEMIZLIK =================
    printHeader("SISTEM KAPATILIYOR");
    
    // Cihazlari temizle
    for (size_t i = 0; i < devices.size(); ++i) {
        delete devices[i];
    }
    devices.clear();

    // Sistem bilesenlerini temizle
    delete masterAlarm; // Once alarmi sil
    delete secSystem;   // Sonra sistemi sil
    // Logger Singleton oldugu icin program bitisinde kendi static pointer'i kalir 
    // veya Logger::~Logger() cagrilir.

    cout << "Main program sonlandi." << endl;
    return 0;
}