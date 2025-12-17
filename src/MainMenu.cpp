// src/MainMenu.cpp
#include "../include/MainMenu.h"

void MainMenu::clearScreen() {
    // Cross-platform basit temizleme (50 satır boşluk)
    for (int i = 0; i < 50; i++) cout << endl;
}

void MainMenu::displayHeader() {
    cout << "========================================" << endl;
    cout << "      MY SWEET HOME (MSH) SYSTEM        " << endl;
    cout << "========================================" << endl;
}

void MainMenu::displayWelcome() {
    clearScreen();
    displayHeader();
    cout << "Welcome to the Smart Home Simulation." << endl;
    cout << "System is initializing..." << endl;
    cout << "----------------------------------------" << endl;
}

void MainMenu::displayManual() {
    cout << "\n========================================" << endl;
    cout << "           USER MANUAL (MSH v3.0)" << endl;
    cout << "========================================" << endl;
    cout << "\n[1] Get Home Status" << endl;
    cout << "    - Displays all connected devices and their current power states." << endl;
    cout << "\n[2] Add Device" << endl;
    cout << "    - Add a new smart device to the system." << endl;
    cout << "    - Supported: Light, TV, Curtain, SmartFan, SmartFaucet, Stove," << endl;
    cout << "      SmokeDetector, GasDetector, Camera, SoundSensor, Alarm" << endl;
    cout << "\n[3] Remove Device" << endl;
    cout << "    - Remove an existing device by its ID." << endl;
    cout << "\n[4] Power ON Device" << endl;
    cout << "    - Turn on a specific device. Complex devices (like Stove)" << endl;
    cout << "      allow individual component control." << endl;
    cout << "\n[5] Power OFF Device" << endl;
    cout << "    - Turn off a specific device." << endl;
    cout << "\n[6] Change Mode" << endl;
    cout << "    - Switch between home automation modes:" << endl;
    cout << "      * Normal Mode: Lights ON, TV OFF" << endl;
    cout << "      * Evening Mode: Lights OFF, TV OFF" << endl;
    cout << "      * Party Mode: Lights ON, Sound ON, TV OFF" << endl;
    cout << "      * Cinema Mode: TV ON, Lights OFF" << endl;
    cout << "      * Sleep Mode: All non-security devices OFF" << endl;
    cout << "      * Good Neighbor Mode: Monitors noise levels" << endl;
    cout << "\n[7] Restore Previous State" << endl;
    cout << "    - Undo the last mode change and restore device states." << endl;
    cout << "\n[8] Manual" << endl;
    cout << "    - Display this help text." << endl;
    cout << "\n[9] About" << endl;
    cout << "    - Display developer information." << endl;
    cout << "\n[10] Shutdown" << endl;
    cout << "    - Exit the application safely." << endl;
    cout << "\n========================================" << endl;
    cout << "SECURITY NOTES:" << endl;
    cout << "- SmokeDetector, GasDetector, and Alarm cannot be turned off manually." << endl;
    cout << "- Camera will stop recording when powered off." << endl;
    cout << "- Gas leak detection will automatically shut off the Stove." << endl;
    cout << "========================================" << endl;
}

void MainMenu::displayOptions() {
    clearScreen();
    cout << "\n--- MAIN MENU ---" << endl;
    cout << "[1] Get Home Status" << endl;
    cout << "[2] Add Device" << endl;
    cout << "[3] Remove Device" << endl;
    cout << "[4] Power ON Device" << endl;
    cout << "[5] Power OFF Device" << endl;
    cout << "[6] Change Mode (Normal/Evening/Party/Cinema/Sleep/GoodNeighbor)" << endl;
    cout << "[7] Restore Previous State (Undo)" << endl;
    cout << "[8] User Manual" << endl;
    cout << "[9] About" << endl;
    cout << "[10] Shutdown" << endl;
    cout << "[11] Wait / Pass Time (Trigger Automations)" << endl;
    cout << "[12] Device Actions (Special Controls)" << endl;
    cout << "----------------------------------------" << endl;
}