#include <lathe_gui.h>
#include <bsp.h>

#include <stdio.h>

#define STATE_UNINITIALIZED 0
#define STATE_UNCALIBRATED 1
#define STATE_CALIBRATED 2
#define N_SZERSZAM 10

utkozo_setup_t utkozo_setup[2];
utkozo_active_t utkozo_active;

uint8_t segmentValues[NUMBER_DISPLAY_ALLBYTES];
int32_t inputValues[2];
int32_t inputValuesCalibration[2];
int32_t szerszamValue[N_SZERSZAM];
bool inputValuesValidState[2];
int32_t diffValues[2];
uint8_t mode=1; // 0:d (*2) 1:r
uint8_t szerszam=0;
uint16_t debugInput=0;


/** Index of the module that is currently edited. */
static uint8_t editFocus=0;
static int32_t counter=0;
static uint8_t lastButtonPressed=255;

/**
 * Set the visible value of an utkozo.
 * @param counterIndex counter index
 * @param value the new value - in d mode it is 2* the measured value
 */
static void setUtkozoValue(uint8_t counterIndex, int32_t value);

/**
 * Set the visible value of a counter.
 * @param counterIndex counter index
 * @param value the new value - in d mode it is 2* the measured value
 */
static void setValue(uint8_t counterIndex, int32_t value);

/**
 * Show a number on a seven segment display.
 * @param target index of the right most digit (smallest index)
 * @param length number of digits on the screen
 * @param value to be shown on the display negative values light up the minus segment
 * @param dotMask bit mask the dot segment in these position is lighted up. 1<<n means n fractional digits
 */
static void showNumber(uint8_t target, uint8_t length, int32_t value, uint8_t dotMask);
static void showNumberUnsigned(uint8_t target, uint8_t length, int32_t value, uint8_t dotMask);
/**
 * Set a decimal digit on a display.
 * @param target index of the digit
 * @param value decimal value to be shown on the digit. 0-9 are valid values. Other values turn all 7 segments off
 * @param dot boolean value true means the dot is lighted up
 */
static void setDigit(uint8_t target, uint8_t value, bool dot);
/**
 * Directly set the pattern of a digit.
 */
static void setDigitPattern(uint8_t target, uint8_t pattern);
/**
 * Set LED state.
 * @param ledIndex index of LED
 * @param value true light on
 */
static void setLed(uint16_t ledIndex, bool value);
/**
 * Save all settings to EEPROM memory.
 */
static void saveSettings();
/**
 * Query if value was crossed if we have the prev and next value.
 */
static inline bool crossed(int32_t prev, int32_t next, int32_t value)
{
	return next==value ||
		 (prev<value && next>value) ||
		 (prev>value && next<value);
}

static void toggleEditFocus(uint8_t target);
static void cancelEditFocus(uint8_t target);

static void fireUtkozo(uint8_t index)
{
	utkozo_setup[index].state=0;
	utkozo_active.at=getCurrentTimeMillis();
	utkozo_active.transistor=true;
}
static void saveSettings()
{
	uint8_t asFile[N_SZERSZAM*4+1];
	for(uint8_t i=0;i<N_SZERSZAM;++i)
	{
		*((int32_t *)(&asFile[i*4]))=szerszamValue[i];
	}
	asFile[N_SZERSZAM*4]=mode;
	saveData(asFile, N_SZERSZAM*4+1);
}
static void loadSettings()
{
	uint8_t asFile[N_SZERSZAM*4+1];
	if(loadData(asFile, N_SZERSZAM*4+1))
	{
		for(uint8_t i=0;i<N_SZERSZAM;++i)
		{
			szerszamValue[i]=*((int32_t *)(&asFile[i*4]));
		}
		mode=asFile[N_SZERSZAM*4];
		if(mode>1){ mode=1; }
	}
}
void gui_init()
{
	utkozo_setup[0].state=0;
	utkozo_setup[0].value=0;
	utkozo_setup[1].state=0;
	utkozo_setup[1].value=0;
	utkozo_active.at=0;
	utkozo_active.transistor=false;
	editFocus=0;
}

void gui_setup()
{
	diffValues[0]=0;
	diffValues[1]=0;
	inputValuesValidState[0]=STATE_UNINITIALIZED;
	inputValuesValidState[1]=STATE_UNINITIALIZED;
	inputValuesCalibration[0]=0;
	inputValuesCalibration[1]=0;
	for(uint8_t i=0;i<N_SZERSZAM;++i)
	{
		szerszamValue[i]=0;
	}
	loadSettings();
}

