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
// PB2(SS)  - Arduino 8 - must be pulled to NCS through a resistor!


#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5
#define DD_SS 2


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

static void UART0_Send_uint32(uint32_t v)
{
	int8_t out[16];
	int8_t i=0;
	do
	{
		out[i]='0'+v%10;
		v/=10;
		i++;
	}while(v>0&&i<16);
	for(i--;i>=0;--i)
	{
		UART0_Send(out[i]);
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
#define BAUD 19200
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
static void doFastQuads(uint32_t k);
static void doFastQuadsDown(uint32_t k);



uint16_t timeoutAt;

static void timer1_setupTimeout(uint16_t millis)
{
	timeoutAt=TCNT1; // Timeout is 488Hz ~ 2ms
}
static bool timer1_isTimeout()
{
	uint16_t t=TCNT1;
	return (t-timeoutAt)>32000;
}
static void timer1_cancelTimeout()
{
}
uint32_t prevv=0;
static void doQuads(uint32_t n, int8_t dir);
static void sensor_readout_callback(uint8_t sensorIndex, uint32_t data32, uint8_t err, uint32_t zero)
{
	union
	{
		uint8_t data[4];
		uint32_t data32b;
	};
	data32b=data32;
//		UART0_Send('C');
//		UART0_Send_uint32(data32);
//		UART0_Send('\n');

	if(data32!=prevv)
	{
		prevv=data32;
		UART0_Send('C');
		for(int8_t i=3;i>=0;--i)
		{
			UART0_Send_Bin(data[i]);
			UART0_Send(' ');
		}
		UART0_Send_Bin(err);
		UART0_Send(' ');
		UART0_Send_uint32(data32);
		UART0_Send('\n');
	}
/*	for(uint8_t i=0;i<4;++i)
	{
		UART0_Send_Bin(data[i]);
		UART0_Send(' ');
	}*/
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
		UART0_Send('c');
		UART0_Send_Bin(clockSetup);
		UART0_Send('\n');
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

static bool UART_hasInput()
{
	return (UCSR0A & (1<<RXC0))!=0;
}

static void loop() {
  if( UART_hasInput() )
  {
    uint8_t v=UDR0;
    if(finished())
    {
      UART0_Send('Y');
      UART0_Send(v);
	    switch(v)
	    {
	      case 'a': doQuads(1ul, 1); break; //    1 full cycle
	      case 'b': doQuads(2ul, 1); break; //    1 full cycle
	      case 'c': doQuads(4ul, 1); break; //    1 full cycle
	      case 'd': doQuads(8ul, 1); break; //    1 full cycle
	      case 'e': doQuads(16ul, 1); break; //    1 full cycle
	      case 'f': doQuads(32ul, 1); break; //    1 full cycle
	      case 'g': doQuads(64ul, 1); break; //    1 full cycle
	      case 'h': doQuads(128ul, 1); break; //    1 full cycle
	      case 'i': doQuads(256ul, 1); break; //    1 full cycle
	      case 'j': doQuads(512ul, 1); break;
	      case 'k': doQuads(1024ul, 1); break;
	      case 'l': doQuads(2048ul, 1); break;
	      case 'm': doQuads(4096ul, 1); break;
	      case 'n': doQuads(8192ul, 1); break;
	      case 'o': doQuads(16384ul, 1); break;
	      case 'p': doQuads(32768ul, 1); break;
	      case 'q': doQuads(1000000ul, 1); break;
	      case 'r': doQuads(10000000ul, 1); break;
	      case 's':     doFastQuads(100000ul); break;
	      case 'S': doFastQuadsDown(100000ul); break;
	      case 't':     doFastQuads(1000000ul); break;
	      case 'T': doFastQuadsDown(1000000ul); break;

	      case 'A': doQuads(1ul, -1); break;
	      case 'B': doQuads(2ul, -1); break;
	      case 'C': doQuads(4ul, -1); break;
	      case 'D': doQuads(8ul, -1); break;
	      case 'E': doQuads(16ul, -1); break;
	      case 'F': doQuads(32ul, -1); break;
	      case 'G': doQuads(64ul, -1); break;
	      case 'H': doQuads(128ul, -1); break;
	      case 'I': doQuads(256ul, -1); break;
	      case 'J': doQuads(512ul, -1); break;
	      case 'K': doQuads(1024ul, -1); break;
	      case 'L': doQuads(2048ul, -1); break;
	      case 'M': doQuads(4096ul, -1); break;
	      case 'N': doQuads(8192ul, -1); break;
	      case 'O': doQuads(16384ul, -1); break;
	      case 'P': doQuads(32768ul, -1); break;
	      case 'Q': doQuads(1000000ul, -1); break;
	      case 'R': doQuads(10000000ul, -1); break;

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
	uint16_t err=sensor_readout(0);
	if(err!=0)
	{
		UART0_Send('x');
		UART0_Send_uint32(err);
		UART0_Send('\n');
	}else
	{
//		UART0_Send('o');
	}
}

static inline void setState(uint8_t st)
{
	switch(st)
	{
		case 0: PORTD&=~_BV(5);PORTD&=~_BV(6);break;
		case 1: PORTD|=_BV(5);PORTD&=~_BV(6);break;
		case 2: PORTD|=_BV(5);PORTD|=_BV(6);break;
		case 3: PORTD&=~_BV(5);PORTD|=_BV(6);break;
	}
}

static uint8_t state=0;
static void doQuads(uint32_t n, int8_t dir)
{
	for(uint32_t i=0;i<n;++i)
	{
		state+=dir; state%=4;
		setState(state);
	}
}

#define BITTIME() asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop");\
	asm volatile("nop")

void doFastQuads(uint32_t k)
{
	// Adjust bittime for preferred frequency and signal profile
	for(uint32_t x=k;x>0;--x)
	{
		PORTD|=_BV(5);PORTD&=~_BV(6);
		BITTIME();
		PORTD|=_BV(5);PORTD|=_BV(6);
		BITTIME();
		PORTD&=~_BV(5);PORTD|=_BV(6);
		BITTIME();
		PORTD&=~_BV(5);PORTD&=~_BV(6);
		BITTIME();
	}
}

void doFastQuadsDown(uint32_t k)
{
	// Adjust bittime for preferred frequency and signal profile
	for(uint32_t x=k;x>0;--x)
	{
		PORTD&=~_BV(5);PORTD|=_BV(6);
		BITTIME();
		PORTD|=_BV(5);PORTD|=_BV(6);
		BITTIME();
		PORTD|=_BV(5);PORTD&=~_BV(6);
		BITTIME();
		PORTD&=~_BV(5);PORTD&=~_BV(6);
		BITTIME();
	}
}


int main()
{
	UART_Init();
	initTimer1();

	PORTD&=~_BV(5);
	PORTD&=~_BV(6);
	DDRD|=_BV(5);
	DDRD|=_BV(6);

	sei();
	while(1){
		loop();
	}
	return 0;
}

