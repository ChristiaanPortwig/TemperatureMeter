#include <DHT.h>

#include "StateManager.h"
#include "DisplayManager.h"

#define BUTTON_PIN 15
#define DHT22_PIN 14
#define SDA_PIN 4
#define SCL_PIN 5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define TEMP_READ_TIME 2500
#define BTN_PRESS_INTERVAL 200

int buttonVal = 0;

enum State currState = BOTH;
int buttonPressed = 0;

DHT dht22(DHT22_PIN, DHT22);
DisplayManager dispMngr(SDA_PIN, SCL_PIN);
StateManager btnManager;

unsigned long prevBtnPressTime = 0;
unsigned long prevSensorReadTime = 0;

float tempVal;
float humVal;

void printSensorVals(float tempVal, float humVal)
{
    Serial.println(tempVal);
    Serial.println(humVal);

    return;
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    dht22.begin();
    dispMngr.begin();
}

void loop()
{
    buttonPressed = !digitalRead(BUTTON_PIN);
    if (buttonPressed && millis() - prevBtnPressTime >= BTN_PRESS_INTERVAL)
    {
        btnManager.setNextState();
        prevBtnPressTime = millis();
    }
    

    if (millis() - prevSensorReadTime >= TEMP_READ_TIME)
    {
        prevSensorReadTime = millis();
        tempVal = dht22.readTemperature();
        humVal = dht22.readHumidity();
    }

    switch (btnManager.currState) {
        case BOTH:
            dispMngr.writeBoth(tempVal, humVal);
        break;
        case TEMP:
            dispMngr.writeTemp(tempVal);
        break;
        case HUM:
            dispMngr.writeHum(humVal);
        break;
    }
}

//dispMngr.freeAll();