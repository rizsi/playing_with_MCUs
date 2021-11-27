
#include <avr/io.h>
#include <stdint.h>
#include <debug_uart0.h>
#include <sensor.h>
#include <util/delay.h>
#include <motor.h>

#include <motor.h>

// PWM A: 11 PB3 OC2A
// A1: 12 PB4    A2: 13 PB5

// PWM B: 2 PD3 OC2B
// B1: 8 PB0        B2: 10 PB2

void motor_init()
{
	// Motor control pins to 0
	PORTB&=~_BV(3)&~_BV(4)&~_BV(5)&~_BV(0)&~_BV(2);
	// Motor control pins Output mode
	DDRB|=_BV(3)|_BV(4)|_BV(5)|_BV(0)|_BV(2);
	
	
	// initialize TCCR2 as: fast pwm mode, non inverting
	TCCR2A = (1<<COM2B1) | (0<<COM2B0) | (1<<COM2A1) | (0<<COM2A0) |(1<<WGM21) | (1<<WGM20);
	TCCR2B = (1<<CS21) | (0<<WGM22); // clkT2S/8 prescale
	// OC2RA pin made as output
	DDRB |= (1<<PB3);
	DDRD |= (1<<PD3);
	OCR2A = 0;
	OCR2B = 0;
/*	// connect pwm to pin on timer 2, channel A
				sbi(TCCR2A, COM2A1);
				 val; // set pwm duty
			case TIMER2B:
				// connect pwm to pin on timer 2, channel B
				sbi(TCCR2A, COM2B1);
				OCR2B = val; // set pwm duty
*/
}
#define ZERO 30
void motor_set(int16_t l, int16_t r)
{
	if(l==0)
	{
		// Motor control pins to 0
//		PORTB&=~_BV(3)&~_BV(4)&~_BV(5);
		PORTB|=_BV(3)|_BV(4)|_BV(5); // Brake
		OCR2A = 0;
	}else if(l<0)
	{
		PORTB&=~_BV(5);
		PORTB|=_BV(4);
		
		OCR2A = -l+ZERO;
//		UART0_Send_int32(-l);
//		UART0_Send('\n');
//		PORTB|=_BV(3);
	}else
	{
		PORTB|=_BV(5);
		PORTB&=~_BV(4);

		OCR2A = l+ZERO;
//		UART0_Send_int32(l);
//		UART0_Send('\n');
		
//		PORTB|=_BV(3);
	}

	if(r==0)
	{
		// Motor control pins to 0
//		PORTB&=~_BV(3)&~_BV(4)&~_BV(5);
		PORTB|=_BV(0)|_BV(2); // BRAKE
		OCR2B=0;
	}else if(r<0)
	{
		PORTB|=_BV(0);
		PORTB&=~_BV(2);
		OCR2B = -r+ZERO;
	}else
	{
		PORTB&=~_BV(0);
		PORTB|=_BV(2);		
		OCR2B = r+ZERO;
	}
}


