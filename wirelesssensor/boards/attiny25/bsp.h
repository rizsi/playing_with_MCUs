/**
 * Board support package for Wireless Temperature sensor project.
 * MCU: ATTiny25

Top view of DIP socket ATtiny25

                         ____U____
 /RESET           PB5   1           20  VCC
    CE,LEDs+      PB3   2           19  PB2   SCL
NCS               PB4   3           18  PB1   MOSI/MISO
                  GND  10           11  PB0   DEBUG TX, DQ

 * VCC connected direct to battery - not regulated so it is possible to measure battery compared to internal VBG reference
 * MOSI/MISO - input from radio is connected through a resistor - it is possible to sense input on the same line
 * Button input resistor is big enough that it can not pull down an active high but it can pull down a pullup high.
 * Button press while NCS is high will activate the LED! Must be designed so that the LED current keeps it in the low value
 ** Pullup: 30-60kOhm
 ** LED resistor: 2000 Ohm
 ** Button pulldown resistor: 3kOhm - button sensing is possible only when CE/LED+ is off

 * CE is normally 0 (1 is possible when radio is in OFF mode)
 * NCS is normally 1
 * SCL/DQ is normally low (no parasitic power given to the Thermo chip)
 */
#ifndef BSP_H
#define BSP_H
#define 	F_CPU   1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/wdt.h>

#include <bitbanguart.h>

#define BITBANG_UART_OUT_LOW() {PORTB&=~_BV(0); DDRB|=_BV(0);}
#define BITBANG_UART_OUT_HIGH() {PORTB|=_BV(0); DDRB|=_BV(0);}

// There is no UART/USART on this chip - bitbang output must be implemented if it is a must
//#define USART_sendChar(data) bitbang_uart_send(data) 
// disable USART debugging
#define USART_sendChar(data)

#define deepSleepInit() deepSleep(WDTO_1S)
extern void deepSleepPeriod();
// Deep sleep at min 750 ms - wait for conversion of the temperature sensor
extern void deepSleepConversionTime();


extern void bsp_init();

// Print a decimal number onto the debug line
extern void debugDecimal(uint16_t n);
extern void debugBinary(uint8_t n);
extern void debugString(const char * str);

/**
 * Deep sleep for a given time. Deep sleep uses very small power.
 */
extern void deepSleep(uint8_t wdto_value);

/**
 * Mark the BSP subsystem that radio communication is beginning.
 */
#define radioSessionBegin()
/**
 * Mark the BSP subsystem that radio communication has ended.
 */
#define radioSessionEnd()

// Turn the green LED on
#define GREEN_LED_ON(x)
// TODO  if(x){DDRB|=_BV(0);PORTB&=~_BV(0);}else{DDRB&=~_BV(0);PORTB|=_BV(0);}
// Turn the RED LED on
#define RED_LED_ON(x)
// TODO if(x){DDRD|=_BV(6);PORTD&=~_BV(6);}else{DDRD&=~_BV(6);PORTD|=_BV(6);}

// Good battery voltage limit. Below this RED status LED is blinked TODO must be well adjusted
#define VOLTAGE_LIMIT 512

// Turn the temperature sensor power on/off - 0 it before interacting with it. After turning on a small delay is required so that the power is stable before requesting communication.
// On ATTiny25 we also initialize ADC to read the battery in this step
extern void OW_TEMP_POWER(bool on);

// Debug pin is not possible beacuse we have no unused pins
// #define DEBUG_PIN_SIGNAL(x)

// #define DEBUG 1

// Pull the OW interface to active low
#define BSP_OW_LOW()  {DDRB|=_BV(0);PORTB&=~_BV(0);}
// Release OW and apply pullup resistor on OW
#define BSP_OW_PULLUP()  {DDRB&=~_BV(0);PORTB|=_BV(0);}
// DQ Active HIGH power mode (when parasitic power is used. Otherwise same as pullup.)
#define BSP_OW_HIGH()  {PORTB|=_BV(0);DDRB|=_BV(0);}
// Read current state of OW: LOW:0 HIGH:1
#define BSP_OW_READ() ((PINB&_BV(0))!=0)
// delayMicroseconds - wait for the given microseconds

#define owDelayMillis(x) _delay_ms(x)
#define owDelayMicroseconds(x) _delay_us(x)



// Logging is disabled
#define BSP_OW_LOG_CH(A)
#define BSP_OW_LOG_NUM(A)
#define BSP_OW_LOG_LN()


/*
// Logging is enabled
#define BSP_OW_LOG_CH(A) USART_sendChar(A)
#define BSP_OW_LOG_NUM(A) debugDecimal(A)
#define BSP_OW_LOG_LN() USART_sendChar('\n')
*/


// nRF24L01 Radio hardware bindings

// Chip select for the radio SPI
extern void RADIO_BEGIN();
// Chip deselect for the radio SPI
extern void RADIO_END();
// Enable Radio RX or TX
#define RADIO_SET_ENABLED(enabled) if(enabled){PORTB|=_BV(3);DDRB|=_BV(3);}else{PORTB&=~_BV(3);DDRB|=_BV(3);}

extern void RADIO_PINS_INIT();
extern uint8_t RADIO_SPI(uint8_t transmit);

/** Get raw voltage value. Always called after temperature readout. */
extern uint16_t bspGetVoltage();

/** Button 1 was pressed since last clear of the state */
extern bool bspButton1Pressed();
/** Clear the pressed state of button1 */
extern void bspButton1Clear();

//   SPI.begin();
//  SPI.setClockDivider(SPI_CLOCK_DIV128);


/*
// Debug logging disabled
#define RADIO_DEBUG_CH(x)
#define RADIO_DEBUG_BIN(x)
#define RADIO_DEBUG_STR(x)
#define RADIO_DEBUG_DEC(x)
#define RADIO_DEBUG_HEX(x)
*/

// Radio debug logging
#define RADIO_DEBUG_CH(x) {_delay_ms(20); USART_sendChar(x);}
#define RADIO_DEBUG_BIN(x) debugDecimal(x)
#define RADIO_DEBUG_STR(x) debugString(x)
#define RADIO_DEBUG_DEC(x) debugDecimal(x)
#define RADIO_DEBUG_HEX(x) debugDecimal(x)

#endif



