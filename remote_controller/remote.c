// 4 button IR Remote controller

#define 	F_CPU   8000000UL
#define N_PRESS_TO_TOGGLE 10

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

 Program BODLEVEL - brown out detector:

 101 - 2.7V
 100 - 4.3V



So main freq is 0.6MHz


Top view of DIP socket ATtiny25

                 ____U____
 /RESET   PB5   1           8  VCC
 Button4  PB3   2           7  PB2   SCK,   Button1
 /IR LED  PB4   3           6  PB1   MISO,   Button2
          GND   4           5  PB0   MOSI,   Button3

Additional circuits:

 * Connect Battery to GND/VCC. Chip is Always on in deep sleep waiting for button press
 * Remove battery while programming (if using programmer that supports power)
 * Buttons short the pin to GND. Do not press buttons while programming
*/

/*
pattern_minus: 0xE0E0D02F
    .byte 0B11100000
    .byte 0B11100000
    .byte 0B11010000
    .byte 0B00101111
    
pattern_plus: 0xE0E0E01F
    .byte 0B11100000
    .byte 0B11100000
    .byte 0B11100000
    .byte 0B00011111

pattern_power: 0xE0E040BF
    .byte 0B11100000
    .byte 0B11100000
    .byte 0B01000000
    .byte 0B10111111
*/
ISR(	PCINT0_vect)
{
// Flag is auto-cleared but why not clear again.
GIFR|=0b00100000;
// ISR is not handled it was just used to break the sleep of the MCU
}
static uint32_t codes[4]={0xE0E0D02F,1,2,3};

static bool is_pressed(uint8_t pin)
{
return false;
}
static void sendOnNPeriod(uint8_t nperiod)
{
// 4MHz clock: 4000000÷38000 = 105,263157895
// One cycle should be 105. 100 DDRB|= lines are necessary
	while(nperiod>0)
	{
	// 1 cycle for each line and 5 cycles to increment and loop (ASM was checked)
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB|= 0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	DDRB&=~0b00010000;
	nperiod--;
	}
}
/// Send an on signal for given us
/// @param us max value is 6630 (255 periods of 38khz signal)
static void sendOn(uint16_t us)
{
	// 38kHz
	// one period is 26,316 us
	uint8_t nperiod=(uint8_t)(((uint32_t)us)*1000/26316); // 26,316
  sendOnNPeriod(nperiod);
}

// Takes about 110ms
void sendCode(uint32_t code)
{
	sendOn(4500);
	_delay_us(4500);  // Start signal
	for(uint8_t i=0;i<32;++i)
	{
		sendOn(600);
		if(((int32_t)code)<0)
		{
			_delay_us(1650);
		}else
		{
			_delay_us(600);
		}
	}
	sendOn(600);	// Close signal	
	_delay_us(46000);	// Close signal
}

__attribute__((naked))
__attribute__((noreturn))
void main ()
{
	// MCU is active once battery is connected
	// All button pins set to pullup
	// Except pwm output because that is set to input low
	DDRB =0b00000000;
	PORTB=0b11101111;
	
	GIMSK=0b100000; // PCIE Pin Change Interrupt enabled
	PCMSK=0b1111; // PB0-3 causes IRQ
	sei();

	while(true)
	{
		bool active=false;
		for(uint8_t i=0;i<4;++i)
		{
			if(is_pressed(i))
			{
				sendCode(codes[i]);
				active=true;
			}
		}
		if(!active)
		{
			MCUCR=0b00110000;
			asm("SLEEP"); // Sleep is broken by any Pin Change Interrupt. Otherwise sleep forewer
			MCUCR=0b00010000;
		}
	}
}

