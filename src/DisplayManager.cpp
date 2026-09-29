#include "DisplayManager.h"
#include <Wire.h>

#define SCREEN_ADDRESS 0x3C

DisplayManager::DisplayManager(uint8_t sdaPin, uint8_t sclPin) {
    DisplayManager::display = Adafruit_SSD1306(width, height, &Wire, -1);
    DisplayManager::sdaPin = sdaPin;
    DisplayManager::sclPin = sclPin;
}

void DisplayManager::begin() {
    Wire.begin(sdaPin, sclPin);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.display();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1.5);
    
    display.setCursor(0, 0);
}

void DisplayManager::writeTemp(float temp) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temp: ");
    display.println(temp);
    display.display();
}

void DisplayManager::writeHum(float hum) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Hum: ");
    display.println(hum);
    display.display();
}

void DisplayManager::writeBoth(float temp, float hum) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temp: ");
    display.println(temp);
    display.print("Hum: ");
    display.println(hum);
    display.display();
}