void gui_loop(uint32_t currentTimeMillis)
{
	bool villogas=currentTimeMillis%256>128;
	counter++;
	showNumber(DIGITS_UTKOZO_K_INDEX, DIGITS_UTKOZO_K_N, utkozo_setup[0].value, 1<<2);
	showNumber(DIGITS_UTKOZO_H_INDEX, DIGITS_UTKOZO_K_N, utkozo_setup[1].value, 1<<2);
	int32_t value=inputValues[0]+diffValues[0];
	if(mode==0)
	{
		value*=2;
		setDigit(DIGIT_MODE_INDEX, 'd', false);
	}else
	{
		setDigit(DIGIT_MODE_INDEX, 'r', false);
	}
	showNumber(DIGITS_K_INDEX, DIGITS_K_N, value, 1<<2);
	showNumber(DIGITS_H_INDEX, DIGITS_H_N, inputValues[1]+diffValues[1], 1<<2);
	bool szerszamVillog=diffValues[0]!=szerszamValue[szerszam];
	if(szerszamVillog&&!villogas)
	{
		for(int i=0;i<DIGITS_SZERSZAM_N;++i)
		{
			setDigitPattern(DIGITS_SZERSZAM_INDEX+i, 0);
		}
	}else
	{
		showNumber(DIGITS_SZERSZAM_INDEX, DIGITS_SZERSZAM_N, szerszam, (editFocus==EDIT_SZERSZAM && villogas)?1:0);
	}
	setLed(LED_INDEX_UTKOZO_K, utkozo_setup[0].state==1?true:(editFocus==EDIT_UTKOZO_KERESZT?villogas:false)); // LED kereszt
	setLed(LED_INDEX_UTKOZO_H, utkozo_setup[1].state==1?true:(editFocus==EDIT_UTKOZO_HOSSZ?villogas:false)); // LED hossz
	if(utkozo_active.transistor && currentTimeMillis>utkozo_active.at+500)
	{
		utkozo_active.transistor=false;
	}
	setLed(LED_INDEX_TRANSISTOR, utkozo_active.transistor); // transistor


	setLed(LED_INDEX_K, editFocus==EDIT_MEASURED_KERESZT?villogas:false); // LED edit kereszt measured
	setLed(LED_INDEX_H, editFocus==EDIT_MEASURED_HOSSZ?villogas:false); // LED edit kereszt measured

	// TODO debug remove
//	showNumberUnsigned(3, 3, lastButtonPressed, false);
//	showNumberUnsigned(6, 4, lastButtonPressed, false);
}
static void buttonPressedOff(uint8_t index)
{
	// Input focus not exists. Nothing to do.
}
static void buttonPressedUtkozo(uint8_t index)
{
	uint8_t utkozoIndex= (editFocus==EDIT_UTKOZO_KERESZT?0:1);
	int32_t value=utkozo_setup[utkozoIndex].value;
//	if(utkozoIndex==0 && mode==0)
//	{
//		value*=2;
//	}
	switch(index)
	{
		case 10:
			setUtkozoValue(utkozoIndex, value/10);
			break; // '*'
		case 11: // '#'
			setUtkozoValue(utkozoIndex, 0);
			break;
		default:
			setUtkozoValue(utkozoIndex, value*10+index);
			break;
	}
}
static void buttonPressedMeasured(uint8_t index)
{
	uint8_t measuredIndex= (editFocus==EDIT_MEASURED_KERESZT?0:1);
	int32_t value=inputValues[measuredIndex]+diffValues[measuredIndex];
	if(measuredIndex==0 && mode==0)
	{
		value*=2;
	}
	switch(index)
	{
		case 10:
			setValue(measuredIndex, value/10);
			break; // '*'
		case 11: // '#'
			setValue(measuredIndex, 0);
			break;
		default:
			setValue(measuredIndex, value*10+index);
			break;
	}
}
static void buttonPressedSzerszam(uint8_t index)
{
	if(index<10)
	{
		szerszam=index;
	}else
	{
		switch(index)
		{
			case 10: // '*'
				szerszamValue[szerszam]=diffValues[0];
				saveSettings();
				break;
			case 11: // '#'
				diffValues[0]=szerszamValue[szerszam];
				break;
			default:
				break;
		}
	}
}
typedef void (*handler_t)(uint8_t index);

void gui_buttonPressed(uint8_t index)
{
	lastButtonPressed=index;
	handler_t handler;
	switch(editFocus)
	{
		case EDIT_MEASURED_KERESZT:
		case EDIT_MEASURED_HOSSZ:
			handler=buttonPressedMeasured;
			break;
		case EDIT_UTKOZO_KERESZT:
		case EDIT_UTKOZO_HOSSZ:
			handler=buttonPressedUtkozo;
			break;
		case EDIT_SZERSZAM:
			handler=buttonPressedSzerszam;
			break;
		default:
			handler=buttonPressedOff;
			break;
	}
	switch(index)
	{
		// pin pad:
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			handler(index);
			break;
		case 200: mode++; mode%=2; saveSettings(); break;
		case 201:
			toggleEditFocus(EDIT_UTKOZO_KERESZT);
			break;
		case 202:
			cancelEditFocus(EDIT_UTKOZO_KERESZT);
			utkozo_setup[0].state=utkozo_setup[0].state==1?0:1;
			if(utkozo_setup[1].state==1 && utkozo_setup[0].state==1)
			{
				utkozo_setup[1].state=0;
			}
			break;
		case 203:
			toggleEditFocus(EDIT_UTKOZO_HOSSZ);
			break;
		case 204:
			cancelEditFocus(EDIT_UTKOZO_HOSSZ);
			utkozo_setup[1].state=utkozo_setup[1].state==1?0:1;
			if(utkozo_setup[1].state==1 && utkozo_setup[0].state==1)
			{
				utkozo_setup[0].state=0;
			}
			break;
		case 205:
			toggleEditFocus(EDIT_MEASURED_KERESZT);
			break;
		case 206:
			toggleEditFocus(EDIT_MEASURED_HOSSZ);
			break;
		case 207:
			toggleEditFocus(EDIT_SZERSZAM);
			break;
	}
}
static void cancelEditFocus(uint8_t target)
{
	if(editFocus==target)
	{
		editFocus=0;
	}
}
static void toggleEditFocus(uint8_t target)
{
	if(editFocus==target)
	{
		editFocus=0;
	}else
	{
		editFocus=target;
		switch(editFocus)
		{
			case EDIT_UTKOZO_KERESZT:
				utkozo_setup[0].state=0;
				break;
			case EDIT_UTKOZO_HOSSZ:
				utkozo_setup[1].state=0;
				break;
		}
	}
}

