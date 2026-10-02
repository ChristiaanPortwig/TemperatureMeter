#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class DisplayManager{
    public:
        DisplayManager(uint8_t, uint8_t);
        void begin();
        void writeTemp(float);
        void writeHum(float);
        void writeBoth(float, float);
    
    private:
        Adafruit_SSD1306 display;
        uint8_t sdaPin;
        uint8_t sclPin;
        int width = 128;
        int height = 32;
        void drawWaveAnim(unsigned long, int);        
};