#include <bsp_platform.h>

__int40_t alma;
uint32_t sensor_readout()
{
	union
	{
		uint8_t data[4];
		uint32_t data32;
	};
	bool ready=false;
	uint8_t byteIndex=0;
	timer1_setupTimeout(10);
	SPI_SS_SLAVE();
	SPCR=0;	// RESET SPI as slave
	SPDR=0; // Send 0s when asked
	SPCR=_BV(SPE)|_BV(DORD);
	NCS_SENSOR_ON(i);  // signal sensor for read
	while(!ready)
	{
		if(timer1_isTimeout())
		{
			ready=true;
		}
		if(SPSR&_BV(SPIF)!=0)
		{
			// Transfer of 1 byte finished
			uint8_t status=SPSR; uint8_t value=SPDR;	// Reset status and read value
			SPDR=0;
			data[byteIndex]=value;
			byteIndex++;
			if(byteIndex==4)
			{
				ready=true;
			}
		}
	}
	timer1_cancelTimeout();
	NCS_SENSOR_OFF(i); // signal sensor for end of read
	_delay_us(500);    // wait little until client releases the line after signalling end of
	SPCR=0;	// RESET SPI hardware
	if(byteIndex==4)
	{
		// data read successfully -> store it!
		gui_updateInput(i, data32);
	}
	return data32;
}

