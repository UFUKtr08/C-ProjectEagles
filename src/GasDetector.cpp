#include "../include/GasDetector.h"
#include "../include/SecuritySystem.h"
#include <iostream>

using namespace std;

void GasDetector::detectGas(SecuritySystem *sys) {
  cout << "\n>> GAS LEAK DETECTED by " << name << "!" << endl;
  cout << ">> Initiating Emergency Gas Protocol..." << endl;

  if (sys) {
    sys->notifyBreach(name, "GAS_DETECTED");
  } else {
    cout << "[WARNING] Security System not connected! Local alarm sounding only."
         << endl;
  }
}

void GasDetector::performAction(string actionName) {
  if (actionName == "Check Status") {
    cout << "Gas Detector is Active and Monitoring." << endl;
  } else if (actionName == "SIMULATE GAS LEAK") {
    detectGas(nullptr);
  }
}
