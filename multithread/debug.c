/* Debug UART */
#define F_CPU 16000000
#define BAUD 9600
#include <avr/io.h>

#include <util/setbaud.h>

void init_uart()
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);// | _BV(RXCIE0);   /* Enable RX and TX,  receive interrupt */
}

void sendByte(uint8_t data)
{
	while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
       UDR0 = data;
}
void sendNumber(uint32_t number)
{
	uint8_t chars[16];
	int i=0;
	while(number>0)
	{
		chars[i]=number%10+'0';
		number/=10;
		i++;
	}
	if(i==0)
	{
		chars[i]='0';
		i++;	
	}
	for(int j=i-1;j>=0;--j)
	{
		sendByte(chars[j]);
	}
}
uint8_t hexChar(uint8_t num)
{
	if(num<10)
		return num+'0';
	else
		return num-10+'A';
}
void sendHex(uint32_t number)
{
	uint8_t chars[16];
	int i=0;
	while(number>0)
	{
		chars[i]=hexChar(number%16);
		number/=16;
		i++;
	}
	while(i<2)
	{
		chars[i]='0';
		i++;	
	}
	for(int j=i-1;j>=0;--j)
	{
		sendByte(chars[j]);
	}
}
void sendStr(const char * s)
{
	while((*s)!=0)
	{
		sendByte(*s);
		s++;
	}
}
void dumpStack(uint16_t currentStackPointer, uint16_t nByte)
{
	nByte+=10;
	sendNumber(currentStackPointer);
	sendByte(':');
	uint8_t * ptr=(uint8_t *) currentStackPointer;
	for(int i=nByte;i>0;--i)
	{
		sendHex(*(ptr+i));
		sendByte(',');
	}
}

