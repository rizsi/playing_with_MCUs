#define F_CPU 1000000

#include <util/delay.h>
#include <avr/io.h>

// PB3
#define PORTMASK 0b1000

int main()
{
	DDRB=PORTMASK;
	while(1)
	{
		PINB=PORTMASK;	// toggle pin
		_delay_us(227);	// ~2200Hz
	}
}

