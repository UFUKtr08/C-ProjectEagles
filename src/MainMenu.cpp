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

void MainMenu::displayOptions() {
    cout << "\n--- MAIN MENU ---" << endl;
    cout << "[1] Get Home Status" << endl;
    cout << "[2] Add Device" << endl;
    cout << "[3] Remove Device" << endl;
    cout << "[4] Power ON Device" << endl;
    cout << "[5] Power OFF Device" << endl;
    cout << "[6] Change Mode (Normal/Party/Cinema...)" << endl;
    cout << "[7] Change State (Undo/Previous)" << endl;
    cout << "[8] Manual" << endl;
    cout << "[9] About" << endl;
    cout << "[10] Shutdown" << endl;
    cout << "----------------------------------------" << endl;
}