#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <DS3231.h>

enum LedColor{ red, green, blue, yellow };

class LedStripe{

    public:

        LedStripe(Adafruit_NeoPixel stripe, DS3231 clock);
        ~LedStripe();

        uint8_t getLedCount();

        uint8_t calculateFill();

        void init( LedColor color, uint8_t brightness);
        void update( LedColor color, uint8_t brightness );
        void setColor( LedColor color, uint8_t brightness );

        void updateLast( LedColor color, uint8_t brightness );

    private:

        Adafruit_NeoPixel m_stripe;
        DS3231 m_clock;

        uint32_t m_color;

        void sandDrop( uint8_t index, uint8_t delay, LedColor color, uint8_t brightness );

};