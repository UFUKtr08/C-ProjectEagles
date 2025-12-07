#include <iostream>
#include "../include/Logger.h"
using namespace std;
int main() {
    Logger::getInstance()->log("Sistem Modul 1 Test...");
    cout << "My Sweet Home Calisiyor!" << endl;
    int a; cin >> a; // Ekran hemen kapanmasýn diye
    return 0;
}
