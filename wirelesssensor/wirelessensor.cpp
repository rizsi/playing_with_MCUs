// Wireless sensor

#include <bsp.h>

#include <inttypes.h>
#include <stdbool.h>

#include <onewire.h>
#include <nRF24L01_radio.h>

#define low(x)   ((x) & 0xFF)
#define high(x)   (((x)>>8) & 0xFF)


static struct  __attribute__ ((packed))
{
	uint8_t tempSensorIdentifier[8];	// 0-8: Globally unique identifier of the temperature sensor - can be acquired using the one wire protocol
	uint16_t temperature;	// Temperature reading from the temperature sensor
	uint16_t voltage;	// Voltage of the battery - read while the radio is working or while a LED is working: to measure voltage under load
} message;
//static uint8_t message[32];	// Message to send
//
//static uint16_t voltage;	// Voltage of the battery - read while the radio is working or while a LED is working: to measure voltage under load
//static uint16_t temperature;	

static bool isROMCodeEmpty();


/**
 * Move all peripherials to low power.
 * Turn ADC off
 */
static void lowPower()
{
}

/**
 * Blink the LED to show we are alive and also a status of the battery
 */
static void blinkout()
{
//voltage>VOLTAGE_LIMIT
	if(message.temperature!=0)
	{
		GREEN_LED_ON(1);
	}else
	{
		RED_LED_ON(1);
	}
	GREEN_LED_ON(1);
	RED_LED_ON(1);
	_delay_ms(100);
	//deepSleep(500);
	GREEN_LED_ON(0);
	RED_LED_ON(0);
}
/**
 * Send values on radio. Send 3 times with random in-between time so that package collision has a low chance.
 * Listening to reply is not useful because that uses almost the same power and at the end we can't do else than re-sending the message.
 *
 * Also measure battery voltage while sending!
 */
static void sendRadio()
{
	if(isROMCodeEmpty())
	{
		USART_sendChar('X');
	}else
	{
		USART_sendChar('T');
	}
	debugDecimal(message.temperature);
	USART_sendChar('\n');
	radioSend((uint8_t *)&message, 32, RADIO_MODE_SLEEP);
	radioLoopUntilSent();
	USART_sendChar('R');
}

/**
 * clock based random number generator set up:
 * Count a fast clock with hardware timer/counter
 * use Watchdog overflow to read this counter - because they are different clocks the value will be random
 * Sleep mode of "Idle" can be used so that the clock is not stopped.
 */
static void setupClockbasedRandom()
{
}
static bool isROMCodeEmpty()
{
	for(uint8_t i=0;i<8;++i)
	{
		if(message.tempSensorIdentifier[i]!=0)
		{
			return false;
		}
	}
	return true;
}
void radioReceiveCallback(uint8_t * data)
{
	// Nothing to do: this is a send only node
}

__attribute__((OS_main))
int main ()
{
	uint8_t ctr=0;
	// Initialize all hardware (pins, etc)
	bsp_init();
	radioPinsInit();
	lowPower();
	deepSleepInit(); // Initial sleep - 1 second - why not
/*
	while(1)
	{
		uint16_t status=radioFifoStatus();
//		uint8_t status=radioReadStatus();
		debugBinary(high(status));
		USART_sendChar(' ');
		debugBinary(low(status));
		USART_sendChar('\n');
	}
*/
	radioSetup(RADIO_MODE_SLEEP, 32);
	while(1)
	{
		setupClockbasedRandom();
		OW_TEMP_POWER(1);
		while(isROMCodeEmpty()&& ctr<3)
		{
			owReadROMAddress(message.tempSensorIdentifier);
			ctr++;
		}
#ifdef DEBUG
		for(uint8_t i=0;i<8;++i)
		{
			debugDecimal(message.tempSensorIdentifier[i]);
			USART_sendChar(' ');
		}
#endif
		owInitialize();
		message.temperature=owReadTemp();
		OW_TEMP_POWER(0);
#ifdef DEBUG
		USART_sendChar('Y');
		debugDecimal(message.temperature);
		USART_sendChar('Y');
		USART_sendChar('\n');
#endif
		sendRadio();
		blinkout();
		lowPower();
		deepSleepPeriod(); // 1 minute sleep
	}
}

