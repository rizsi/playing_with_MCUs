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
#include <stdint.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/io.h>
#include <util/delay.h>

static void WDT_off(void);

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void WDT_Prescaler_Change(uint8_t ii)
{
//	uint8_t bb;
//	if (ii > 9 ) ii=9;	// 0-9 are the valid values
//	bb=ii & 7;
//	if (ii > 7) bb|= (1<<5);


	cli();
	wdt_reset();
	/* Start timed  equence */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
	WDTCSR  = (1<<WDIE) | (1<<WDP2) | (1<<WDP0);

	sei();
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {
  uint8_t bb;
	cli();
//  int ww;
  if (ii > 9 ) ii=9;	// 0-9 are the valid values
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= _BV(WDIE);
  wdt_reset();
 // ww=bb;
 
  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;

  sei();
}
  
// Watchdog Interrupt Service / is executed when watchdog timed out
// An empty handler is required at least: no handler will reset the chip when this IT happens
ISR(WDT_OVERFLOW_vect) {
//  f_wdt=1;  // set global flag
//	PORTB=~PORTB;
}


static void mysleep(uint8_t sleepConstant)
{
//    ADCSRA &= ~_BV(ADEN);                   // ADC off
	setup_watchdog(sleepConstant);
//	WDT_Prescaler_Change(5);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	if (1) // Condition is possible that something happened before going cli
	{
		sleep_enable();
//		sleep_bod_disable();
		sei();
		sleep_cpu();
		sleep_disable();
	}
	sei();
//	WDT_off();


/*    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement
    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep
    cli();                                  // Disable interrupts
    sleep_disable();                        // Clear SE bit
    sei();                                  // Enable interrupts
*/
}

static void WDT_off(void){
	cli();
	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;
	sei();
}

int main(void)
{
	// Output - measure power usage while LED is off
	DDRB=0xff;
 	// Activate Pullup on unused pins: no accidental changes on pin input logic
	DDRA=0x0;
	DDRD=0x0;
	PORTA=0xff;
	PORTD=0xff;
	for(uint8_t i=0;i<5;++i)
	{
		// Visualize reset
		PORTB=0xff;
		_delay_ms(50);
		PORTB=0x0;
		_delay_ms(50);
	}
	while(1)
	{
		PORTB=0xff;
		//_delay_ms(500);
		mysleep(0); // Short pulse in every 8 seconds
		PORTB=0x0;
		//_delay_ms(200);
		mysleep(3);
	}
}

