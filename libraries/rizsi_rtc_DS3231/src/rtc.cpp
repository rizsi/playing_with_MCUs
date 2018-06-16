#include <rtc_DS3231.h>

// RTC implementation on Arduino using DS3231 chip

 When  the  microcontroller  resets,  the  DS3231 I2C
 interface  may  be  placed  into  a  known  state  by  toggling SCL until SDA is observed to be at a high level.


#define DS3231_I2C_ADDRESS_R	0xD1
#define DS3231_I2C_ADDRESS_W	0xD0

rtcState rtc_sim_state;

void rtcInit()
{
rtcState * dst=&rtc_sim_state;
	dst->year=0;
	dst->month=0;
	dst->day=0;
	dst->hour=0;
	dst->minute=0;
	dst->second=0;
}

uint8_t decodeBcd(uint8_t bcd)
{
// TODO
	return data;
}
uint8_t toBcd(uint8_t data)
{
// TODO
	return data;
}

/**
 * @return true means error in RTC communication.
 */
bool rtcRead(rtcState * dst)
{
	twiBeginTransmission(DS3231_I2C_ADDRESS_W);
	twiWrite(0x0); // Register address
	twiEndTransmission();
	twiBeginRead(DS3231_I2C_ADDRESS_R);

	rtc_sim_state.second=decodeBcd(twiRead(0));
	rtc_sim_state.minute=decodeBcd(twiRead(0));
	rtc_sim_state.hour=decodeBcd(twiRead(0));
	rtcReadReg(3);
	rtc_sim_state.day=decodeBcd(twiRead(0));
	uint8_t monthCentury=rtcReadReg(twiRead(0));
	rtc_sim_state.month=decodeBcd(monthCentury&0B01111111);
	monthCentury&=0B10000000;
	rtc_sim_state.year=decodeBcd(rtcReadReg(twiRead(1)))+(monthCentury?2000:2100); // Possible to go to the 2100's :-) This program will outlive me!
	
	twiEndRead();
	
	// Normalize out of range values in case of a mis-initialized RTC
	rtc_sim_state.second%=60;
	rtc_sim_state.minute%=60;
	rtc_sim_state.hour%=24;
	rtc_sim_state.day--;
	rtc_sim_state.day%=31;
	rtc_sim_state.day++;
	rtc_sim_state.month--;
	rtc_sim_state.month%=12;
	rtc_sim_state.month++;
	rtc_sim_state.year-=1900;
	rtc_sim_state.year%=200;
	rtc_sim_state.year+=1900;
	
	memcpy(dst, &rtc_sim_state, sizeof(rtcState));
	return false;
}
void rtcWrite(rtcState * src)
{
	twiBeginTransmission(DS3231_I2C_ADDRESS_W);
	twiWrite(0x0); // Register address

	twiWrite(toBcd(src->second));
	twiWrite(toBcd(src->minute));
	twiWrite(toBcd(src->hour)); // BIT6 will be 0 that selects 24 hour mode
	twiWrite(toBcd(0)); // Day of week is not used
	twiWrite(toBcd(src->day)); // Day of month
	uint8_t century=(src->year/100)%1;
	century<<=7;
	twiWrite(toBcd(src->month)|century); // Month+Century in bit7
	twiWrite(toBcd((uint8_t)(src->year%100)));
    twiEndTransmission();
}



void DS3231::_burstRead()
{
	if (_use_hw)
	{
		// Send start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_W;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = 0;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

		// Read data starting from start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send rep. START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_R;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		for (int i=0; i<7; i++)
		{
			TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);								// Send ACK and clear TWINT to proceed
			while ((TWCR & _BV(TWINT)) == 0) {};									// Wait for TWI to be ready
			_burstArray[i] = TWDR;
		}
		TWCR = _BV(TWEN) | _BV(TWINT);												// Send NACK and clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

		TWCR = _BV(TWEN)| _BV(TWINT) | _BV(TWSTO);									// Send STOP
	}
	else
	{
		_sendStart(DS3231_ADDR_W);
		_waitForAck();
		_writeByte(0);
		_waitForAck();
		_sendStart(DS3231_ADDR_R);
		_waitForAck();

		for (int i=0; i<7; i++)
		{
			_burstArray[i] = _readByte();
			if (i<6)
				_sendAck();
			else
				_sendNack();
		}
		_sendStop();
	}
}

uint8_t DS3231::_readRegister(uint8_t reg)
{
	uint8_t	readValue=0;

	if (_use_hw)
	{
		// Send start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_W;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = reg;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

		// Read data starting from start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send rep. START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_R;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Send ACK and clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		readValue = TWDR;
		TWCR = _BV(TWEN) | _BV(TWINT);												// Send NACK and clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

		TWCR = _BV(TWEN)| _BV(TWINT) | _BV(TWSTO);									// Send STOP
	}
	else
	{
		_sendStart(DS3231_ADDR_W);
		_waitForAck();
		_writeByte(reg);
		_waitForAck();
		_sendStart(DS3231_ADDR_R);
		_waitForAck();
		readValue = _readByte();
		_sendNack();
		_sendStop();
	}
	return readValue;
}

void DS3231::_writeRegister(uint8_t reg, uint8_t value)
{
	if (_use_hw)
	{
		// Send start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_W;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = reg;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = value;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

		TWCR = _BV(TWEN)| _BV(TWINT) | _BV(TWSTO);									// Send STOP
	}
	else
	{
		_sendStart(DS3231_ADDR_W);
		_waitForAck();
		_writeByte(reg);
		_waitForAck();
		_writeByte(value);
		_waitForAck();
		_sendStop();
	}
}

