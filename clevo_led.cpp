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
            std::cerr << "Hata: Dosyaya yazilamadi. Udev kurallarini kontrol et!" << std::endl;
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
        // Renk degistiginde parlakligi otomatik maksimuma al (opsiyonel)
        setBrightness(255); 
    }
};

void printMenu() {
    system("clear");
    std::cout << "====================================\n";
    std::cout << "      CLEVO KLAVYE LED KONTROL      \n";
    std::cout << "====================================\n";
    std::cout << "[ Renkler ]\n";
    std::cout << "  1. red    4. white\n";
    std::cout << "  2. green      5. purple\n";
    std::cout << "  3. blue\n";
    std::cout << "\n[ Parlaklik ]\n";
    std::cout << "  6. %25        8. %75\n";
    std::cout << "  7. %50        9. %100\n";
    std::cout << "  0. (Off)\n";
    std::cout << "------------------------------------\n";
    std::cout << "  q. Cikis\n";
    std::cout << "====================================\n";
    std::cout << "Seciminiz: ";
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
    else {
        std::cout << "Bilinmeyen komut. Kullanim: cled [red|green|blue|white|purple|off]\n";
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
