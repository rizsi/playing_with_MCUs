/**
 * Board support package for Wireless Temperature sensor project.

11 general purpose pins are used (ATtiny24 could be enough). 10 is enough if parasitic power is used for the temp sensor.

From the 11 1 is ADC input for battery sensing.

 * MISO MOSI SCL, CE, SNC (IRQ) - 5 (6) radio
 * red, green LEDs                2
 * One wire GND, DQ 2 temp (1?)   2
 * Debug TX                       1
 * VCC measure activate           1
 * VCC measure in (ADC)           1
 * Button input?		  1

14 pins

 * RESET, GND, VCC - 3

 * MCU: ATtiny2313

Top view of DIP socket ATtiny2313

                 ____U____
 /RESET   PA2   1           20  VCC
          PD0   2           19  PB7   SCL
 Debug TX PD1   3           18  PB6   MISO
 OW power PA1   4           17  PB5   MOSI
 OW TEMP  PA0   5           16  PB4   RADIO NCS - chip select active low
 OW GND   PD2   6           15  PB3   RADIO CE - RX/TX enabled active high
          PD3   7           14  PB2   
          PD4   8           13  PB1
          PD5   9           12  PB0   /GREEN LED - active low LED with resistor
          GND  10           11  PD6   /RED LED - active low LED with resistor

RED LED - shows that battery is low
GREEN LED - shows that battery is ok

*/


#define 	F_CPU   1000000UL

#define deepSleepInit() deepSleep(WDTO_1S)
//#define deepSleepPeriod() {for(uint8_t ctr=0;ctr<1;++ctr){deepSleep(WDTO_8S);}deepSleep(WDTO_4S);}
#define deepSleepPeriod() deepSleep(WDTO_1S);
// Deep sleep at min 750 ms - wait for conversion of the temperature sensor
#define deepSleepConversionTime() deepSleep(WDTO_1S)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/wdt.h>

extern void bsp_init();
// Send a byte on the debug serial channel. Wait until TX buffer has free space
extern void USART_sendChar(char data);

// Print a decimal number onto the debug line
extern void debugDecimal(uint16_t n);
extern void debugBinary(uint8_t n);
extern void debugString(const char * str);

/**
 * Deep sleep for a given time. Deep sleep uses very small power.
 */
extern void deepSleep(uint8_t wdto_value);

// Turn the green LED on
#define GREEN_LED_ON(x) if(x){DDRB|=_BV(0);PORTB&=~_BV(0);}else{DDRB&=~_BV(0);PORTB|=_BV(0);}
// Turn the RED LED on
#define RED_LED_ON(x) if(x){DDRD|=_BV(6);PORTD&=~_BV(6);}else{DDRD&=~_BV(6);PORTD|=_BV(6);}

// Good battery voltage limit. Below this RED status LED is blinked TODO must be well adjusted
#define VOLTAGE_LIMIT 512

// Turn the temperature sensor power on/off - o it before interacting with it. After turning on a small delay is required so that the power is stable before requesting communication.
#define OW_TEMP_POWER(x) if(x){DDRD|=_BV(2); PORTD&=~_BV(2); DDRA|=_BV(1); PORTA|=_BV(1); deepSleep(WDTO_15MS);} else {DDRD&=~_BV(2); PORTD|=_BV(2); DDRA&=~_BV(1); PORTA|=_BV(1);}
//#define OW_TEMP_POWER(x) {DDRD|=_BV(2); PORTD&=~_BV(2); DDRA|=_BV(1); PORTA|=_BV(1);}

// PD5
#define DEBUG_PIN_SIGNAL(x) if(x){DDRD|=_BV(5); PORTD&=~_BV(5);}else {PORTD|=_BV(5);}

// DDRD&=~_BV(5);

// #define DEBUG 1

