//ver 1.2.1 UNO
//#include <mega16.h>

//PINS on PCB
//from top
//vcc
//latch
//oe
//data_in
//clk
//gnd

//UNO
#include "uno_consts.h"
//ATTiny4313
//#include "attiny4313_consts.h"

//int const clockPin = 4;    //PD2 - case pin 6
//int const latchPin = 5;    //PD3 - pin 7
//int const dataPin = 7;     //PD5 - pin 9
//int const outputEnablePin = 16;    //PD4 - pin 8

//int const OUTPUT_BITS = 30;
byte const FALSE_BIT = 0;
byte const TRUE_BIT = 1;

byte const MAX_SUPPORTED_BITS = 30;
int const VALUE_LEVELS = 3;

byte ledValues[MAX_SUPPORTED_BITS];

#define DEMO0
#define PRODUCTION

#ifndef PRODUCTION
#define DEBUG(MSG) Serial.println(F(MSG))
#define DEBUGN(MSG) Serial.print(F(MSG))
#define DEBUGHEX(LONG) Serial.println(LONG, HEX)
#define DEBUGHEXN(LONG) Serial.print(LONG, HEX)
#define DEBUG_BYTES(BYTES, LENGTH) { for (int dc = 0; dc < LENGTH; dc++) DEBUGHEXN(BYTES[dc]); DEBUG(""); }
#define DEBUGL(LONG) Serial.print(LONG)
#define DELAY(ms) delay(ms); 
#else
#define DEBUGHEX(LONG) 
#define DEBUGHEXN(LONG)
#define DEBUG(MSG) 
#define DEBUGN(MSG)
#define DEBUG_BYTES(BYTES, LENGTH)
#define DEBUGL(LONG)
#define DELAY(ms)
#endif

//receiving
const byte WAITING = 0;
const byte PREAMBLE = 1; 
const byte RECEIVING = 2; 

byte state = WAITING;
byte dataPtr = 0;

byte outputBits = 8;

boolean received = false;  // whether the string is complete

byte rInc = 4;
byte gInc = 15;
byte bInc = 9;

byte r = 0;
byte g = 60;
byte b = 128;

unsigned long demoCnt =4;

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
    

     //RGB
//first and last bit in byte is unused     
        ledValues[0] = (byte) 0;
        ledValues[1] = (byte) 2; //R
        ledValues[2] = (byte) 0; //G
        ledValues[3] = (byte) 0; //B
        ledValues[4] = (byte) 0; //R
        ledValues[5] = (byte) 2; //G
        ledValues[6] = (byte) 0; //B
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


void allRed() {
  outputBits = 8;
        ledValues[0] = (byte) 0;
        ledValues[1] = (byte) 2; //R
        ledValues[2] = (byte) 0; //G
        ledValues[3] = (byte) 0; //B
        ledValues[4] = (byte) 2; //R
        ledValues[5] = (byte) 0; //G
        ledValues[6] = (byte) 0; //B
        ledValues[7] = (byte) 0;
}

void allBlue() {
  outputBits = 8;
        ledValues[0] = (byte) 0;
        ledValues[1] = (byte) 0; //R
        ledValues[2] = (byte) 0; //G
        ledValues[3] = (byte) 2; //B
        ledValues[4] = (byte) 0; //R
        ledValues[5] = (byte) 0; //G
        ledValues[6] = (byte) 2; //B
        ledValues[7] = (byte) 0;
}

void allGreen() {
  outputBits = 8;
        ledValues[0] = (byte) 0;
        ledValues[1] = (byte) 0; //R
        ledValues[2] = (byte) 2; //G
        ledValues[3] = (byte) 0; //B
        ledValues[4] = (byte) 0; //R
        ledValues[5] = (byte) 2; //G
        ledValues[6] = (byte) 0; //B
        ledValues[7] = (byte) 0;
}

void loop() {


            for (byte i = 0; i < VALUE_LEVELS; i++) {
                for (short j = outputBits -1; j >= 0; j--) {
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

    #ifdef DEMO
    tickDemo();
    #endif
    
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (state == WAITING) {
        if (inChar != '[') {
            continue;
        } else {
          DEBUG("PREAMBLE!");
            state = PREAMBLE;
//allBlue();
            continue;
        }
    } else if (state == PREAMBLE) {
        outputBits = (byte)inChar;
        state = RECEIVING;
        DEBUG("RECEIVING, expected length: ");
        DEBUGL(outputBits);

//allGreen();
        continue;
    } else {        //receiving
         ledValues[dataPtr] = inChar;
         if (dataPtr == outputBits || dataPtr == MAX_SUPPORTED_BITS) {
             state = WAITING;
             received = true;
             dataPtr = 0;
//allRed();
            DEBUG("DONE!->WAITING");
            DEBUG_BYTES(ledValues, outputBits);
            continue;
         }

         dataPtr++;
     }
        
  }
}


void tickDemo()
{
    demoCnt--;
    DEBUGHEX(demoCnt);
    if (demoCnt > 0L) {
        return;
    }
    
    demoCnt = 80;

        DEBUGHEX(demoCnt);
    DEBUG("DUUUUUUUUUUPA");
    r+=rInc;
    g+=gInc;
    b+=bInc;
    
    ledValues[1] = r;
    ledValues[2] = g;
    ledValues[3] = b;
}

