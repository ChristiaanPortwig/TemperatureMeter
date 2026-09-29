#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class DisplayManager{
    public:
        DisplayManager(uint8_t, uint8_t);
        void begin();
        void writeTemp(int);
        void writeHum(int);
        void writeBoth(int, int);
    
    private:
        Adafruit_SSD1306 display;
        uint8_t sdaPin;
        uint8_t sclPin;
        
};