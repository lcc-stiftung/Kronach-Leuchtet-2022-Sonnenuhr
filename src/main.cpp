// Bibliotheken
#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <DS3231.h>
#include <Wire.h>

#include "LedStripe.h"

// RTC & Time
DS3231 clockRtc;
bool century = false;
bool h12Flag;
bool pmFlag;

uint8_t hour = 0;
uint8_t hourLast = 0;
bool hourChange;

// Set LED Stripe Color and Brightness
uint8_t brightness = 100;
uint8_t brightnessLast = brightness;

// Create LED Stripes Objects

LedStripe Stripe1( Adafruit_NeoPixel(240, 7, NEO_GRB), clockRtc );
LedStripe Stripe2( Adafruit_NeoPixel(240, 8, NEO_GRB), clockRtc );
LedStripe Stripe3( Adafruit_NeoPixel(240, 9, NEO_GRB), clockRtc );
LedStripe Stripe4( Adafruit_NeoPixel(180, 10, NEO_GRB), clockRtc );
LedStripe Stripe5( Adafruit_NeoPixel(180, 11, NEO_GRB), clockRtc );
LedStripe Stripe6( Adafruit_NeoPixel(120, 12, NEO_GRB), clockRtc );
LedStripe Stripe7( Adafruit_NeoPixel(120, 13, NEO_GRB), clockRtc );
LedStripe Stripe8( Adafruit_NeoPixel(120, 2, NEO_GRB), clockRtc );
LedStripe Stripe9( Adafruit_NeoPixel(120, 3, NEO_GRB), clockRtc );
LedStripe Stripe10( Adafruit_NeoPixel(180, 4, NEO_GRB), clockRtc );
LedStripe Stripe11( Adafruit_NeoPixel(180, 5, NEO_GRB), clockRtc );
LedStripe Stripe12( Adafruit_NeoPixel(240, 6, NEO_GRB), clockRtc );

// Get right Stripe for choosen hour

LedStripe& getLedStripe( uint8_t hour ){
    
    switch ( hour ) {

        case 1:
            //Falltrough
        case 13:
            return Stripe1;
        case 2:
            //Falltrough
        case 14:
            return Stripe2;
        case 3:
            //Falltrough
        case 15:
            return Stripe3;
        case 4:
            //Falltrough
        case 16:
            return Stripe4;
        case 5:
            //Falltrough
        case 17:
            return Stripe5;
        case 6:
            //Falltrough
        case 18:
            return Stripe6;
        case 7:
            //Falltrough
        case 19:
            return Stripe7;
        case 8:
            //Falltrough
        case 20:
            return Stripe8;
        case 9:
            //Falltrough
        case 21:
            return Stripe9;
        case 10:
            //Falltrough
        case 22:
            return Stripe10;
        case 11:
            //Falltrough
        case 23:
            return Stripe11;
        case 12:
            //Falltrough
        case 0:
            return Stripe12;
    
        default:
        Serial.println("couldnt Choose the right Stripe for curent Time Fallback to Stripe 1");
            return Stripe1;
    }

}

//#####################################//
//#               SETUP               #//
//#####################################//

void setup() {

    Serial.begin(57600);            // Seriellen Port für Debug starten
    Wire.begin();                   // I2C Interface für die RTC starten

    hour = clockRtc.getHour( h12Flag, pmFlag );
    hourLast = hour - 1;
    hourChange = false;

    LedStripe& ledStripe = getLedStripe( hour );
    ledStripe.init( red, brightness );


}

//#####################################//
//#               LOOP                #//
//#####################################//

void loop() {

    hour = clockRtc.getHour( h12Flag, pmFlag );

    LedStripe& ledStripe = getLedStripe( hour );
    ledStripe.update( red, brightness );

    if( hourLast != hour - 1 ){
        hourLast++;
        hourChange = true;
    }

    if( hourChange == true ){

        brightnessLast--;

        LedStripe& ledStripe = getLedStripe( hourLast );
        ledStripe.updateLast( red, brightnessLast );

        if( brightnessLast == 0 ){
            hourChange = false;
        }
    }

    ///timeDebug();
}

//#####################################//
//#           time for debug          #//
//#####################################//

void timeDebug() {
  Serial.print(clockRtc.getYear(), DEC);
  Serial.print("-");
  Serial.print(clockRtc.getMonth(century), DEC);
  Serial.print("-");
  Serial.print(clockRtc.getDate(), DEC);
  Serial.print(" ");
  Serial.print(clockRtc.getHour(h12Flag, pmFlag), DEC); //24-hr
  Serial.print(":");
  Serial.print(clockRtc.getMinute(), DEC);
  Serial.print(":");
  Serial.println(clockRtc.getSecond());
  
}