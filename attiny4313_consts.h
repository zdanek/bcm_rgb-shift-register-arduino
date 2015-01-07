//ATTiny 4313 consts

//LATCH PB7
#define LATCH_HIGH PORTB |= B10000000
#define LATCH_LOW  PORTB &= B01111111

//DATA PB1
#define DATA_HIGH PORTB |= B00000010
#define DATA_LOW  PORTB &= B11111101

//DATA PB1 with control lines low
//#define DATA_HIGH_CTRL_LOW PORTB |= B00000010
//#define DATA_LOW_CTRL_LOW  PORTB &= B11111101

//CLOCK PD6 - setting directly. not masking because it's on different port and masking i very slow
#define CLOCK_HIGH PORTD = B01000000
#define CLOCK_LOW  PORTD = B10111111

//OE PB5
#define OUTPUT_EN_HIGH PORTB |= B00100000 
#define OUTPUT_EN_LOW  PORTB &= B11011111

//Outputs on pins PB7, PB5, PB1, PD6
#define CONFIG_OUTPUTS DDRD |= B01000000; DDRB |= B10100010

