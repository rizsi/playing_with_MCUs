// Bitbang UART output 1 start and 2 stop bit
#include <bsp.h>

// A little less than 104 because we also do things that add to the wait time
#define BITTIME 102

void bitbang_uart_send(uint8_t c)
{
	BITBANG_UART_OUT_LOW();
	_delay_us(BITTIME);
	for(uint8_t i=0;i<8;++i)
	{
		if((c&1)!=0)
		{
			BITBANG_UART_OUT_HIGH();
		}else
		{
			BITBANG_UART_OUT_LOW();
		}
		c>>=1;
		_delay_us(BITTIME);
	}
	BITBANG_UART_OUT_HIGH();
	_delay_us(BITTIME);
	_delay_us(BITTIME);
}

