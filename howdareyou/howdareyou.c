// How dare you??????? Watch music clip: G.T - How Dare You https://www.youtube.com/watch?v=rbrdRcwZE6Q

#define 	F_CPU   500000UL
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

Fuse settings for 5V (4.3V brown out detection)
-U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

Fuse settings for 3.3V (2.7V BOD)
-U lfuse:w:0x62:m -U hfuse:w:0xdb:m -U efuse:w:0xff:m 

Description of FUSE settings:
 Device Clocking Select(1)   Device Clocking Option CKSEL3..0
 Calibrated Internal RC Oscillator 4MHz   0010


 Program CKDIV8 to 1

 Program BODLEVEL - brown out detector:

 101 - 2.7V
 100 - 4.3V



So main freq is 0.6MHz


Top view of DIP socket ATtiny2313

                 ____U____
 /RESET   PA2   1           20  VCC
          PD0   2           19  PB7   SCL
          PD1   3           18  PB6   MISO
          PA1   4           17  PB5   MOSI
          PA0   5           16  PB4
          PD2   6           15  PB3
          PD3   7           14  PB2   /Button pull output - (active LOW)
          PD4   8           13  PB1
          PD5   9           12  PB0
          GND  10           11  PD6   /LED sense input - (active LOW)

Top view of DIP socket ATtiny13A-PU

                                            ____U____
/RESET                              PB5   1           20  VCC
/LED sense input - (active LOW)     PB3   2           19  PB2  SCK
/Button pull output - (active LOW)  PB4   3           18  PB1  MISO
                                    GND   4           17  PB0  MOSI

Additional circuits:

 * Connect ICSP connector for easy reprogramming of chip
 * Voltage regulator+capacitors to power from the 12V socket
 * Optocoupler with proper current limiting resistor to sense red LED
 ** When LED is active PB3 is pulled to ground through the optocoupler
 * PB4 Optocoupler that is activated when PB4 is forced to GND
 ** This optocoupler pulls the button to ground and so simulates a button press
 * Connect reset to VCC using a 10kOhm resistor
 * All other pins can be floating - will be set to pullup by code.
*/

static void pressButton()
{
	PORTB&=~_BV(4);
	DDRB|=_BV(4);
	_delay_ms(200); // 200 ms "button press"
	DDRB&=~_BV(4);
	PORTB|=_BV(4);
}

static bool isLed()
{
	return (PINB & _BV(3))==0;
}

static bool waitShortChange(bool prev)
{
	for(uint8_t i=0;i<10;++i)
	{
		_delay_ms(100);
		if(isLed()!=prev)
		{
			return 1;
		}
	}
	return 0;
}

static void pulse(uint8_t pulses)
{
	for(uint8_t i=0;i<pulses;++i)
	{
		if(i!=0)
		{
			_delay_ms(1000);
		}
		pressButton();
		_delay_ms(1000);
		pressButton();
	}
}

__attribute__((naked))
__attribute__((noreturn))
void main ()
{
	// MCU is active when ignition switch is at least in stage I - measured on the 12V socket
	// All pins set to pullup
	DDRB=0b00000000;
	PORTB=0b11111111;

	_delay_ms(1000);	// Wait some after boot so that all pins have stable values
	bool currentSetting=eeprom_read_byte((const uint8_t *)1);
	if(currentSetting) // Current setting loaded from EEPROM
	{
		while(!isLed())
		{
			_delay_ms(2000);
			if(!isLed())
			{
				pressButton();
				_delay_ms(500); // Wait before sampling the LED status
			}
		}
	}
	bool prevLED=isLed();
	while(1)
	{
		for(uint8_t ctr=0;ctr<N_PRESS_TO_TOGGLE;++ctr)
		{
			if(waitShortChange(prevLED))
			{
				prevLED=!prevLED;
				if(ctr==(N_PRESS_TO_TOGGLE-1))
				{
					currentSetting=!currentSetting;
					eeprom_write_byte((uint8_t *)1, currentSetting);

					_delay_ms(5000); // Wait before signalling
					if(currentSetting)
					{
						// Turned on: 2 pulses
						pulse(2);
					}else
					{
						// Turned off: 1 pulse
						pulse(1);
					}
				}
			}else
			{
				ctr=100; // Exit loop - reset counter
			}
		}
	}
}

