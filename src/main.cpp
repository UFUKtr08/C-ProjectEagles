// src/main.cpp (Modül 6 Test)
#include <iostream>
#include "../include/InputHandler.h"
#include "../include/MainMenu.h"
#include "../include/Logger.h" // Modül 1

using namespace std;

int main() {
    // Modül 1 Testi: Logger Başlatma
    Logger::getInstance()->log("Module 6 UI Test Started...");

    InputHandler input;
    MainMenu menu;

    menu.displayWelcome();
    input.waitPressEnter();

    int choice = 0;
    while (choice != 10) {
        menu.clearScreen();
        menu.displayHeader();
        menu.displayOptions();
        
        // InputHandler testi: Hatalı giriş yapmayı dene (harf vs.)
        // Programın çökmediğini göreceksin.
        choice = input.getIntInput(1, 10, "Select Operation: ");
        
        cout << "\n>> You selected option: " << choice << endl;
        
        // Örnek: Cihaz ekleme simülasyonu
        if (choice == 2) {
            string name = input.getStringInput("Enter new device name: ");
            cout << ">> Device name received: " << name << endl;
            // Buraya ilerde DeviceManager->addDevice(...) gelecek.
        }
        
        if (choice != 10) {
            input.waitPressEnter();
        }
    }

    Logger::getInstance()->log("Module 6 UI Test Finished.");
    return 0;
}