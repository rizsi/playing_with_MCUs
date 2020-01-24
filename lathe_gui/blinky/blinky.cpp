// Blinky example

#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include <inttypes.h>
#include <stdbool.h>

int main ()
{
	while(1)
	{
		DDRB|=_BV(0);
		PORTB|=_BV(0);
		_delay_ms(500);
		PORTB&=~_BV(0);
		_delay_ms(500);
	}
}

