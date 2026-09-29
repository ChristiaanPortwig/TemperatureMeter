#include "DisplayManager.h"
#include <Wire.h>

#define SCREEN_ADDRESS 0x3C

DisplayManager::DisplayManager(uint8_t sdaPin, uint8_t sclPin) {
    DisplayManager::display = Adafruit_SSD1306(128, 32, &Wire, -1);
    DisplayManager::sdaPin = sdaPin;
    DisplayManager::sclPin = sclPin;
}

void DisplayManager::begin() {
    Wire.begin(sdaPin, sclPin);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    
    display.setCursor(0, 0);
    display.println("HELLO WORLD");
    display.display();
}