// Wireless sensor

#define 	F_CPU   500000UL

#include <inttypes.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <util/delay.h>

/*

Description of FUSE settings:
 Device Clocking Select(1)   Device Clocking Option CKSEL3..0
 Calibrated Internal RC Oscillator 4MHz   0010


 Program CKDIV8 to 1

 Program BODLEVEL - brown out detector OFF


So main freq is 0.6MHz

Top view of DIP socket ATtiny13A-PU

                                            ____U____
/RESET                              PB5   1           20  VCC
                                    PB3   2           19  PB2  SCK
                                    PB4   3           18  PB1  MISO
                                    GND   4           17  PB0  MOSI

*/







__attribute__((naked))
__attribute__((noreturn))
void main ()
{
	// All pins set to pullup
	DDRB=0b00000000;
	PORTB=0b11111111;

	_delay_ms(1000);	// Wait some after boot so that all pins have stable values
}

