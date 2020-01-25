// Lathe GUI on ATMega328 - see README.asciidoc

#include <bsp.h>
#include <bsp_platform.h>
#include <lathe_gui.h>
#include <pinmapping.h>
#include <timer1.h>

/**
 * Set all pins to default status and reset all HW the way we use them.
 */
static void resetAllHW();

/**
 * Set up pinpad input ADC to start reading value
 */
static void startPinPadADC()
{
	ADCSRA|=_BV(ADSC);
}
/**
 * Wait pinpad input reading and store the input value.
 */
static void finishPinPadADC()
{
	/// Exit loop when either there is no running ADC or there is an active ready signalling.
	while( ((ADCSRA&_BV(ADIF)) == 0 ) && ((ADCSRA&_BV(ADSC)) == 1))
	{
	}
	/// If there is a ready signalling...
	if((ADCSRA&_BV(ADIF)) != 0)
	{
		/// Clear ready singalling
		ADCSRA|=_BV(ADIF);
		uint16_t value=ADC;
		// TODO process value: decode ADC value to buttons bits pattern
	}
	// TODO
}
/**
 * Shift in and out into and from the shift registers that handle input/output.
 */
static void shiftButtonsAndSegments()
{
	uint8_t status;
	uint8_t value;
	uint8_t nbytes=128;
	// Turn SS to output! Otherwise low SS would transition SPI into slave mode!
	SPI_SS_MASTER();
	// DORD: LSB is transmitted first
	SPCR=_BV(SPE)|_BV(DORD)|_BV(MSTR);

	status=SPSR; value=SPDR;	// Reset status
	for(int i=0;i<nbytes;++i)
	{
		SPDR=0x0; // TODO get output data
		while(SPSR&_BV(SPIF)==0);	// Wait until transfer is finished
		status=SPSR; value=SPDR;	// Reset status and read value
		// TODO store read value
	}
	SPCR=0;	// disable SPI
}
/**
 * Read the values from the quad decoders and update the locally stored value.
 */
static void readQuadDecoders()
{
	for(uint8_t i=0;i<2;++i)
	{
		// TODO 
	}
}
/**
 * Execute debounce logic on input and execute button press handler in case a valid button press is detected.
 */
static void debounceAndHandleInput()
{
	// TODO 0->1 triggers button event but only if there was a minimal time spent since last change
	// TODO 0->1 and 1->0 resets the time counter since last change
	// TODO changed bit to button index
}

/**
 * TODO call this on power fail before saving state into EEPROM.
 */
static void disableAllHardware()
{
	// TODO disable all hardware - executed on pre-power fail to spare energy for state saving
	// TODO disable SPI
	// disable ADC
	ADMUX=0;
	ADCSRA=0;
	ADCSRB=0;
	// TODO disable PWM
	// TODO turn pins off
}

int main()
{
	resetAllHW();
	gui_init();
	gui_setup();
	while(1)
	{
		startPinPadADC();
		shiftButtonsAndSegments();
		readQuadDecoders();
		finishPinPadADC();
		debounceAndHandleInput();
		gui_loop(getCurrentTimeMillis());
	}
}

static void resetAllHW()
{
	// Input/pullup on all pins
	DDRB=0;
	PORTB=0xFF;
	DDRC=0;
	PORTC=0xFF;
	DDRD=0;
	PORTD=0xFF;

	// TODO AIN0 and AIN1 - power fail detector
	DIDR1|=_BV(AIN1D)|_BV(AIN0D);	// Disable digital input on Analog comparator pins

	DIGITS_LATCH_OFF();
	INPUT_LATCH_OFF();
	PINPAD_INPUT();
	CONFIG_PWM_PINS();

	NCS_SENSOR_OFF(0);
	NCS_SENSOR_OFF(1);

	// AD converter set up:
	ADMUX=_BV(REFS0)|0b0000;
	ADCSRA=_BV(ADEN);
	ADCSRB=_BV(ACME);
	initTimer1();
	sei();
}

