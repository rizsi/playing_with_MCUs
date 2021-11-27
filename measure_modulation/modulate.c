/** Simple signal generator for measurement purpose. */

// This is defined in the Makefile instead
// #define 	F_CPU   16000000UL
#include <util/delay.h>
#include <avr/io.h>

static void loop();
int main()
{
	// Initialize D4-D2 pins to output LOW
	PORTD=0b00000000;
	DDRD =0b00011100;
	while(1)
	{
		loop();
	}
}
#define ACTIVE_US 1
static void loop()
{
	for(int i=0;i<5000;++i)
	{
//		_delay_us(ACTIVE_US);
		PORTD=0b00010100;
		_delay_us(10);
		PORTD=0b00011000;
		_delay_us(10);
	}
	PORTD=0b00000000;
}
