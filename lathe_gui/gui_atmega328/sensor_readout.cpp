

/**
 * Read out Quad sensor counter value.
 * If readout happens without error gui_updateInput is called with the value as parameter.
 * @return true means read out happend without problem.
 */
bool sensor_readout(uint8_t sensorIndex)
{
	union
	{
		uint8_t data[5];	// 4 data and 1 byte signaling of error
		uint32_t data32;
	};
	bool ready=false;
	uint8_t byteIndex=0;
	timer1_setupTimeout(3);
	SPI_SS_SLAVE();
	SPCR=0;	// RESET SPI as slave
	SPDR=0; // Send 0s when asked
	{uint8_t status=SPSR; uint8_t value=SPDR;}	// Reset status and read value
	SPCR=_BV(SPE)|_BV(DORD)|_BV(CPOL);
	NCS_SENSOR_ON(sensorIndex);  // signal sensor for read
	while(!ready)
	{
		if(timer1_isTimeout())
		{
//			UART0_Send_Bin(PINB);
//			UART0_Send('T');
//			UART0_Send('\n');
			ready=true;
		}
		if(( (SPSR&_BV(SPIF))!=0))
		{
			// Transfer of 1 byte finished
			uint8_t status=SPSR; uint8_t value=SPDR;	// Reset status and read value
			SPDR=0;
			data[byteIndex]=value;
			byteIndex++;
			if(byteIndex==5)
			{
				ready=true;
			}
		}
		if((SPSR&_BV(WCOL))!=0)
		{
			uint8_t status=SPSR; uint8_t value=SPDR;	// Reset status and read value
		}
	}
	timer1_cancelTimeout();
	NCS_SENSOR_OFF(sensorIndex); // signal sensor for end of read
	_delay_us(500);    // wait little until client releases the line after signalling end of
	_delay_ms(3);    // wait little until client releases the line after signalling end of
	SPCR=0;	// RESET SPI hardware
	if(byteIndex==5)
	{
		// data read successfully -> store it!
		gui_updateInput(sensorIndex, data32, data[4]);
		return true;
	}
	return false;
//	for(uint8_t i=0;i<byteIndex;++i)
//	{
//		UART0_Send_Bin(data[i]);
//		UART0_Send(' ');
//	}
//	UART0_Send('\n');
}

