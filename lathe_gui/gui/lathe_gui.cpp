#include <lathe_gui.h>
#include <bsp.h>

utkozo_t utkozo[2];
uint8_t segmentValues[4*NUMBER_DISPLAY_NDIGIT+5];
int32_t inputValues[2];
int32_t diffValues[2];
uint8_t mode=1; // 0:d (*2) 1:r

static int32_t counter=0;

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
 * Query if value was crossed if we have the prev and next value.
 */
static inline bool crossed(int32_t prev, int32_t next, int32_t value)
{
	return next==value ||
		 (prev<value && next>value) ||
		 (prev>value && next<value);
}

static void fireUtkozo(uint8_t index)
{
	utkozo[index].state=0;
	utkozo[index].at=getCurrentTimeMillis();
//	printf("Fire utkozo %d %llu\n", index, currentTimeMillis);
	utkozo[index].transistor=true;
}

void gui_init()
{
	utkozo[0].state=0;
	utkozo[0].value=0;
	utkozo[0].at=0;
	utkozo[0].transistor=false;
	utkozo[1].state=0;
	utkozo[1].value=0;
	utkozo[1].at=0;
	utkozo[1].transistor=false;
}

void gui_setup()
{
	diffValues[0]=0;
	diffValues[1]=0;
}

void gui_loop(uint64_t currentTimeMillis)
{
	bool villogas=currentTimeMillis%256>128;
	counter++;
	showNumber(0, utkozo[0].value*(mode==0?2:1), 1<<2);
	showNumber(1, utkozo[1].value, 1<<2);
	int32_t value=inputValues[0]+diffValues[0];
	if(mode==0)
	{
		value*=2;
		setDigit(4, 0, 'd', false);
	}else
	{
		setDigit(4, 0, 'r', false);
	}
	showNumber(2, value, 1<<2);
	showNumber(3, inputValues[1]+diffValues[1], 1<<2);
	setDigit(4, 1, 'a', utkozo[0].state==0?false:(utkozo[0].state==1?villogas:true)); // LED kereszt
	setDigit(4, 2, 'a', utkozo[1].state==0?false:(utkozo[1].state==1?villogas:true)); // LED hossz
	if(utkozo[0].transistor && currentTimeMillis>utkozo[0].at+500)
	{
		//printf("Turn transistor off 0\n");
		utkozo[0].transistor=false;
	}
	if(utkozo[1].transistor && currentTimeMillis>utkozo[1].at+500)
	{
		//printf("Turn transistor off 1\n");
		utkozo[1].transistor=false;
	}
	setDigit(4, 3, 'a', utkozo[0].transistor); // transistor
	setDigit(4, 4, 'a', utkozo[1].transistor); // transistor
}
void gui_buttonPressed(uint8_t index)
{
	int32_t leftValue=inputValues[0]+diffValues[0];
	int32_t leftUtkozo=utkozo[0].value;
	int32_t rightUtkozo=utkozo[1].value;
	int32_t rightValue=inputValues[1]+diffValues[1];
	if(mode==0)
	{
		leftValue*=2;
		leftUtkozo*=2;
	}
	switch(index)
	{
		// Left pad:
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
			// digit
			if(utkozo[0].state==1)
			{
				setUtkozoValue(0, leftUtkozo*10+index);
			}else
			{
				setValue(0, leftValue*10+index);
			}
			break;
		case 10:
			if(utkozo[0].state==1)
			{
				setUtkozoValue(0, leftUtkozo/10);
			}else
			{
				setValue(0, leftValue/10);
			}
			break; // '*'
		case 11: // '#'
			if(utkozo[0].state==1)
			{
				setUtkozoValue(0, 0);
			}else
			{
				setValue(0, 0);
			}
			break;
		// Right pad:
		case 100:
		case 101:
		case 102:
		case 103:
		case 104:
		case 105:
		case 106:
		case 107:
		case 108:
		case 109: // digit
			if(utkozo[1].state==1)
			{
				setUtkozoValue(1, rightUtkozo*10+(index-100));
			}else
			{
				setValue(1, rightValue*10+(index-100));
			}
			break;
		case 110: // '*'
			if(utkozo[1].state==1)
			{
				setUtkozoValue(1, rightUtkozo/10);
			}else
			{
				setValue(1, rightValue/10);
			}
			break;
		case 111: // '#'
			if(utkozo[1].state==1)
			{
				setUtkozoValue(1, 0);
			}else
			{
				setValue(1, 0);
			}
			break;
		case 200: mode++; mode%=2; break;
		case 201:
			utkozo[0].state=utkozo[0].state==1?0:1; break;
		case 202:
			utkozo[0].state=utkozo[0].state==2?0:2;
			if(utkozo[1].state==2 && utkozo[0].state==2)
			{
				utkozo[1].state=0;
			}
			break;
		case 203:
			utkozo[1].state=utkozo[1].state==1?0:1; break;
		case 204:
			utkozo[1].state=utkozo[1].state==2?0:2;
			if(utkozo[1].state==2 && utkozo[0].state==2)
			{
				utkozo[0].state=0;
			}
			break;
	}
}

void gui_updateInput(uint8_t index, int32_t value)
{
	int32_t prev=inputValues[index]+diffValues[index];
	int32_t next=value+diffValues[index];
	if(utkozo[index].state==2)
	{
		int32_t value=utkozo[index].value;
		if(crossed(prev, next, value) ||
			crossed(prev, next, -value)
			)
		{
			fireUtkozo(index);
		}
	}
	inputValues[index]=value;
}


void showNumber(uint8_t target, int32_t value, uint8_t dotMask)
{
	bool sign=value<0;
	if(sign)
	{
		value=-value;
	}
	for(uint8_t i=0;i<5;++i)
	{
		uint8_t digit=value%10;
		value/=10;
		setDigit(target, i, digit, dotMask&1);
		dotMask>>=1;
	}
	setDigit(target, 5, sign?10:11, dotMask&1);
}

void setDigit(uint8_t target, uint8_t digitIndex, uint8_t value, bool dot)
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
	segmentValues[NUMBER_DISPLAY_NDIGIT*target+digitIndex]=pattern;
}

static void setUtkozoValue(uint8_t counterIndex, int32_t value)
{
	if(mode==0 && counterIndex==0)
	{
		value/=2;
	}
	utkozo[counterIndex].value=value;
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


