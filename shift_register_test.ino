//ver 1.2
//#include <mega16.h>

//ATTiny4313

int const clockPin = 4;    //PD2 - case pin 6
int const latchPin = 5;    //PD3 - pin 7
int const dataPin = 7;     //PD5 - pin 9
int const outputEnablePin = 6;    //PD4 - pin 8

//int const OUTPUT_BITS = 30;
byte const FALSE_BIT = 0;
byte const TRUE_BIT = 1;

byte const MAX_SUPPORTED_BITS = 60;

byte ledValues[MAX_SUPPORTED_BITS];

//#define PRODUCTION

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
//receiving
const byte WAITING = 0;
const byte PREAMBLE = 1; 
const byte RECEIVING = 2; 

byte state = WAITING;
byte dataPtr = 0;


byte outputBits = 1;

boolean received = false;  // whether the string is complete


void setup() {
    
    DDRD |= B11110000;        //Outputs on pins 4,5,6,7

    PORTD &= B00001111;    //OE, latchPin, clockPin LOW
//    PORTD |= B10000000;    //outputEnable LOW
//    PORTD |= B10000000;    //outputEnable LOW
    
    Serial.begin(9600);
    DEBUG("Hello!");
    

     //BRG
     
        ledValues[0] = (byte) 1;
        ledValues[1] = (byte) 0;
        ledValues[2] = (byte) 0;
        ledValues[3] = (byte) 0;
        ledValues[4] = (byte) 0;
        ledValues[5] = (byte) 0;
        ledValues[6] = (byte) 1;
        ledValues[7] = (byte) 1;

}

//LATCH 5
#define LATCH_HIGH PORTD |= B00100000
#define LATCH_LOW PORTD &= B11011111

//DATA 7
#define DATA_HIGH PORTD |= B10000000
#define DATA_LOW PORTD &= B01111111

//CLOCK 4
#define CLOCK_HIGH PORTD |= B00010000
#define CLOCK_LOW PORTD &= B11101111

//OE 6
#define OUTPUT_EN_HIGH PORTD |= B01000000 
#define OUTPUT_EN_LOW PORTD &= B10111111

void loop() {

            for (int i = 0; i < 255; i++) {
                for (int j = outputBits -1; j >= 0; j--) {
                    if (ledValues[j] > i) {
                        DATA_HIGH;
                        DEBUG("D[1]");
                    }
                    else {
                        DATA_LOW;
                        DEBUG("D[0]");
                    }
                    DELAY(500);
                    CLOCK_HIGH;
                DEBUG("   C[1]");                    
                    DELAY(500);
                    CLOCK_LOW;
                DEBUG("   C[0]");

                }

                LATCH_HIGH;
                DEBUG("       L[1]");
                DELAY(1000)
                LATCH_LOW;
                DEBUG("       L[0]");
                DELAY(1000);
                
            }
}

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


