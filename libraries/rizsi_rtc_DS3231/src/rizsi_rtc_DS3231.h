typedef struct
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} rtcState;

void rtcInit();
/**
 * @return true means error in RTC communication.
 */
bool rtcRead(rtcState * dst);


bool rtcWrite(rtcState * src);
/**
 * Get the low bits of a counter that can be used as a quasi random number.
 */
uint8_t rtcGetTimeLowBits();