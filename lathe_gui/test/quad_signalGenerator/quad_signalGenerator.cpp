/**
 * Quadrature signal generator for Arduino UNO
 * Starts from state 0,0 Waits for serial input and when receives a command then
 * executes a bunch of AB signal ticks.
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <util/delay.h>

// PD6(OC0A) Arduino6, PD5(OC0B) Arduino5
// NCS PB0 Arduino 8

// SPI pins used:
// SCK - Arduino13
// MOSI - Arduino11
// PB2(SS)  - Arduino 10 - must be pulled to GND!


#define PORT_SPI PORTB
#define DDR_SPI DDRB
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5
#define DD_SS 2

#define SS_PIN_IN(PINID) PORT_SPI&=~_BV(PINID); DDR_SPI&=~_BV(PINID)
#define SS_PIN_OUT(PINID) PORT_SPI&=~_BV(PINID); DDR_SPI|=_BV(PINID)
#define SS_PIN_OUT_HIGH(PINID) PORT_SPI|=_BV(PINID); DDR_SPI|=_BV(PINID)

#define SPI_SS_MASTER() SS_PIN_OUT_HIGH(DD_SS); SS_PIN_OUT(DD_MOSI); SS_PIN_OUT(DD_SCK); SS_PIN_IN(DD_MISO)
#define SPI_SS_SLAVE() SS_PIN_IN(DD_SS);         SS_PIN_IN(DD_MOSI);  SS_PIN_IN(DD_SCK); SS_PIN_OUT(DD_MISO)

#define NCS_SENSOR_OFF(index) PORTB|=_BV(0);DDRB|=_BV(0)
#define NCS_SENSOR_ON(index) PORTB&=~_BV(0);DDRB|=_BV(0)

static uint16_t counter;
static uint32_t timeCounter;
//static uint8_t smallCounter;
static bool running=false;

// Debug send a byte by waiting for send possible
static void UART0_Send(uint8_t data)
{
	while((UCSR0A&_BV(UDRE0)) == 0);
	UDR0=data;
	return;
}

static void UART0_Send_Bin(uint8_t data)
{
	for(uint8_t i=0;i<8;++i)
	{
		UART0_Send((data&0b10000000)==0?'0':'1');
		data<<=1;
	}
}


ISR(TIMER1_OVF_vect)
{
	timeCounter++;
}
ISR(TIMER1_COMPA_vect)
{
  if(counter==0)
  {
    // Ready - Stop counter
    TCCR0B=0;
    TCCR0A=0;
    TIMSK0=0;
    // Disable self
    TIMSK1&=~_BV(OCIE1A);
  }
  counter--;
}
void initTimer1()
{
    // set up timer with prescaler = 1, interrupts freq is: 244 Hz
    TCCR1B = 0b001;
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
	bool ovf=(tifr & _BV(TOV1)) && (ctr <32000);
	if(ovf)
	{
		m++;
	}
//	// Div by 8 -> shift left 13 instead of 16
	m<<=16;
	m+=ctr;
	// Returned value is measured in CPU ticks
	return m;
}

static void UART_Init()
{
#define BAUD 9600
#include <util/setbaud.h>
/* Set baud rate */
UBRR0H = UBRRH_VALUE;
UBRR0L = UBRRL_VALUE;

/* Enable transmitter and receiver, disable all other features */
UCSR0A = 0;
UCSR0B = 0
  |(1<<RXEN0)
  // |_BV(RXCIE0)
  |(1<<TXEN0)
  //|(0<<UDRIE0)
  ;
/* Set frame format: 8data, 1stop bit */
UCSR0C = (0<<USBS0)|(3<<UCSZ00);

// TX: PD1
DDRD|=_BV(1);
// RX: PD0
DDRD&=~_BV(0);
PORTD|=_BV(0); // Pullup - why not
}
static uint8_t decodeClockDiv(uint16_t divisor)
{
    switch(divisor)
    {
      case 1: return 0b001;
      case 8: return 0b010;
      case 64: return 0b011;
      case 256: return 0b100;
      case 1024: return 0b101;
      default: 0;
    }
}

uint32_t timeoutAt;

