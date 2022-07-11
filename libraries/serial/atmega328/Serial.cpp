/** Serial interface implementation based on UART0 */

#include <Serial.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define SERIAL_BUFFER_SIZE 250

static uint8_t rx_buffer[SERIAL_BUFFER_SIZE];
static volatile uint8_t rx_read=0, rx_write=0;
static uint8_t tx_buffer[SERIAL_BUFFER_SIZE];
// offset within the buffer. Equal means empty - thus 1 byte can not be used in the buffer.
static volatile uint8_t tx_read=0, tx_write=0;
static volatile bool tx_en=0;
static uint16_t receiveCounter=0;

ISR(USART_RX_vect)
{
	receiveCounter++;
	uint8_t rx_write_inc=rx_write+1;
	if(rx_write_inc>=SERIAL_BUFFER_SIZE)
	{
		rx_write_inc=0;
	}
	if(rx_write_inc!=rx_read)
	{
		rx_buffer[rx_write]=UDR0;
		rx_write=rx_write_inc;
	} else
	{
		// TODO signal overflow
	}
}
ISR(USART_UDRE_vect)
{
	if(tx_read!=tx_write)
	{
		UDR0=tx_buffer[tx_read];
		tx_read++;
		if(tx_read>=SERIAL_BUFFER_SIZE) tx_read=0;
	}else
	{
		UCSR0B&=~_BV(UDRIE0);	// No more data - disable transmit buffer empty interrupt
	}
}

void Serial::begin(uint32_t baud)
{
	rx_read=0;
	rx_write=0;
	tx_read=0;
	tx_write=0;
	tx_en=1;
	UBRR0=(uint16_t)((((uint32_t)F_CPU)/16/baud)-1);

/* Enable transmitter and receiver, disable all other features */
UCSR0A = 0;
UCSR0B = 0
  |(1<<RXEN0)
  |_BV(RXCIE0)
  |(1<<TXEN0)
  ;
/* Set frame format: 8data, 1stop bit */
UCSR0C = (0<<USBS0)|(3<<UCSZ00);
// TX: PD1
DDRD|=_BV(1);
// RX: PD0
DDRD&=~_BV(0);
PORTD|=_BV(0); // Pullup - why not

}
void Serial::write(uint8_t byte)
{
	while(tx_en && availableForWrite()<1); 	// Wait until buffer has free space
// 		PINC|=1;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if(UCSR0B&_BV(UDRIE0))
		{
			// Interrupt enable means that transmit is going on. Enqueue data
			tx_buffer[tx_write]=byte;
			uint8_t next=tx_write+1;
			if(next>=SERIAL_BUFFER_SIZE) next=0;
			tx_write=next;
		}
		else
		{
			// Interrupt not enable means that transmit is not going on. Add data to UDR directly and enable interrupt
			UDR0=byte;
			UCSR0B|=_BV(UDRIE0);
		}
	}
//while (!( UCSR0A & (1<<UDRE0))); /* Wait for empty transmit buffer*/
//          UDR0 = byte;            /* Put data into buffer, sends the data */

}
void Serial::writeString(const char * str)
{
	while(*str!=0)
	{
		write(*str);
		str++;
	}
}
uint8_t Serial:: writeNumber(uint32_t v)
{
	int8_t out[16];
	int8_t i=0;
	uint8_t n=0;
	do
	{
		out[i]='0'+v%10;
		v/=10;
		i++;
	}while(v>0&&i<16);
	n=i;
	for(i--;i>=0;--i)
	{
		write(out[i]);
	}
	return n;
}

void Serial::writeBin(uint8_t data)
{
	for(uint8_t i=0;i<8;++i)
	{
		write((data&0b10000000)==0?'0':'1');
		data<<=1;
	}
}


int Serial::available()
{
	uint8_t rx_length=rx_write-rx_read;
	if(rx_length>=SERIAL_BUFFER_SIZE) rx_length+=SERIAL_BUFFER_SIZE;	// handle underflow
	return rx_length;
}
int Serial::availableForWrite()
{
	uint8_t tx_length=tx_write-tx_read;
	if(tx_length>=SERIAL_BUFFER_SIZE) tx_length+=SERIAL_BUFFER_SIZE;	// handle underflow
	return SERIAL_BUFFER_SIZE-1-tx_length;
}
uint16_t Serial::getReceiveCounter()
{
	return receiveCounter;
}
int Serial::peek(uint8_t offset)
{
	if(offset<available())
	{
		offset+=rx_read;
		if(offset>=SERIAL_BUFFER_SIZE)
		{
			offset-=SERIAL_BUFFER_SIZE;
		}
		return rx_buffer[offset];
	}
	return 0;
}
int Serial::read()
{
	while(available()==0);	// Wait until there is data available
	uint8_t ret=rx_buffer[rx_read];
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		rx_read++;
		if(rx_read>=SERIAL_BUFFER_SIZE)
		{
			rx_read=0;
		}
	}
	return ret;
}
void Serial::flushRead()
{
	return;
}
