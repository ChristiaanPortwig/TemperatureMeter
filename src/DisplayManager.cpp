#include "DisplayManager.h"
#include "Bitmaps.h"
#include <Wire.h>

#define SCREEN_ADDRESS 0x3C

#define ANIM_TOP_LEFT_X 43
#define ANIM_TOP_LEFT_Y 0
#define ANIM_WIDTH 85
#define ANIM_HEIGHT 32

#define SNOWFLAKE_DIM 3

DisplayManager::DisplayManager(uint8_t sdaPin, uint8_t sclPin) {
    DisplayManager::display = Adafruit_SSD1306(width, height, &Wire, -1);
    DisplayManager::sdaPin = sdaPin;
    DisplayManager::sclPin = sclPin;
}

void DisplayManager::freeAll() {
    if (snowflakes) {
        free(snowflakes);
    }
}

void DisplayManager::begin() {
    //Set random seed
    srand(time(0));

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
    display.setCursor(0, 0);
    display.println("Temp: ");
    display.println(temp);
    display.println("Hum: ");
    display.println(hum);

    if (temp < 16) {
        drawSnowmanAnim(150);
        drawSnowflakeAnim(15, 150);
    } else {
        drawWaveAnim(150);
    }

    display.display();
}

void DisplayManager::drawWaveAnim(int waitTime = 150) {

    if (millis() - lastAnimUpdate > waitTime) {
        lastWaveFrame ++;
        lastWaveFrame = lastWaveFrame % epd_bitmap_allWavesArray_LEN;
        lastAnimUpdate = millis();
    }

    //Assuming clear and display is called externally
    display.drawBitmap(
    ANIM_TOP_LEFT_X,
    ANIM_TOP_LEFT_Y,
    epd_bitmap_allWavesArray[lastWaveFrame], ANIM_WIDTH, ANIM_HEIGHT, 1);
}

void DisplayManager::drawSnowmanAnim(int waitTime = 150) {

    if (millis() - lastAnimUpdate > waitTime) {
        lastSnowmanFrame ++;
        lastSnowmanFrame = lastSnowmanFrame % epd_bitmap_allSnowmanArray_LEN;
        lastAnimUpdate = millis();
    }

    //Assuming clear and display is called externally
    display.drawBitmap(
    ANIM_TOP_LEFT_X,
    ANIM_TOP_LEFT_Y,
    epd_bitmap_allSnowmanArray[lastSnowmanFrame], ANIM_WIDTH, ANIM_HEIGHT, 1);
}

void DisplayManager::drawSnowflakeAnim(int snowflakeAmount, int waitTime = 150) {

    // Only initialize snowflake positions and allocatie mem if it hasn't been created
    if (!snowflakes) {
        snowflakes = (Snowflake*) calloc(snowflakeAmount, sizeof(Snowflake));

        for (int i = 0; i < snowflakeAmount; i++) {
            int tempX = rand() % (ANIM_WIDTH) + (width - ANIM_WIDTH);
            int tempDelta = rand() % 3 + 1; //random from 1 - 3

            snowflakes[i].x = tempX;
            snowflakes[i].y = 0;
            snowflakes[i].deltaY = tempDelta; 
        }
        
        lastSnowflakeUpdate = millis();

    } else if (millis() - lastSnowflakeUpdate > waitTime) { //Only update is waitTime reached

        //Update everything
        for (int i = 0; i < snowflakeAmount; i++) {
            snowflakes[i].y += snowflakes[i].deltaY;
            
            // Also update x to make movement more natural...
            int sign = rand() % 2;
            int tempX = rand() % 5;

            snowflakes[i].x += (2 * sign - 1) * (tempX);
            
            //Reset to top if off screen
            if (snowflakes[i].y > height) {
                int tempX = rand() % (ANIM_WIDTH) + (width - ANIM_WIDTH);
                int tempDelta = rand() % 6 + 1; //random from 1 - 6

                snowflakes[i].x = tempX;
                snowflakes[i].y = 0;
                snowflakes[i].deltaY = tempDelta; 
            }
        }
        
        lastSnowflakeUpdate = millis();
    }
        
    //Now actually draw the snowflakes (Assuming clear happened externally)
    for (int i = 0; i < snowflakeAmount; i++) {
        display.drawBitmap(
            snowflakes[i].x - floor(SNOWFLAKE_DIM / 2),
            snowflakes[i].y - floor(SNOWFLAKE_DIM / 2),
            snowflakeBitmap,
            SNOWFLAKE_DIM,
            SNOWFLAKE_DIM,
            0
        );
    }
}