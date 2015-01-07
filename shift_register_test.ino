//ver 1.2.1 UNO
//#include <mega16.h>

//UNO
//#include "uno_consts.h"
//ATTiny4313
#include "attiny4313_consts.h"

//int const clockPin = 4;    //PD2 - case pin 6
//int const latchPin = 5;    //PD3 - pin 7
//int const dataPin = 7;     //PD5 - pin 9
//int const outputEnablePin = 16;    //PD4 - pin 8

//int const OUTPUT_BITS = 30;
byte const FALSE_BIT = 0;
byte const TRUE_BIT = 1;

byte const MAX_SUPPORTED_BITS = 30;
int const VALUE_LEVELS = 255;

byte ledValues[MAX_SUPPORTED_BITS];

#define PRODUCTION

#ifndef PRODUCTION
#define DEBUG(MSG) Serial.println(F(MSG))
#define DEBUGN(MSG) Serial.print(F(MSG))
#define DEBUGHEX(LONG) Serial.println(LONG, HEX)
#define DEBUGHEXN(LONG) Serial.print(LONG, HEX)
#define DEBUG_BYTES(BYTES, LENGTH) { for (int dc = 0; dc < LENGTH; dc++) DEBUGHEXN(BYTES[dc]); DEBUG(""); }
#define DELAY(ms) delay(ms);
#else
#define DEBUGHEX(LONG) 
#define DEBUGHEXN(LONG)
#define DEBUG(MSG) 
#define DEBUGN(MSG)
#define DEBUG_BYTES(BYTES, LENGTH)
#define DELAY(ms)
#endif

//receiving
const byte WAITING = 0;
const byte PREAMBLE = 1; 
const byte RECEIVING = 2; 

byte state = WAITING;
byte dataPtr = 0;

byte outputBits = 32;

boolean received = false;  // whether the string is complete


void setup() {

        
    CONFIG_OUTPUTS;
    
    LATCH_LOW;
    CLOCK_LOW;
    OUTPUT_EN_LOW;
    
//    PORTD &= B00001111;    //OE, latchPin, clockPin LOW
//    PORTD |= B10000000;    //outputEnable LOW
//    PORTD |= B10000000;    //outputEnable LOW
    
    Serial.begin(9600);
    DEBUG("Hello!");
    

     //BRG
     
        ledValues[0] = (byte) 0;
        ledValues[1] = (byte) 2;
        ledValues[2] = (byte) 2;
        ledValues[3] = (byte) 2;
        ledValues[4] = (byte) 2;
        ledValues[5] = (byte) 2;
        ledValues[6] = (byte) 2;
        ledValues[7] = (byte) 0;
               
        ledValues[8] = (byte) 0;
        ledValues[9] = (byte) 1;
        ledValues[10] = (byte) 0;
        ledValues[11] = (byte) 0;
        ledValues[12] = (byte) 0;
        ledValues[13] = (byte) 0;
        ledValues[14] = (byte) 1;
        ledValues[15] = (byte) 0;
        

        ledValues[16] = (byte) 0;

        ledValues[28] = (byte) 0;
        ledValues[29] = (byte) 1;
        ledValues[30] = (byte) 0;
        ledValues[31] = (byte) 0;


/*
        for (int j=0; j < 5; j++) {
        for (int x=1;x < 7; x+=3) {
            ledValues[j*8 + x] = (byte) 1;
            ledValues[j*8 +x+1] = (byte) 1;
            ledValues[j*8 +x+2] = (byte) 1;
        }
        }
*/

}


void loop() {

            for (int i = 0; i < VALUE_LEVELS; i++) {
                for (int j = outputBits -1; j >= 0; j--) {
                    if (ledValues[j] > i) {
                        DATA_HIGH;
                        DEBUG("D[1]");
                    }
                    else {
                        DATA_LOW;
                        DEBUG("D[0]");
                    }
                    DELAY(50);
                    CLOCK_HIGH;
                DEBUG("   C[1]");                    
                    DELAY(50);
                    CLOCK_LOW;
                DEBUG("   C[0]");

                }

                LATCH_HIGH;
                DEBUG("       L[1]");
                DELAY(50)
                LATCH_LOW;
                DEBUG("       L[0]");
                DELAY(50);
                
            }
}
/*
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (state == WAITING) {
        if (inChar != '[') {
            continue;
        } else {
            state = PREAMBLE;
            continue;
        }
    } else if (state == PREAMBLE) {
        outputBits = (byte)inChar;
        state = RECEIVING;
        continue;
    } else {        //receiving
         ledValues[dataPtr] = inChar;
         if (dataPtr == outputBits || dataPtr == MAX_SUPPORTED_BITS) {
             state = WAITING;
             received = true;
             dataPtr = 0;
             continue;
         }

         dataPtr++;
     }
        
  }
}
*/

