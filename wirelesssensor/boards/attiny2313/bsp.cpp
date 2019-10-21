#include <bsp.h>


#include <stdlib.h>

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_OVERFLOW_vect)
{
 // nothing here
}


void bsp_init()
{
// All to input/pullup. Except D1 which is the debug serial output which is configured to output
DDRB=0b00000000; PORTB=0b11111111;
DDRA=0b00000000; PORTA=0b11111111;
DDRD=0b00000000| _BV(1); PORTD=0b11111111&~_BV(1);

MCUSR = 0;
wdt_disable();

#define BAUD 9600
#include <util/setbaud.h>
UBRRH = UBRRH_VALUE;
UBRRL = UBRRL_VALUE;
#if USE_2X
UCSRA |= (1 << U2X);
#else
UCSRA &= ~(1 << U2X);
#endif
UCSRB = (1<<TXEN);
// USART.BAUD = (uint16_t)USART0_BAUD_RATE(9600);

// TODO invalid on this hardware
// cbi(ADCSRA,ADEN);  // switch Analog to Digitalconverter OFF

ACSR|=_BV(ACD); // Turn Analog comparator off to spare some power!
// srandom(0); // Random seed - when multiple sensors will be used then this value have to be different for each unit. 500 byte!
// uint32_t v=random(); // This is how a random value must be queried
}


bool bspButton1Pressed()
{
	return 0;
}
/** Clear the pressed state of button1 */
void bspButton1Clear()
{
}

void USART_sendChar(char data)
{
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

void deepSleep(uint8_t wdto_value)
{
//	cli();
//	wdt_reset(); // Counter is zero
		/*First step is Enable Watchdog*/

/*
Macro WDTO_15MS
Macro WDTO_30MS
Macro WDTO_60MS
Macro WDTO_120MS
Macro WDTO_250MS
Macro WDTO_500MS
Macro WDTO_1S
Macro WDTO_2S
Macro WDTO_4S
Macro WDTO_8S
*/
	wdt_enable(wdto_value); /*Watchdog Reset after 1Sec*/

	// Start timed session
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	// Enable WDT interrupt
	WDTCSR |= _BV(WDIE);

/*	if((PINB&_BV(3))==0)
	{
		wdt_disable(); // TODO this is stupid but for the sake of the measurement
		for(int i=0;i<10;++i)
		{
			GREEN_LED_ON(1);
	RED_LED_ON(1);
	_delay_ms(300);
	//deepSleep(500);
	GREEN_LED_ON(0);
	RED_LED_ON(0);
	_delay_ms(300);
		}
	}
*/
	// Choose our preferred sleep mode:
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	// Set sleep enable (SE) bit:
	sleep_enable();
	sei();
	// Put the device to sleep:
	sleep_mode();

	// Upon waking up, sketch continues from this point.
	sleep_disable();
	wdt_disable();
}

void debugDecimal(uint16_t n)
{
	uint8_t ctr=0;
	char num[8];
	while(n>0)
	{
		num[ctr]='0'+(n%10);
		n/=10;
		ctr++;
	}
	if(ctr==0)
	{
		num[0]='0';
		ctr++;
	}
	for(int8_t i=ctr-1;i>=0;--i)
	{
		USART_sendChar(num[i]);
	}
}

void debugBinary(uint8_t n)
{
	for(uint8_t i=0;i<8;++i)
	{
		if(n>=128)
		{
			USART_sendChar('1');
		}else
		{
			USART_sendChar('0');
		}
		n<<=1;
	}
}


void debugString(const char * str)
{
	while(*str!=0)
	{
		USART_sendChar(*str);
		str++;
	}
}


void RADIO_PINS_INIT()
{
	DDRB&=~_BV(6); PORTB|=_BV(6); // data in to input, pullup
	DDRB|=_BV(5); PORTB|=_BV(5); // data out to high
	DDRB|=_BV(7); PORTB&=~_BV(7); // Clock to high
}

uint8_t RADIO_SPI(uint8_t transmit)
{
	uint8_t in=0;
	for(uint8_t i=0;i<8;++i)
	{
		in<<=1;
		if(transmit>=128)
		{
			PORTB|=_BV(5); // data out 1
		}else
		{
			PORTB&=~_BV(5); // data out 0
		}
		PORTB|=_BV(7); // Clock out up
//		_delay_us(30);
		in|=((PINB&_BV(6))==0?0:1); // Data in
		transmit<<=1;
		PORTB&=~_BV(7); // Clock out down
//		_delay_us(30);
	}
	return in;
}

