//v0.1UNO
//tradional shift regs with Ardu serial out - Very slow, but good for dev


int const dataPin = 7;        //Define which pins will be used for the Shift Register control
int const latchPin = 5;
int const clockPin = 4;
int const oePin = 6;

int const OUTPUT_BITS = 8;
int const FALSE_BIT = 0;
int const TRUE_BIT = 1;

int const VALUE_LEVELS = 255;

byte ledValues[OUTPUT_BITS];

#define PRODUCTION

#ifndef PRODUCTION
#define DELAY(ms) delay(ms);
#define DEBUG(MSG) Serial.println(MSG)
#define DEBUGN(MSG) Serial.print(MSG)
#define DEBUGHEX(LONG) Serial.println(LONG, HEX)
#define DEBUGHEXN(LONG) Serial.print(LONG, HEX)
#define DEBUG_BYTES(BYTES, LENGTH) { for (int dc = 0; dc < LENGTH; dc++) DEBUGHEXN(BYTES[dc]); DEBUG(""); }
#else
#define DELAY(ms)
#define DEBUGHEX(LONG) 
#define DEBUGHEXN(LONG)
#define DEBUG(MSG) 
#define DEBUGN(MSG)
#define DEBUG_BYTES(BYTES, LENGTH)
#endif




void setup() {
    pinMode(dataPin, OUTPUT);       //Configure each IO Pin
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(oePin, OUTPUT);

//prepare all control lines in low state, because rising edge is controlling edge
    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, LOW);
    digitalWrite(oePin, LOW);
    //uncomment to disable output
//        digitalWrite(oePin, HIGH);
    
    #ifndef PRODUCTION
    Serial.begin(9600);
    #endif  

    DEBUG("Hello!");
    
        ledValues[0] = (byte) 0;
        ledValues[1] = (byte) 1;
        ledValues[2] = (byte) 1;
        ledValues[3] = (byte) 1;
        ledValues[4] = (byte) 1;
        ledValues[5] = (byte) 0;
        ledValues[6] = (byte) 0;
        ledValues[7] = (byte) 0;
}

void loop() {
     

        boolean outputWord[OUTPUT_BITS];

//      while (true) {

            for (int i = 0; i < VALUE_LEVELS; i++) {
                for (int j = 0; j < OUTPUT_BITS; j++) {
                    outputWord[j] = ledValues[j] > i; //? TRUE_BIT : FALSE_BIT;
                }

                pushToRegister(outputWord);
// hang();
            }
//        }


}

void hang() {
    while (true) {
    };
}

void loop0() {
//BRG
        ledValues[0] = (byte) 1;
        ledValues[1] = (byte) 0;
        ledValues[2] = (byte) 0;
        ledValues[3] = (byte) 0;
        ledValues[4] = (byte) 1;
        ledValues[5] = (byte) 0;
        ledValues[6] = (byte) 0;
        ledValues[7] = (byte) 0;

        boolean outputWord[OUTPUT_BITS];

        while (true) {

            for (int i = 0; i < 255; i++) {
                for (int j = 0; j < OUTPUT_BITS; j++) {
                    outputWord[j] = ledValues[j] > i; //? TRUE_BIT : FALSE_BIT;
                }

                pushToRegister(outputWord);
            }
        }

}

void pushToRegister(byte data[]) {
    DEBUGN("Pushing to reg ");
    DEBUG_BYTES(data, OUTPUT_BITS);
//    dataClear();
    
    for (int i = 0; i < OUTPUT_BITS ; i++) {
        DEBUGHEXN(data[OUTPUT_BITS - i -1]);
        digitalWrite(dataPin, data[OUTPUT_BITS - i -1]);// == FALSE_BIT ? LOW : HIGH);
        tickClock();
    }
    
    tickLatch();
    
    DELAY(2000);
}

void dataClear() {
    digitalWrite(oePin, LOW);
//    DELAY(20);
    digitalWrite(oePin, HIGH);
}

void tickClock() {
    DEBUG("Clock");
    digitalWrite(clockPin, HIGH);
//    DELAY(20);
    digitalWrite(clockPin, LOW);
}

void tickLatch() {
        DEBUG("Latch");
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);    


//    DELAY(20);
    
}


//OE pulled high

//OE pulled low

//LOOP
//Data Clear
//DataIn clock - wsuwa dane
//DataStore - kopiuje

