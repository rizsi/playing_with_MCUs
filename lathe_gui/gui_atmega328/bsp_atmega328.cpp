// Lathe GUI on ATMega328 - see README.asciidoc

#include <bsp.h>
#include <bsp_platform.h>
#include <lathe_gui.h>
#include <pinmapping.h>
#include <timer1.h>
#include <debug_uart0.h>

// Number of input shift registers multipled by number of repeats due to scanning rows of pinpad
#define NUMBER_SHIFT_IN_BYTES 6
#define NUMBER_SHIFT_IN_CYCLES 9

static volatile uint8_t prevPIND;
static volatile uint32_t calib1UpEdgeTime;
static volatile uint32_t calib2UpEdgeTime;

ISR(PCINT2_vect)
{
	uint8_t v=PIND;
	if(((v&_BV(6))!=0) && ((prevPIND&_BV(6))==0))
	{
		calib1UpEdgeTime=timer1_GetCycles();
	}
	if(((v&_BV(7))!=0) && ((prevPIND&_BV(7))==0))
	{
		calib2UpEdgeTime=timer1_GetCycles();
	}
	prevPIND=v;
}

/**
 * Shifted in bits of the input shift registers - handles buttons.
 */
static uint8_t shiftInValues[NUMBER_SHIFT_IN_BYTES];

/**
 * Set all pins to default status and reset all HW the way we use them.
 */
static void resetAllHW();

/**
 * Process current time and current measured pressed button index.
 * Debounce the button event and execute button handler when debounced event happens.
 * @param t current time in millis
 * @param pressedIndex the result of current measurement of buttons input
 */
static void debounceAndExecute(uint32_t t, uint8_t pressedIndex)
{
	static uint32_t eventT=0;
	static uint8_t index=-1;
	static uint8_t status=0;
	switch(status)
	{
		case 0:	// idle
			if(pressedIndex!=255)
			{
				index=pressedIndex;
				eventT=t;
				status=1;
			}
			break;
		case 1: // pre-press
			if(pressedIndex==index)
			{
				// Same button - check time
				if(t-eventT>50)
				{
//					UART0_Send('i');
//					UART0_Send_uint32(pressedIndex);
//					UART0_Send('\n');
					gui_buttonPressed(pressedIndex);
					status=2;
				}
			}else
			{
				status=0;
			}
			break;
		case 2: // press handled
			if(pressedIndex==index)
			{
				// Nothing to do
			}else
			{
				// Button unpressed
				status=3;
				eventT=t;
			}
			break;
		case 3: // Unpress started - after a timeout go to idle
			if(t-eventT>50)
			{
				status=0;
			}
			break;
		default:
			status=0;	// Never happens but return to normal states though
			break;
	}
}
static inline uint8_t max8(uint8_t a, uint8_t b)
{
	return a>b?a:b;
}
static uint8_t getOutputByte(uint8_t i, uint8_t nbytes)
{
	uint8_t hatravan=nbytes-i-1;
	if(hatravan<NUMBER_DISPLAY_ALLBYTES)
	{
		return segmentValues[hatravan];	// We send index 0 last
	}else
	{
		return 0b01010101;	// Do not cate - bacause this will be shifted through all registers
	}
}
static void driveInput(uint8_t i, uint8_t nbytes)
{
	if(i<NUMBER_SHIFT_IN_CYCLES)
	{
		if((i%3)==0)
		{
			PINPAD_ROW_ON(i/3);
			_delay_us(10);	// Stabilize output
			// Enable input SHRs reads current button states - only when CP is ticking
			SHIFT_IN_LATCH_ON();
		}
		if((i%3)==1)
		{
			SHIFT_IN_LATCH_OFF();
			PINPAD_ROWS_INIT();
		}
	}
}
static void storeInputByte(uint8_t i, uint8_t nbytes, uint8_t value)
{
	if(i<NUMBER_SHIFT_IN_CYCLES)
	{
		if((i%3)!=0)
		{
			shiftInValues[i-(i/3)-1]=value;
		}
	}// else do not care because those values are garbage input on the last shift register
}
/**
 * Shift in and out into and from the shift registers that handle input/output.
 */
static void shiftButtonsAndSegments()
{
	uint8_t status;
	uint8_t value;
	uint8_t nbytes=max8(NUMBER_DISPLAY_ALLBYTES, NUMBER_SHIFT_IN_CYCLES);

	// Turn SS to output! Otherwise low SS would transition SPI into slave mode!
	SPI_SS_MASTER();
	SHIFT_IN_BUFFER_ON();
	SPCR=_BV(SPE)
	//	|_BV(DORD) // DORD: LSB is transmitted first
		|_BV(MSTR);
	SPCR|=0b11;	// clockdiv: /16
	SPSR&=~_BV(SPI2X); // Disable clock x2
	status=SPSR; value=SPDR;	// Reset status
	for(int i=0;i<nbytes;++i)
	{
		driveInput(i, nbytes);
		SPDR=getOutputByte(i, nbytes);
		while((SPSR&_BV(SPIF))==0);	// Wait until transfer is finished
		status=SPSR; value=SPDR;	// Reset status and read value
		storeInputByte(i, nbytes, value);
	}
	SPCR=0;	// disable SPI
	SHIFT_IN_BUFFER_OFF();
	DIGITS_LATCH_ON();	// Strobe on Latch loads value into the output register of shifts
	_delay_us(10);
	DIGITS_LATCH_OFF();
}

