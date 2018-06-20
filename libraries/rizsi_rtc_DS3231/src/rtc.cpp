#include <Arduino.h>
#include <rizsi_rtc_DS3231.h>
#include <rizsi_TWI.h>

// RTC implementation on Arduino using DS3231 chip

// From the doc this is missing:
// When  the  microcontroller  resets,  the  DS3231 I2C
// interface  may  be  placed  into  a  known  state  by  toggling SCL until SDA is observed to be at a high level.


#define DS3231_I2C_ADDRESS 0B01101000
//#define DS3231_I2C_ADDRESS_R	0xD1
//#define DS3231_I2C_ADDRESS_W	0xD0

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
	twiInit();
}

uint8_t decodeBcd(uint8_t bcd)
{
	return (bcd>>4)*10+(bcd&0B00001111);
}
uint8_t toBcd(uint8_t data)
{
	uint8_t lo=data%10;
	uint8_t hi=data/10;
	return lo|(hi<<4);
}

/**
 * @return true means error in RTC communication.
 */
bool rtcRead(rtcState * dst)
{
	twiBeginTransmission(DS3231_I2C_ADDRESS);
	twiWrite(0x0); // Register address
	twiEndTransmission();
	twiBeginRead(DS3231_I2C_ADDRESS);

	rtc_sim_state.second=decodeBcd(twiRead(0));
	rtc_sim_state.minute=decodeBcd(twiRead(0));
	rtc_sim_state.hour=decodeBcd(twiRead(0));
	twiRead(0); // Daw of week not interested
	rtc_sim_state.day=decodeBcd(twiRead(0));
	uint8_t monthCentury=decodeBcd(twiRead(0));
	rtc_sim_state.month=decodeBcd(monthCentury&0B01111111);
	monthCentury&=0B10000000;
	rtc_sim_state.year=decodeBcd(twiRead(1))+(monthCentury?2100:2000); // Possible to go to the 2100's :-) This program will outlive me!
	
	twiEndTransmission();
	
	/*
	Serial.println(rtc_sim_state.year);
	Serial.println(rtc_sim_state.month);
	Serial.println(rtc_sim_state.day);
	Serial.println(rtc_sim_state.hour);
	Serial.println(rtc_sim_state.minute);
	Serial.println(rtc_sim_state.second);
	*/
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
	rtc_sim_state.year-=2000;
	rtc_sim_state.year%=200;
	rtc_sim_state.year+=2000;
	
	memcpy(dst, &rtc_sim_state, sizeof(rtcState));
	return false;
}
bool rtcWrite(rtcState * src)
{
	twiBeginTransmission(DS3231_I2C_ADDRESS);
	twiWrite(0x0); // Register address

	twiWrite(toBcd(src->second));
	twiWrite(toBcd(src->minute));
	twiWrite(toBcd(src->hour)); // BIT6 will be 0 that selects 24 hour mode
	twiWrite(toBcd(0)); // Day of week is not used
	twiWrite(toBcd(src->day)); // Day of month
	uint8_t century=(src->year/100)%2;
	century<<=7;
	twiWrite(toBcd(src->month)|century); // Month+Century in bit7
	twiWrite(toBcd((uint8_t)(src->year%100)));
	twiEndTransmission();
	return false;
}
