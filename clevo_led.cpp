#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class ClevoLEDController {
private:
    const std::string basePath = "/sys/devices/platform/tuxedo_keyboard/leds/rgb:kbd_backlight/";

    bool writeSysfs(const std::string& fileName, const std::string& value) {
        std::ofstream file(basePath + fileName);
        if (!file.is_open()) {
            std::cerr << "Error: Could not be written to the file. Check the rules of Udev!" << std::endl;
            return false;
        }
        file << value;
        return true;
    }

public:
    void setBrightness(int level) {
        writeSysfs("brightness", std::to_string(level));
    }

    void setColor(int r, int g, int b) {
        std::string rgbValue = std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
        writeSysfs("multi_intensity", rgbValue);
        setBrightness(255); 
    }
};

void printHelp() {
    std::cout << "Kullanim: cled [KOMUT]\n\n";
    std::cout << "Lightweight LED control tool for Monster/Clevo laptops.\n\n";
    std::cout << "Komutlar:\n";
    std::cout << "  red       Makes the keyboard color red\n";
    std::cout << "  green     Makes the keyboard color green\n";
    std::cout << "  blue      Makes the keyboard color blue\n";
    std::cout << "  white     Makes the keyboard color white\n";
    std::cout << "  purple    Makes the keyboard color purple\n";
    std::cout << "  orange    Makes the keyboard color orange\n";
    std::cout << "  cyan      Makes the keyboard color cyan\n";
    std::cout << "  magenta   Makes the keyboard color magenta\n";
    std::cout << "  gold      Makes tke keyboard color gold\n";
    std::cout << "  pink      Makes the keyboard color pink\n";
    std::cout << "  amber     Makes the keyboard color amber\n";
    std::cout << "  teal      Makes tke keyboard color teal\n";
    std::cout << "  off       Turn off keyboard lighting\n\n";
    std::cout << "Opsiyonlar:\n";
    std::cout << "  -h, --help    Bu yardim sayfasini gosterir\n\n";
    std::cout << "Not: Sadece 'cled' yazarak interaktif menuyu acabilirsiniz.\n";
}

void printMenu() {
    system("clear");
    std::cout << "====================================\n";
    std::cout << "      CLEVO keyboard LED CONTROL      \n";
    std::cout << "====================================\n";
    std::cout << "[ color ]\n";
    std::cout << "  1. red    4. white\n";
    std::cout << "  2. green      5. purple\n";
    std::cout << "  3. blue\n";
    std::cout << "\n[ Parlaklik ]\n";
    std::cout << "  6. %25        8. %75\n";
    std::cout << "  7. %50        9. %100\n";
    std::cout << "  0. (Off)\n";
    std::cout << "------------------------------------\n";
    std::cout << "  q. Quit\n";
    std::cout << "====================================\n";
    std::cout << "Select: ";
}

// Terminalden argüman girildiğinde çalışacak fonksiyon
void handleDirectCommand(ClevoLEDController& keyboard, const std::string& command) {
    if (command == "off") {
        keyboard.setBrightness(0);
    } else if (command == "red") keyboard.setColor(255, 0, 0);
    else if (command == "green") keyboard.setColor(0, 255, 0);
    else if (command == "blue") keyboard.setColor(0, 0, 255);
    else if (command == "white") keyboard.setColor(255, 255, 255);
    else if (command == "purple") keyboard.setColor(128, 0, 128);
    else if (command == "orange") keyboard.setColor(255, 128, 0);
    else if (command == "gold") keyboard.setColor(255, 215, 0);
    else if (command == "amber") keyboard.setColor(255, 191, 0);
    else if (command == "cyan") keyboard.setColor(0, 255, 255);
    else if (command == "teal") keyboard.setColor(0, 128, 128);
    else if (command == "magenta") keyboard.setColor(255, 0, 255); 
    else if (command == "pink") keyboard.setColor(255, 105, 180);
    else {
        std::cout << "unknow command. Try --help\n";
    }
}

int main(int argc, char* argv[]) {
    ClevoLEDController keyboard;

    // KONTROL 1: Argüman var mı? (Örn: cled red)
    if (argc > 1) {
        std::string command = argv[1];
        handleDirectCommand(keyboard, command);
        return 0; // İşlemi yap ve programı hemen sonlandır
    }

    // KONTROL 2: Argüman yoksa menüyü çalıştır (Sadece cled yazıldıysa)
    char choice;
    bool isRunning = true;

    while (isRunning) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case '1': keyboard.setColor(255, 0, 0); break;
            case '2': keyboard.setColor(0, 255, 0); break;
            case '3': keyboard.setColor(0, 0, 255); break;
            case '4': keyboard.setColor(255, 255, 255); break;
            case '5': keyboard.setColor(128, 0, 128); break;
            
            case '6': keyboard.setBrightness(64); break;
            case '7': keyboard.setBrightness(128); break;
            case '8': keyboard.setBrightness(192); break;
            case '9': keyboard.setBrightness(255); break;
            case '0': keyboard.setBrightness(0); break;

            case 'q':
            case 'Q':
                isRunning = false;
                system("clear");
                break;
        }
    }

    return 0;
}