inline static void sensor_readout_callback(uint8_t sensorIndex, int32_t data32, int8_t errorcode)
{
	uint32_t time=timer1_GetCycles();
	gui_updateInput(sensorIndex, data32, errorcode);
}


// Ugly hack to include the source code but it works :-)
#include "sensor_readout.cpp"
/**
 * Read the values from the quad decoders and update the locally stored value.
 */
static void readQuadDecoders()
{
	sensor_readout(0);
	sensor_readout(1);
}

#define BUTTON(BYTE, BIT, VALUE) ((((uint16_t)(BYTE))<<8)+(BIT)+((VALUE)?0b10000000:0))

static uint8_t decodedIndex(uint8_t byteIndex, uint8_t bitIndex, bool value)
{
	switch(BUTTON(byteIndex,bitIndex,value))
	{
		// PINPAD ROW 1
		case BUTTON(1,0,true): return 0;
		case BUTTON(1,1,true): return 1;
		case BUTTON(1,2,true): return 2;
		case BUTTON(1,3,true): return 3;

		// PINPAD ROW 2
		case BUTTON(3,0,true): return 4;
		case BUTTON(3,1,true): return 5;
		case BUTTON(3,2,true): return 6;
		case BUTTON(3,3,true): return 7;

		// PINPAD ROW 3
		case BUTTON(5,0,true): return 8;
		case BUTTON(5,1,true): return 9;
		case BUTTON(5,2,true): return 10;
		case BUTTON(5,3,true): return 11;

		// Simple buttons
		case BUTTON(1,4,true): return 200;
		case BUTTON(1,5,true): return 201;
		case BUTTON(1,6,true): return 202;
		case BUTTON(1,7,true): return 203;

		case BUTTON(0,0,true): return 204;
		case BUTTON(0,1,true): return 205;
		case BUTTON(0,2,true): return 206;
		case BUTTON(0,3,true): return 207;
		case BUTTON(0,4,true): return 208;
		case BUTTON(0,5,true): return 209;
		case BUTTON(0,6,true): return 210;
		case BUTTON(0,7,true): return 211;

		default: return 255;
	}
}

/**
 * Decode shift in button to index.
 * @return -1 means no button
 */
static uint8_t decodeShiftInButton()
{
	uint8_t currentIndex=255;
	uint8_t nFound=0;
	for(uint8_t byteIndex=0;byteIndex<NUMBER_SHIFT_IN_BYTES;++byteIndex)
	{
		uint8_t mask=0b10000000;
		for(uint8_t bitIndex=0;bitIndex<8;++bitIndex)
		{
			bool v=(shiftInValues[byteIndex]&mask)!=0;
			uint8_t decoded=decodedIndex(byteIndex, bitIndex, v);
			if(decoded!=255)
			{
				currentIndex=decoded;
				nFound++;
			}
			mask>>=1;
		}
	}
	if(nFound!=1)
	{
		currentIndex=255;
	}
	return currentIndex;
}

int main()
{
	resetAllHW();
	gui_init();
	gui_setup();
	while(1)
	{
		// Single period time: about 16ms - perfect
		uint32_t t=getCurrentTimeMillis();
		shiftButtonsAndSegments();
		
		uint32_t tc=timer1_GetCycles();
		uint32_t old=tc-16000000ul;	// Very old - 1 second
		uint32_t c1;
		uint32_t c2;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			c1=calib1UpEdgeTime;
			calib1UpEdgeTime=old;
			c2=calib2UpEdgeTime;
			calib2UpEdgeTime=old;
		}
		if(tc-c1<8000000ul || c1-tc<8000000ul)
		{
			// TODO there was a calib1 edge
		}
		if(tc-c2<8000000ul || c2-tc<8000000ul)
		{
			// TODO there was a calib2 edge
		}
		readQuadDecoders();
		uint8_t shiftInButton=decodeShiftInButton();
		debounceAndExecute(t, shiftInButton);
		gui_loop(t);
		for(uint8_t i=0;i<NUMBER_SHIFT_IN_BYTES;++i) // TODO remove
		{
			segmentValues[6+i]=shiftInValues[i];
		}
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
	SHIFT_IN_LATCH_OFF();
	SHIFT_IN_BUFFER_OFF();

	PINPAD_ROWS_INIT();
	CONFIG_PWM_PINS();

	NCS_SENSOR_OFF(0);
	NCS_SENSOR_OFF(1);

	initTimer1();
	UART0_Init();	// Debug messages are sent using UART0

	// Calibration signal
	PCICR=_BV(PCIE2);
	PCMSK2=_BV(PCINT22)|_BV(PCINT23);
	prevPIND=PIND;
	sei();
}

