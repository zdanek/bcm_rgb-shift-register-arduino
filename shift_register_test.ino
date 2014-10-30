#include <mega16.h>

int const clockPin = 4;    //PD4
int const latchPin = 5;    //PD5
int const dataPin = 6;     //PD6
int const clearPin = 7;    //PD7

int const OUTPUT_BITS = 30;
int const FALSE_BIT = 0;
int const TRUE_BIT = 1;

byte ledValues[OUTPUT_BITS];

#define PRODUCTION

#ifndef PRODUCTION
#define DEBUG(MSG) Serial.println(MSG)
#define DEBUGN(MSG) Serial.print(MSG)
#define DEBUGHEX(LONG) Serial.println(LONG, HEX)
#define DEBUG_BYTES(BYTES, LENGTH) { for (int dc = 0; dc < LENGTH; dc++) DEBUGHEX(BYTES[dc]); }
#else
#define DEBUGHEX(LONG) 
#define DEBUG(MSG) 
#define DEBUGN(MSG)
#define DEBUG_BYTES(BYTES, LENGTH)
#endif

#define DELAY(ms) delay(ms);

void setup() {
    
    DDRD |= B11110000;        //Outputs on pins 4,5,6,7

    PORTD &= B11001111;    //latchPin, clockPin LOW
    PORTD |= B10000000;    //clearPin HIGH
    
    #ifndef PRODUCTION
    Serial.begin(9600);
    #endif  

    DEBUG("Hello!");
}

#define LATCH_HIGH PORTD |= B00100000
#define LATCH_LOW PORTD &= B11011111

#define DATA_HIGH PORTD |= B01000000
#define DATA_LOW PORTD &= B10111111

#define CLOCK_HIGH PORTD |= B00010000
#define CLOCK_LOW PORTD &= B11101111

void loop() {

        ledValues[0] = (byte) 30;
        ledValues[1] = (byte) 21;
        ledValues[2] = (byte) 0;
        ledValues[3] = (byte) 100;
        ledValues[4] = (byte) 128;
        ledValues[5] = (byte) 170;
        ledValues[6] = (byte) 200;
        ledValues[7] = (byte) 255;

        while (true) {

            for (int i = 0; i < 255; i++) {
                for (int j = 0; j < OUTPUT_BITS; j++) {
                    if (ledValues[j] > i) 
                        DATA_HIGH;
                    else
                        DATA_LOW;
                    
                    CLOCK_HIGH;
                    CLOCK_LOW;
                }

                LATCH_HIGH;
                LATCH_LOW;
            }
        }

}

//LOOP
//DataIn clock - wsuwa dane
//DataStore - kopiuje

