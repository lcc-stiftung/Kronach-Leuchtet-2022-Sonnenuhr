#include <LedStripe.h>

//#####################################//
//#            Constructor            #//
//#####################################//

LedStripe::LedStripe( Adafruit_NeoPixel stripe, DS3231 clock )
    : m_stripe( stripe ), m_clock( clock ){
}

//#####################################//
//#           Deconstructor           #//
//#####################################//

LedStripe::~LedStripe(){
}

//#####################################//
//#         Get Stripe Lenght         #//
//#####################################//

uint8_t LedStripe::getLedCount()
{
  return m_stripe.numPixels();
}

//#####################################//
//#          Calculate  Fill          #//
//#####################################//

uint8_t LedStripe::calculateFill(){

    // 120 Leds
    if( getLedCount() == 120 ){
        if( m_clock.getSecond() <= 30 ){
            return m_clock.getMinute() * 2;
        } else {
            return m_clock.getMinute() * 2 + 1;
        }
    }
    
    //180 Leds
    if( getLedCount() == 180 ){
        if( m_clock.getSecond() <= 20 ){
            return m_clock.getMinute() * 3;
        } else if( m_clock.getSecond() <= 40 ) {
            return m_clock.getMinute() * 3 + 1;
        } else {
            return m_clock.getMinute() * 3 + 2;
        }
    }
    
    //240Leds
    if( getLedCount() == 240 ){
        if( m_clock.getSecond() <= 15 ){
            return m_clock.getMinute() * 4;
        } else if( m_clock.getSecond() <= 30 ) {
            return m_clock.getMinute() * 4 + 1;
        } else if( m_clock.getSecond() <= 45 ) {
            return m_clock.getMinute() * 4 + 2;
        } else {
            return m_clock.getMinute() * 4 + 3;
        }
    }

}

//#####################################//
//#               INIT                #//
//#####################################//

void LedStripe::init( LedColor color, uint8_t brightness){

    m_stripe.begin();
    m_stripe.clear();

    setColor( color, brightness );

    m_stripe.fill( m_color, 0, calculateFill() );
    m_stripe.show();

}

//#####################################//
//#              Update               #//
//#####################################//

void LedStripe::update( LedColor color, uint8_t brightness ){
    
    switch( getLedCount() ){

        case 120:
            if( m_clock.getSecond() == 0 || m_clock.getSecond() == 30 ){
                for( int i = 120; i >= calculateFill(); i-- ){
                    sandDrop( i, 30, color, brightness );
                }
            }
            break;

        case 180:
            if( m_clock.getSecond() == 0 || m_clock.getSecond() == 20 || m_clock.getSecond() == 40 ){
                for( int i = 180; i >= calculateFill(); i-- ){
                    sandDrop( i, 20, color, brightness );
                }
            }
            break;

        case 240:
            if( m_clock.getSecond() == 0 || m_clock.getSecond() == 15 || m_clock.getSecond() == 30 || m_clock.getSecond() == 45){
                for( int i = 2400; i >= calculateFill(); i-- ){
                    sandDrop( i, 10, color, brightness );
                }
            }
            break;

        default:
            break;
    }

}

//#####################################//
//#             Set Color             #//
//#####################################//

void LedStripe::setColor( LedColor color, uint8_t brightness ){
    
    switch ( color ){

        case LedColor::red:
            m_color = m_stripe.Color(brightness, 0, 0);
            break;
        case LedColor::green:
            m_color = m_stripe.Color(0, brightness, 0);
            break;
        case LedColor::blue:
            m_color = m_stripe.Color(0, 0, brightness);
            break;
        case LedColor::yellow:
            m_color = m_stripe.Color(brightness, brightness, 0);
            break;
    }

}

//#####################################//
//#             Sanddrop             #//
//#####################################//

void LedStripe::sandDrop( uint8_t index, uint8_t delayMs, LedColor color, uint8_t brightness ){

    setColor( color, brightness / 50 );
        m_stripe.setPixelColor( index, m_color );
    setColor( color, brightness / 30 );
        m_stripe.setPixelColor( index - 1, m_color );
    setColor( color, brightness );
        m_stripe.setPixelColor( index - 2, m_color );
    
    m_stripe.show();
    delay( delayMs );

    m_stripe.setPixelColor( index, 0, 0, 0) ;
    m_stripe.setPixelColor( index - 1, 0, 0, 0) ;

    m_stripe.show();
    delay( delayMs );

}

void LedStripe::updateLast( LedColor color, uint8_t brightness){

    setColor( color, brightness );
    m_stripe.fill( m_color, 0, 240 );
    m_stripe.show();

    if( brightness == 0 ){
        m_stripe.clear();
    }

    delay(100);

}