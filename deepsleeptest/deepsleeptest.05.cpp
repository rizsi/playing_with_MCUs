// Wireless sensor

#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/wdt.h>

#include <inttypes.h>
#include <stdbool.h>


__attribute__((OS_main))
int main ()
{
DDRB=0b00000000; PORTB=0b11111111;
DDRC=0b00000000; PORTC=0b11111111;
 DDRD=0b00000000; PORTD=0b11111111;
//	CLKPR=0b10000000; // Enable clock prescaler change
//	CLKPR=0b00001000; // div256
	ACSR|=_BV(ACD); // Turn Analog comparator off to spare some power!
	PRR=0xff;
MCUSR = 0;
wdt_disable();	
	while(1)
	{
	ACSR|=_BV(ACD); // Turn Analog comparator off to spare some power!
		// Choose our preferred sleep mode:
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	// Set sleep enable (SE) bit:
	sleep_enable();
	sei();
	// Put the device to sleep:
	sleep_mode();

	// Upon waking up, sketch continues from this point.
	sleep_disable();
	}
}