static void timer1_setupTimeout(uint16_t millis)
{
	
	timeoutAt=timeGetTicks()+((uint32_t) millis)*16000;
}
static bool timer1_isTimeout()
{
	uint32_t t=timeGetTicks();
//	UART0_Send_Bin((t>>24)&0xFf);
//	UART0_Send(' ');
//	UART0_Send_Bin((t>>16)&0xFf);
//	UART0_Send('\n');

	int8_t v=(int8_t)((timeoutAt-t)>>24);
	bool qt=v<0;
//	UART0_Send(qt?'T':'N');
	return qt;
}
static void timer1_cancelTimeout()
{
}
static void gui_updateInput(uint8_t sensorIndex, uint32_t data32)
{
	UART0_Send('W');
}

#include "../../gui_atmega328/sensor_readout.cpp"

/**
 * periodDiv2 - half of the full period of the output signal
 * phaseShift - The output of the second signal is shifted by this phase
 * @param n - n full periods are executed
 */
static void startQuads(uint8_t periodDiv2, uint8_t phaseShift, uint16_t clockDivisor, uint32_t n)
{
	uint8_t clockSetup=decodeClockDiv(clockDivisor);
	if(clockSetup==0)
	{
		return;
	}
  // WGM=0b010;  - CTC mode
    // Reset all logic and stop counting
    TCCR0A=0;
    TCCR0B=0;
    TCNT0=1;  // Count from 1 - no match at first start, both output is 0
    TCCR0A|=0b10; // WGM 1-0
    TCCR0A|=0b01010000; // Toggle on compare match for both
    OCR0A=periodDiv2; // Counting turns back at this point.
    OCR0B=phaseShift;
    TIFR0|=_BV(TOV0); // Clear overflow flag if was set
//    TIMSK0=_BV(OCIE0A); // Enable interrupt when half period ends
	//|_BV(TOIE0); // Enable interrupt
    // TCCR0B|=_BV(WGM02); this is 0
    counter=n*2-1;


	uint32_t allClocks=clockDivisor*periodDiv2*2*n;	// This is the length of the whole signal in CPU clocks
	uint32_t fullCycles=allClocks/65536ul;
	uint32_t remaining=allClocks-fullCycles*65536ul;
	TIMSK1|=_BV(OCIE1A);	// Disable compare match interrupt
	TIFR1|=_BV(OCF1A);	// Clear compare match interrupt flag
	cli();
	counter=fullCycles;

	TCCR0B|=clockSetup;	// Launch Output generator clock

	// Launch stop clock
	OCR1A=remaining+TCNT1;	// Stop clock at this time
	TIFR1|=_BV(OCF1A);	// Clear output compare match interrupt flag
	TIMSK1|=_BV(OCIE1A);	// Enable compare match interrupt
	sei();
	running=true;
}

static bool finished()
{
	return TCCR0B==0;
}

static void loop() {
  if( UCSR0A & (1<<RXC0) )
  {
    uint8_t v=UDR0;
    if(finished())
    {
	    switch(v)
	    {
	      case 'a': startQuads(32, 16, 1,   250000ul); break; // T=4us  250.000 periods, 500.000 interrupt per second - 1.000.000 signals per second
	      case 'b': startQuads(64, 32, 1,   125000ul); break; //    250.000 interrupt per second -   500.000 signals per second
	      default: break;
	    }
    }else
    {
      UART0_Send('X');
	UART0_Send_Bin(TCNT0);
    }
  }
	if(finished()&&running)
	{
		running=false;
		UART0_Send('R');
	}

	uint32_t t=timeGetTicks();
/*	#define MODVAL 16000
	t%=MODVAL;
	if(t<MODVAL/2)
	{
		NCS_SENSOR_ON(0);
	}
	else
	{
		NCS_SENSOR_OFF(0);
	}
*/
	sensor_readout(0);
//	UART0_Send('P');
//	_delay_ms(20);
}

int main()
{
	UART_Init();
	initTimer1();
//	PORTB|=_BV(5);
//	DDRB|=_BV(5);

	PORTD&=~_BV(5);
	PORTD&=~_BV(6);
	DDRD|=_BV(5);
	DDRD|=_BV(6);

	SPI_SS_SLAVE();
	sei();
//while(1){UART0_Send(0xf0);}
	while(1){
		loop();
	}
	return 0;
}

