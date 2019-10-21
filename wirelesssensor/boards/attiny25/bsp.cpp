#include <bsp.h>


#include <stdlib.h>

static uint8_t bspState=0;

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect)
{
 // nothing here
}


void bsp_init()
{
bspState=0;
// All to input/pullup.
DDRB=0b00000000; PORTB=0b11111111;

MCUSR = 0;
wdt_disable();

ACSR|=_BV(ACD); // Turn Analog comparator off to spare some power!
// srandom(0); // Random seed - when multiple sensors will be used then this value have to be different for each unit. 500 byte!
// uint32_t v=random(); // This is how a random value must be queried
}

bool bspButton1Pressed()
{
	return bspState!=0;
}
/** Clear the pressed state of button1 */
void bspButton1Clear()
{
	bspState=0;
}

void deepSleepPeriod()
{
//#define deepSleepPeriod() {for(uint8_t ctr=0;ctr<1;++ctr){deepSleep(WDTO_8S);}deepSleep(WDTO_4S);}
	// TODO enable pin change interrupt and check button pin
	 deepSleep(WDTO_1S);
	// TODO disable pin change interrupt and check button pin
}

void deepSleepConversionTime()
{
	// TODO readout of batt voltage
 deepSleep(WDTO_1S);
}

static void initADC()
{
  /* this function initialises the ADC 

        ADC Prescaler Notes:
	--------------------

	   ADC Prescaler needs to be set so that the ADC input frequency is between 50 - 200kHz.
  
           For more information, see table 17.5 "ADC Prescaler Selections" in 
           chapter 17.13.2 "ADCSRA – ADC Control and Status Register A"
          (pages 140 and 141 on the complete ATtiny25/45/85 datasheet, Rev. 2586M–AVR–07/10)

           Valid prescaler values for various clock speeds
	
	     Clock   Available prescaler values
           ---------------------------------------
             1 MHz   8 (125kHz), 16 (62.5kHz)
             4 MHz   32 (125kHz), 64 (62.5kHz)
             8 MHz   64 (125kHz), 128 (62.5kHz)
            16 MHz   128 (125kHz)

           Below example set prescaler to 128 for mcu running at 8MHz
           (check the datasheet for the proper bit values to set the prescaler)
  */

  // 8-bit resolution
  // set ADLAR to 1 to enable the Left-shift result (only bits ADC9..ADC2 are available)
  // then, only reading ADCH is sufficient for 8-bit results (256 values)

  ADMUX =
            (1 << ADLAR) |     // left shift result - the high bits are used to represent the read out value
            (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
            (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
            (1 << MUX3)  |     // use VBG (internal reference) for input (PB4)
// After switching to internal voltage reference the ADC requires a settling time of 1ms before measurements are sta-
// ble. Conversions starting before this may not be reliable. The ADC must be enabled during the settling time.
            (1 << MUX2)  |
            (0 << MUX1)  |
            (0 << MUX0);

// VBG Bandgap reference voltage is 1.0-1.2V (nominal 1.1V). Its value is stable within a chip so a single calibration is enough.
// How to calibrate: The program sends the raw read out value to the radio base. The calibration is done on the server by measuring the
// voltage when the sensor is installed and storing the measured value/ADC readout.

  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (0 << ADPS2) |     // set ADC clock prescaler to 8, (011) -> 125 kHz clock
            (1 << ADPS1) |
            (1 << ADPS0);
	_delay_ms(1); // Settling time after enabling internal reference voltage to measure
}

uint16_t bspGetVoltage()
{
	while (ADCSRA & (1 << ADSC) ); // wait till first conversion is complete (that value is dropped)
	ADCSRA |= (1 << ADSC);         // start ADC measurement
	while (ADCSRA & (1 << ADSC) ); // wait till conversion complete
	uint8_t adc_lobyte=ADCL;
	uint8_t adc_hibyte=ADCH;
	uint16_t ret=(((uint16_t)adc_hibyte)<<8)|adc_lobyte;
	ADCSRA = 0;     // Disable ADC
	ACSR|=_BV(ACD); // Turn Analog comparator off to spare some power!
	return ret;
}

void deepSleep(uint8_t wdto_value)
{
	wdt_enable(wdto_value); /*Watchdog Reset after configured timeout value */

	// Start timed session
	WDTCR |= (1<<WDCE) | (1<<WDE);
	// Enable WDT interrupt
	WDTCR |= _BV(WDIE);

/*	if((PINB&_BV(3))==0)
	{
		wdt_disable(); // TODO this is stupid but for the sake of the measurement
		for(int i=0;i<10;++i)
		{
			GREEN_LED_ON(1);
	RED_LED_ON(1);
	_delay_ms(300);
	//deepSleep(500);
	GREEN_LED_ON(0);
	RED_LED_ON(0);
	_delay_ms(300);
		}
	}
*/
	// Choose our preferred sleep mode:
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	// Set sleep enable (SE) bit:
	sleep_enable();
	sei();
	// Put the device to sleep:
	sleep_mode();

	// Upon waking up, sketch continues from this point.
	sleep_disable();
	wdt_disable();
}

void debugDecimal(uint16_t n)
{
	uint8_t ctr=0;
	char num[8];
	while(n>0)
	{
		num[ctr]='0'+(n%10);
		n/=10;
		ctr++;
	}
	if(ctr==0)
	{
		num[0]='0';
		ctr++;
	}
	for(int8_t i=ctr-1;i>=0;--i)
	{
		USART_sendChar(num[i]);
	}
}

void debugBinary(uint8_t n)
{
	for(uint8_t i=0;i<8;++i)
	{
		if(n>=128)
		{
			USART_sendChar('1');
		}else
		{
			USART_sendChar('0');
		}
		n<<=1;
	}
}


void debugString(const char * str)
{
	while(*str!=0)
	{
		USART_sendChar(*str);
		str++;
	}
}


void RADIO_PINS_INIT()
{
	DDRB&=~_BV(1); PORTB|=_BV(1); // data input to input with pullup
//	DDRB|=_BV(0); PORTB|=_BV(0); // data out to high
	DDRB|=_BV(2); PORTB&=~_BV(2); // Clock to low
}
void RADIO_BEGIN()
{
//	DDRB|=_BV(2);
	PORTB&=~_BV(4);DDRB|=_BV(4); // NCS to low -> active
}
void RADIO_END()
{
	PORTB|=_BV(4);DDRB|=_BV(4); // NCS to high -> inactive
	PORTB|=_BV(1); // Pullup on data line to force to a definite value
//	PORTB|=_BV(2); // Clock to high
}

uint8_t RADIO_SPI(uint8_t transmit)
{
	uint8_t in=0;
	for(uint8_t i=0;i<8;++i)
	{
		in<<=1;
		if(transmit>=128)
		{
			PORTB|=_BV(1); // data out 1
//			PORTB&=~_BV(1); // data out 0
//			PORTB|=_BV(1); // data out 1
		}else
		{
			PORTB&=~_BV(1); // data out 0
//			PORTB|=_BV(1); // data out 1
//			PORTB&=~_BV(1); // data out 0
		}
		DDRB|=_BV(1);
//		asm("nop");
//		asm("nop");
		PORTB|=_BV(2); // Clock out up

		DDRB&=~_BV(1); // data line to pullup
		PORTB|=_BV(1);
		transmit<<=1;

		in|=((PINB&_BV(1))==0?0:1); // Data in
		PORTB&=~_BV(2); // Clock out down
	}
	return in;
}

void OW_TEMP_POWER(bool on)
{
	if(on){
		// Turn parasitic power on and wait until the chip is ready to communicate
		BSP_OW_HIGH();
		deepSleep(WDTO_15MS);
		initADC(); // Turn on ADC to measure battery voltage
		ADCSRA |= (1 << ADSC);         // start ADC measurement - this first measurement value will be dumped because it may not be correct
	} else {
		// Turn parasitic power of the temperature sensor off
		BSP_OW_LOW();
	}
}

