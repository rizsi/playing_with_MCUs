// Battery powered sensor project.
// Processor: ATTINY2313-20PU ISP-MC 5V 2K ISP Flash 20MHz
// Features:
//  * initialization initializes all pins and hardwares for least power use
//  * Loop
//  ** On startup processor executes the measurement using a OWI ds18b20 temperature sensor
//  ** The measured value is sent through radio
//  ** Radio reply is avaited from data receiver
//  *** If reply is not received then a random wait and resend is done 3 times
//  ** Then goes to sleep for about 1 minute using the internal watchdog
//  ** On watchdog wake up the loop restarts


#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB=0xff;
	while(1)
	{
		PORTB=0xff;
		_delay_ms(500);
		PORTB=0x0;
		_delay_ms(500);
	}
}

