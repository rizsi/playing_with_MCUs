// Receive data from quad counter through custom protocol (1 bit serial)
// Pins: PINB 0 : sensor 1 Arduino 8
// DEBUG:PINB 1 : sensor 1 NChipSelect Arduino 9
//       PINB 2 : sensor 1 timing debug output Arduino 10
// Pins: PIND 4 : sensor 2 Arduino 4

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <receiver.h>
#include <SW_RX_1.h>
#include <SW_RX_2.h>

#define high(value) ((uint8_t)((value>>8)&0xff))
#define low(value) ((uint8_t)(value&0xff))
#define combine16(h,l) (((((uint16_t)h)<<8)&0xff00) | (((uint16_t)l)&0xff))

typedef uint16_t (*fun)();

#define rec()

#define HANDLE_ERR(index) \
if(high(v)!=0) \
	{ \
		return combine16(high(v), index); \
	} 

uint16_t quad_receive(uint8_t index, quad_receiver_t * ret)
{
	fun f;
	uint16_t v;
#ifdef DEBUG_EDGE_START
	DDRB|=_BV(2); // Debug pin output
#endif
	cli();
	switch(index)
	{
	case 0:f=SW_RX_1_receiveByte;
		PORTB&=~1;	// Drive to low
		DDRB|=1;
		_delay_us(10);
		PORTB|=1;	// Pullup input
		DDRB&=~1;
		break;
	case 1:f=SW_RX_2_receiveByte; break;
		PORTD&=~_BV(4);
		DDRD|=_BV(4);
		_delay_us(10);
		PORTD|=_BV(4);
		DDRD&=~_BV(4);
	default:return 0xffff;
	}
	v=f(); HANDLE_ERR(0);
	ret->count_bytes[0]=low(v);
	v=f(); HANDLE_ERR(1);
	ret->count_bytes[1]=low(v);
	v=f(); HANDLE_ERR(2);
	ret->count_bytes[2]=low(v);
	v=f(); HANDLE_ERR(3);
	ret->count_bytes[3]=low(v);
	v=f(); HANDLE_ERR(4);
	ret->status=low(v);
	v=f(); HANDLE_ERR(5);
	ret->zero_bytes[0]=low(v);
	v=f(); HANDLE_ERR(6);
	ret->zero_bytes[1]=low(v);
	v=f(); HANDLE_ERR(7);
	ret->zero_bytes[2]=low(v);
	v=f(); HANDLE_ERR(8);
	ret->zero_bytes[3]=low(v);
	sei();
	return 0;
}


