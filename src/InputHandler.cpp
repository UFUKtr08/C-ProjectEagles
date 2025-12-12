// src/InputHandler.cpp
#include "../include/InputHandler.h"
#include <limits> // numeric_limits için
#include <sstream> // stringstream için

// intToString fonksiyonunu Utils.h'den de kullanabilirdik ama
// burada bağımlılığı azaltmak için basitçe inline hallettik.
// Modül 1'deki Utils.h varsa onu da include edebilirsin.

int InputHandler::getIntInput(int min, int max, string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // Giriş başarılı mı ve aralıkta mı?
            if (value >= min && value <= max) {
                // Buffer temizliği (Enter karakterini silmek için)
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                // --- LOGLAMA (Modül 1 Entegrasyonu) ---
                // Logger::log string beklediği için dönüşüm yapıyoruz
                stringstream ss;
                ss << "User Input (Int): " << value;
                Logger::getInstance()->log(ss.str());
                
                return value;
            } else {
                cout << ">> Error: Please enter a number between " << min << " and " << max << ".\n";
            }
        } else {
            // Sayı yerine harf girildiyse
            cout << ">> Error: Invalid input type. Please enter a number.\n";
            cin.clear(); // Hata bayrağını temizle
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Buffer'ı boşalt
        }
    }
}

string InputHandler::getStringInput(string prompt) {
    string value;
    cout << prompt;
    getline(cin, value);

    // --- LOGLAMA ---
    Logger::getInstance()->log("User Input (String): " + value);

    return value;
}

char InputHandler::getCharInput(string prompt) {
    char value;
    cout << prompt;
    cin >> value;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Temizlik

    // --- LOGLAMA ---
    string msg = "User Input (Char): ";
    msg += value;
    Logger::getInstance()->log(msg);

    return value;
}

void InputHandler::waitPressEnter() {
    cout << "\n(Press ENTER to continue...)";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}