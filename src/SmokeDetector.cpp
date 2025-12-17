#include "../include/SmokeDetector.h"
#include "../include/SecuritySystem.h" // BAĞLANTIYI KURAN KİLİT SATIR!

using namespace std;

void SmokeDetector::detectSmoke(SecuritySystem *sys) {
  cout << "\n>> SMOKE DETECTED by " << name << "!" << endl;
  cout << ">> Initiating Emergency Protocols..." << endl;

  // EĞER SİSTEM BAĞLIYSA HABER VER (INTEGRATION)
  if (sys) {
    sys->notifyBreach(name, "FIRE_DETECTED");
  } else {
    cout
        << "[WARNING] Security System not connected! Local alarm sounding only."
        << endl;
  }
}

void SmokeDetector::performAction(string actionName) {
  if (actionName == "Check Status") {
    cout << "Smoke Detector is Active and Monitoring." << endl;
  } else if (actionName == "SIMULATE SMOKE") {
    // Test sırasında sistemi 'nullptr' geçiyoruz çünkü arayüzden sys'ye
    // erişimimiz yok. Ama gerçek main loop içinde bu sys dolu gelecek.
    // Simülasyonun çalıştığını görmek için şimdilik nullptr ile çağırıyoruz.
    detectSmoke(nullptr);
  }
}