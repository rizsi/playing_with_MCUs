#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <util/delay.h>

// Debug send a byte by waiting for send possible
void UART0_Send(uint8_t data)
{
	while((UCSR0A&_BV(UDRE0)) == 0);
	UDR0=data;
	return;
}

void UART0_Send_Bin(uint8_t data)
{
	for(uint8_t i=0;i<8;++i)
	{
		UART0_Send((data&0b10000000)==0?'0':'1');
		data<<=1;
	}
}

void UART0_Send_uint32(uint32_t v)
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

void UART0_Init()
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