void gui_updateInput(uint8_t index, int32_t value, uint8_t errorcode, int32_t zero, bool zeroed)
{
	int32_t prev=inputValues[index]+diffValues[index];
	if(index==0 && inputValuesValidState[index]==STATE_UNCALIBRATED && zeroed)
	{
		inputValuesCalibration[index]=-zero;
	}
	if(inputValuesValidState[index]==STATE_UNINITIALIZED)
	{
		inputValuesValidState[index]=STATE_UNCALIBRATED;
		inputValuesCalibration[index]=-value;
	}
	inputValues[index]=value+inputValuesCalibration[index];
	int32_t next=inputValues[index]+diffValues[index];
	{
		if(index==0 && mode==0)
		{
			prev*=2;
			next*=2;
		}
		if(utkozo_setup[index].state==1)
		{
			int32_t utkvalue=utkozo_setup[index].value;
			if(crossed(prev, next, utkvalue) ||
			   crossed(prev, next, -utkvalue)
				)
			{
				fireUtkozo(index);
			}
		}
	}
}


static void showNumber(uint8_t target, uint8_t length, int32_t value, uint8_t dotMask)
{
	bool sign=value<0;
	if(sign)
	{
		value=-value;
	}
	for(uint8_t i=0;i<length-1;++i)
	{
		uint8_t digit=value%10;
		value/=10;
		setDigit(target+i, digit, dotMask&1);
		dotMask>>=1;
	}
	setDigit(target+length-1, sign?10:11, dotMask&1);
}
static void showNumberUnsigned(uint8_t target, uint8_t length, int32_t value, uint8_t dotMask)
{
	for(uint8_t i=0;i<length;++i)
	{
		uint8_t digit=value%10;
		value/=10;
		setDigit(target+i, digit, dotMask&1);
		dotMask>>=1;
	}
}
void setDigitPattern(uint8_t target, uint8_t pattern)
{
	if(target<DIGITS_END_INDEX)
	{
		segmentValues[target]=pattern;
	}
}

void setDigit(uint8_t target, uint8_t value, bool dot)
{
	uint8_t pattern=0;
	switch(value)
	{
		case 0: pattern=0b00111111; break;
		case 1: pattern=0b00110; break;
		case 2: pattern=0b1011011; break;
		case 3: pattern=0b1001111; break;
		case 4: pattern=0b1100110; break;
		case 5: pattern=0b1101101; break;
		case 6: pattern=0b1111101; break;
		case 7: pattern=0b00111; break;
		case 8: pattern=0b1111111; break;
		case 9: pattern=0b1101111; break;
		case 10: pattern=0b01000000; break;	// '-'
		case 'd': pattern=0b01011110; break;	// 'd'
		case 'r': pattern=0b00110011; break;	// 'r'
		default: pattern=0b00000000; break;
	}
	if(dot)
	{
		pattern |= 0b10000000;
	}
	setDigitPattern(target, pattern);
}
static void setLed(uint16_t ledIndex, bool value)
{
	uint8_t target=ledIndex/8;
	uint8_t bitIndex=ledIndex%8;
	uint8_t mask=1<<bitIndex;
	if(target>=DIGITS_END_INDEX && target<NUMBER_DISPLAY_ALLBYTES)
	{
		if(value)
		{
			segmentValues[target]|=mask;
		}
		else
		{
			segmentValues[target]&=~mask;
		}
	}
}

static void setUtkozoValue(uint8_t counterIndex, int32_t value)
{
//	if(mode==0 && counterIndex==0)
//	{
//		value/=2;
//	}
	utkozo_setup[counterIndex].value=value;
}

static void setValue(uint8_t counterIndex, int32_t value)
{
	switch(counterIndex)
	{
		case 0:
			if(mode==0)
			{
				//printf("(%d-%d*2)/2=", value, inputValues[0]);
				diffValues[0]=(value-inputValues[0]*2)/2;
				//printf("%d -> %d\n", diffValues[0], (diffValues[0]+inputValues[0])*2);
			}else
			{
				diffValues[0]=value-inputValues[0];
			}
			break;
		case 1:
			diffValues[1]=value-inputValues[1];
			break;
	}
}


