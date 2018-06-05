#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

const uint16_t signalSamples[] PROGMEM={
#define SAMSUNG_BASE 0
#include "samsung_ak59_00149a.h"
};
// Will overflow at about every half second
volatile uint16_t overflowCounter=0;

// Timer/Counter0 overflow interrupt vector
ISR (TIMER0_COMPB_vect) {
	overflowCounter++;
}
/// Based on http://playground.arduino.cc/Main/PinChangeInterrupt
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
//   long t=micros();
 //  uint8_t input=digitalRead(datain);
 //  segments[currentSegment]=(uint16_t)(t-timeSignalLast);
 //  currentSegment++;
 //  timeSignalLast=t;
//  Uncommenting this line helps debugging whether something happens or not
//   digitalWrite(led,input);
}
/**
 * Get the current time from timer0 and overflowCounter
 * @return 24 bit value which overflows after 24 bits!
 */
uint32_t timeGetTicks()
{
	uint32_t m;
	uint8_t ctr;
	uint8_t tifr;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		m = overflowCounter;
		ctr=TCNT0;
		tifr=TIFR0;
	}
	uint8_t ovf=(tifr & _BV(TOV0)) && (ctr <128);
	if(ovf);
	{
		ctr+=256;
	}
	m<<=8;
	m+=ctr;
	return m;
}
uint8_t bb[4];
uint8_t cc[4];
int main(void)
{
  bb[1]=0;
  cc[1]=0;
  OSCCAL += 3;                // Due to 5V VCC we speed up the internal oscillator a little. This is a well known trick on the internet 
  // Setup timer0 to no prescaler, overflow at 255 and interrupt at overflow


//     DDRB = 1 << PINB4;          // Set PB4 to output
/*
     TCNT0 = 0;                  // Count up from 0
     TCCR0A = 2<<WGM00;          // CTC mode
     if (CLKPR == 3)             // If clock set to 1MHz
         TCCR0B = (1<<CS00);     // Set prescaler to /1 (1uS at 1Mhz)
     else                        // Otherwise clock set to 8MHz
         TCCR0B = (2<<CS00);     // Set prescaler to /8 (1uS at 8Mhz)
     GTCCR |= 1 << PSR0;         // Reset prescaler
     OCR0A = 49;                 // 49 + 1 = 50 microseconds (10KHz)
     TIFR = 1 << OCF0A;          // Clear output compare interrupt flag
     TIMSK |= 1<<OCIE0A;         // Enable output compare interrupt
     sei();                      // Enable global interrupts
     
     while (1) {}
*/
}

