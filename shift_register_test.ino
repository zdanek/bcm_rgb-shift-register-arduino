int const dataPin = 7;        //Define which pins will be used for the Shift Register control
int const latchPin = 5;
int const clockPin = 4;
int const oePin = 6;

int const OUTPUT_BITS = 6;
int const FALSE_BIT = 0;
int const TRUE_BIT = 1;

byte ledValues[OUTPUT_BITS];

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

#define DELAY(ms) //delay(ms);

void setup() {
    pinMode(dataPin, OUTPUT);       //Configure each IO Pin
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(oePin, OUTPUT);

    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, LOW);
    digitalWrite(oePin, LOW);
    //uncomment to disable output
//        digitalWrite(oePin, HIGH);
    
    #ifndef PRODUCTION
    Serial.begin(9600);
    #endif  

    DEBUG("Hello!");
}

void loop() {
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
    DEBUG("Pushing to reg");
    DEBUG_BYTES(data, OUTPUT_BITS);
//    dataClear();
    
    for (int i = 0; i < OUTPUT_BITS ; i++) {
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
//    DELAY(20);
    digitalWrite(latchPin, LOW);
}


//OE pulled high

//OE pulled low

//LOOP
//Data Clear
//DataIn clock - wsuwa dane
//DataStore - kopiuje

