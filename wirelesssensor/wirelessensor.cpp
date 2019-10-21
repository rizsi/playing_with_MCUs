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
	uint16_t voltage;	// Voltage of the battery - read while temperature readout is working
} message;
//static uint8_t message[32];	// Message to send
//
//static uint16_t voltage;	// Voltage of the battery - read while the radio is working or while a LED is working: to measure voltage under load
//static uint16_t temperature;	

static bool isROMCodeEmpty();

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
	radioSessionBegin();
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
	radioSessionEnd();
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
/*
	bsp_init();
	radioPinsInit();
	while(1)
	{
//		radioReadData();
		radioFifoStatus();
		_delay_ms(3);
	}
}
*/
/*
	// See waveforms on scope
	bsp_init();
	radioPinsInit();
	while(1)
	{
		radioFifoStatus();
		_delay_ms(3);
	}
}
*/
//void a()
//{
	// Initialize all hardware (pins, etc)
	bsp_init();
	radioPinsInit();
	uint8_t ctr=0;
	deepSleepInit(); // Initial sleep - 1 second - why not
	radioSetup(RADIO_MODE_SLEEP, 32);
	while(1)
	{
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
		message.voltage=bspGetVoltage();
#ifdef DEBUG
		USART_sendChar('Y');
		debugDecimal(message.temperature);
		USART_sendChar('Y');
		USART_sendChar('\n');
#endif
		sendRadio();
		if(bspButton1Pressed())
		{
			bspButton1Clear();
//			blinkout();
		}
		blinkout();
		if(!bspButton1Pressed())
		{
			deepSleepPeriod(); // 1 minute sleep
		}
	}
}

