#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include <vector>
#include "Modes.h"
#include "DeviceMemento.h"
#include "Logger.h"

using namespace std;

class ModeManager {
private:
    IMode* currentMode;
    // Hafıza Listesi
    vector<vector<DeviceMemento> > history;

    // Kaydetme Fonksiyonu
    void saveState(const vector<Device*>& devices) {
        vector<DeviceMemento> snapshot;
        for (size_t i = 0; i < devices.size(); ++i) {
            snapshot.push_back(DeviceMemento(devices[i]->getID(), devices[i]->getPowerStatus()));
        }
        history.push_back(snapshot);
        Logger::getInstance()->log("System state saved to history.");
    }

public:
    ModeManager() {
        currentMode = new NormalMode(); 
    }

    ~ModeManager() {
        if (currentMode) delete currentMode;
    }

    void setMode(IMode* newMode, vector<Device*>& devices) {
        if (newMode == NULL) return;

        saveState(devices); // Önce kaydet

        if (currentMode) delete currentMode;
        currentMode = newMode;

        Logger::getInstance()->log("Switching to " + currentMode->getName() + " Mode...");
        currentMode->execute(devices);
    }

    void restorePreviousState(vector<Device*>& devices) {
        if (history.empty()) {
            Logger::getInstance()->log("WARNING: No previous state to restore!");
            return;
        }

        vector<DeviceMemento> lastSnapshot = history.back();
        history.pop_back();

        Logger::getInstance()->log("Restoring previous system state...");

        for (size_t i = 0; i < lastSnapshot.size(); ++i) {
            int targetID = lastSnapshot[i].getID();
            bool targetPower = lastSnapshot[i].getPowerStatus();

            for (size_t j = 0; j < devices.size(); ++j) {
                if (devices[j]->getID() == targetID) {
                    if (devices[j]->getPowerStatus() != targetPower) {
                        devices[j]->togglePower();
                    }
                    break; 
                }
            }
        }
        Logger::getInstance()->log("System restored to previous state.");
    }

    string getCurrentModeName() const {
        return currentMode->getName();
    }
};

#endif