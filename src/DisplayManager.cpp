#include "DisplayManager.h"
#include "Bitmaps.h"
#include <Wire.h>

#define SCREEN_ADDRESS 0x3C

#define ANIM_TOP_LEFT_X 43
#define ANIM_TOP_LEFT_Y 0
#define ANIM_WIDTH 85
#define ANIM_HEIGHT 32

DisplayManager::DisplayManager(uint8_t sdaPin, uint8_t sclPin) {
    DisplayManager::display = Adafruit_SSD1306(width, height, &Wire, -1);
    DisplayManager::sdaPin = sdaPin;
    DisplayManager::sclPin = sclPin;
}

void DisplayManager::begin() {
    Wire.begin(sdaPin, sclPin);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    //Draws line for height of bought screen
    display.drawLine(0, 32, 128, 32, 1);
    display.display();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1.5);
    
    display.setCursor(0, 0);

}

void DisplayManager::writeTemp(float temp) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Temp: ");
    display.println(temp);
    //Draws line for height of bought screen
    display.drawLine(0, 32, 128, 32, 1);
    display.display();
}

void DisplayManager::writeHum(float hum) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Hum: ");
    display.println(hum);
    //Draws line for height of bought screen
    display.drawLine(0, 32, 128, 32, 1);
    display.display();
}

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
void DisplayManager::writeBoth(float temp, float hum) {
    display.clearDisplay();
    // display.setCursor(0, 0);
    // display.print("Temp: ");
    // display.println(temp);
    // display.print("Hum: ");
    // display.println(hum);
    drawWaveAnim(0, 150);
    display.display();
}

void DisplayManager::drawWaveAnim(unsigned long millis, int waitTime = 150) {

    for (int i = 0; i < epd_bitmap_allWavesArray_LEN; i++)
    {
        display.clearDisplay();
        display.drawBitmap(
        ANIM_TOP_LEFT_X,
        ANIM_TOP_LEFT_Y,
        epd_bitmap_allWavesArray[i], ANIM_WIDTH, ANIM_HEIGHT, 1);
        display.display();
        delay(waitTime);
    }
    
}