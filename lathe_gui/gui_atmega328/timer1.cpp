#include <bsp.h>
#include <bsp_platform.h>

static uint32_t timeCounter=0;
static bool timeout=false;
ISR(TIMER1_COMPA_vect)
{
	timeout=true;
}

/**
 * @param must be smaller than 64000/8=8000; Must be at least a few millisecs so timeout does not happen while setting it up.
 */
void timer1_setupTimeout(uint16_t timeoutMillis)
{
	cli();
	timeout=false;
	OCR1A=TCNT1+timeoutMillis*8;
	TIFR1|=_BV(OCF1A); // Clear interrupt flag!
	TIMSK1|=_BV(OCIE1A); // Enable Compare match interrupt
	sei();
}
bool timer1_isTimeout()
{
	return timeout;
}
void timer1_cancelTimeout()
{
	TIMSK1&=~_BV(OCIE1A); // Disable Compare match interrupt
}

ISR(TIMER1_OVF_vect)
{
	timeCounter++;
}
void initTimer1()
{
    // set up timer with prescaler = 1024, TCNT1 freq is: 7812 Hz
    TCCR1B |= 0b101;
    // initialize counter
    TCNT1 = 0;
    // enable overflow interrupt
    TIMSK1 |= (1 << TOIE1);
    timeCounter=0;
    // enable global interrupts - must be done by caller
}
static uint32_t timeGetTicks()
{
	uint32_t m;
	uint16_t ctr;
	uint8_t tifr;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		m = timeCounter;
		ctr=TCNT1;
		tifr=TIFR1;
	}
	bool ovf=(tifr & _BV(TOV1)) && ((ctr&0b1000000000000000)==0);
	if(ovf)
	{
		m++;
	}
	// Div by 8 -> shift left 13 instead of 16
	m<<=13;
	ctr>>=3;
	m+=ctr;
	// Returned value is measured in about 0.976 millis which is exact enough for our goals.
	return m;
}
uint32_t timer1_GetCycles()
{
	uint32_t m;
	uint16_t ctr;
	uint8_t tifr;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		m = timeCounter;
		ctr=TCNT1;
		tifr=TIFR1;
	}
	bool ovf=(tifr & _BV(TOV1)) && ((ctr&0b1000000000000000)==0);
	if(ovf)
	{
		m++;
	}
	// Div by 8 -> shift left 13 instead of 16
	m<<=16;
	m+=ctr;
	// Returned value is measured in raw cycles.
	return m;
}

uint32_t getCurrentTimeMillis()
{
	return timeGetTicks();
}

