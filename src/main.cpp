#include <DHT.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include "StateManager.h"

#define BUTTON_PIN 15
#define DHT22_PIN 14
#define TEMP_READ_TIME 2500
#define BTN_PRESS_INTERVAL 100

int buttonVal = 0;

enum State currState = BOTH;
int buttonPressed = 0;

DHT dht22(DHT22_PIN, DHT22);
StateManager btnManager;

unsigned long prevBtnPressTime = 0;
unsigned long prevSensorReadTime = 0;

float tempVal;
float humVal;

void printSensorVals(float tempVal, float humVal) {
    Serial.println("called");
    
    Serial.print("Temp: ");
    Serial.println(tempVal);
    Serial.print("Hum: ");
    Serial.println(humVal);

    return;
}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    dht22.begin();
}

void loop() {
    buttonPressed = !digitalRead(BUTTON_PIN);
    if (buttonPressed && millis() - prevBtnPressTime >= BTN_PRESS_INTERVAL) {
        btnManager.setNextState();
        Serial.println(btnManager.getStateString());
        prevBtnPressTime = millis();
    }

    if (millis() - prevSensorReadTime >= TEMP_READ_TIME) {
        prevSensorReadTime = millis();
        tempVal = dht22.readTemperature();
        humVal = dht22.readHumidity();
        printSensorVals(tempVal, humVal);
    }
}