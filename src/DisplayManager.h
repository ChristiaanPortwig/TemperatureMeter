#include <Arduino.h>
#include <Adafruit_SSD1306.h>

typedef struct Snowflake {
    int x;
    int y;
    int deltaY; //This is the change in y... works with the drawSnowflake method.
} Snowflake;

class DisplayManager{
    public:
        DisplayManager(uint8_t, uint8_t);
        void begin();
        void writeTemp(float);
        void writeHum(float);
        void writeBoth(float, float);
        void freeAll();
    
    private:
        Adafruit_SSD1306 display;
        uint8_t sdaPin;
        uint8_t sclPin;
        int width = 128;
        int height = 32;
        unsigned long lastAnimUpdate = 0;

        int lastWaveFrame = 0;
        void drawWaveAnim(int);        
        unsigned long lastSnowflakeUpdate = 0;
        Snowflake *snowflakes = NULL;
        void drawSnowflakeAnim(int, int);
        int lastSnowmanFrame = 0;
        void drawSnowmanAnim(int);
};