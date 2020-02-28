#include <stdarg.h>
#include <sim_labels.h>

#include <sim_progmem.cpp>

#define PIN_NCS 1
#define MASK_RX (1<<PIN_NCS)
#define ZERO_MASK (1<<3)
#define N_CYCLE_RX 212
#define NSTEP 6
#define STATUS_MASK_ERROR 1
#define STATUS_MASK_ZERO 2
// (151+144*5)

static uint8_t sindex=0;
static uint8_t signalAB;
#define N_CS_MASK MASK_RX
static uint8_t nChipSelect=N_CS_MASK;
static uint8_t nZero=ZERO_MASK;
static AVR_simulator_t * ctx;
static bool loopLabelTouched=false;
static uint8_t signalPatterns[]={
	0b000101,
	0b000001,
	0b000000,
	0b000100,
};

static bool logJump=false;

/// Global error marker - when set then tests have failed.
static bool error=false;

/// Increments of patterns between two samples.
static int32_t inc[NSTEP];

#define RX_BUFFER_SIZE 128
static uint8_t rxBytes[RX_BUFFER_SIZE];
static uint8_t rxNChars=0;
static uint8_t rxNbits=0;
static bool rxOn=false;
static uint16_t rxCtr=0;
static uint16_t rxCurr=0;

#define RX_BIT_CYCLES 2

/// Store which commands were executed - used to find untested paths of the program.
static bool commandExecuted[PROGMEM_N_WORDS];
static bool progmemRead[PROGMEM_N_WORDS*2];

static void ASSERT(bool ok, const char * format, ...)
{
    va_list args;
    va_start(args, format);
	if(!ok)
	{
		fprintf(stderr, "ERROR: ");
		vfprintf(stderr, format, args);
		fprintf(stderr, "\n");
		va_end(args);
		va_start(args, format);
		printf("ERROR: ");
		error=true;
	}else
	{
		printf("OK: ");
	}
		vprintf(format, args);
    va_end(args);
	printf("\n");
if(!ok) {fflush(stdout); fflush(stderr); exit(1);}

}
static void ASSERT_SILENT(bool ok, const char * format, ...)
{
    va_list args;
    va_start(args, format);
	if(!ok)
	{
		fprintf(stderr, "ERROR: ");
		vfprintf(stderr, format, args);
		fprintf(stderr, "\n");
		va_end(args);
		printf("ERROR: ");
		va_start(args, format);
		vprintf(format, args);
		    va_end(args);
		printf("\n");
		error=true;
	}else
	{
//		printf("OK: ");
	}
//if(!ok) {fflush(stdout); fflush(stderr); exit(1);}

}



static void rxStart()
{
	rxOn=true;
	rxNbits=0;
	rxNChars=0;
	rxCtr=0;
	rxCurr=0;
}
static void rxEnd()
{
	rxOn=false;
	rxNbits=0;
	rxNChars=0;
	rxCtr=0;
	rxCurr=0;
}

static bool rxRead(uint32_t * outCounter, uint8_t *outError, uint32_t * outZero)
{
	if(rxNChars>=10)
	{
		ASSERT_SILENT(rxBytes[0]==0x80, "Measure byte is correct.");
		*outCounter=(((uint32_t)rxBytes[1])<<0)|
				(((uint32_t)rxBytes[2])<<8)|
			(((uint32_t)rxBytes[3])<<16)|
			(((uint32_t)rxBytes[4])<<24);
		*outError=rxBytes[5];
		*outZero=(((uint32_t)rxBytes[6])<<0)|
				(((uint32_t)rxBytes[7])<<8)|
			(((uint32_t)rxBytes[8])<<16)|
			(((uint32_t)rxBytes[9])<<24);
		return true;
	}else
	{
		*outCounter=0;
		*outError=0;
		*outZero=0;
		return false;
	}
}


static void initializeCPU(AVR_simulator_t* ctx)
{
	ctx->PC=0;
	setSP(ctx, ADDR_SRAM+N_SRAM-1);
	ctx->cycle=0;
	ctx->progmemContent=progMemContent;
	for(uint32_t i=0;i<PROGMEM_N_WORDS; ++i)
	{
		commandExecuted[i]=false;
	}
	for(uint32_t i=0;i<PROGMEM_N_WORDS*2; ++i)
	{
		progmemRead[i]=false;
	}
}
/**
 * Execute the main program until the loop label was touched.
 */
static void executeOneCycle(AVR_simulator_t* ctx)
{
	loopLabelTouched=false;
	do
	{
		executeFromAddress(ctx,ctx->PC);
	}while(!loopLabelTouched);
}

static int32_t getCounterValue()
{
	return getReg(ctx,26)|
			(((uint32_t)getReg(ctx,27))<<8)|
			(((uint32_t)getReg(ctx,28))<<16)|
			(((uint32_t)getReg(ctx,29))<<24);
}
static int32_t setCounterValue(int32_t v)
{
	setReg(ctx,26, v&0xff);
	setReg(ctx,27, (v>>8)&0xff);
	setReg(ctx,28, (v>>16)&0xff);
	setReg(ctx,29, (v>>24)&0xff);
}
static bool getCounterError()
{
	uint8_t regVal=getReg(ctx,17);
	return (regVal&STATUS_MASK_ERROR)!=0;
}
static void clearCounterError()
{
	setReg(ctx,17,getReg(ctx,17)&~STATUS_MASK_ERROR);
}

/// Test starting from all states with current incX settings. The initial counter value is set up by the function. Then a few cycles are executed and results are checked so all combinations occur at least once.
static void testFromAllStates(uint32_t initialCounter);
static void testNCycles(uint32_t nCycle, uint32_t initialCounter);
static void updatePins(AVR_simulator_t * ctx);
/// Initiate communication and read out counter and error values
static void testCommunication(uint32_t counterValue, uint8_t errorValue, uint32_t zeroValue);

/// Initial counter values for test cases to test each overflow arrangements to happen correctly:
/// Overflow up, overflow down in each configuration
static uint32_t initialCounterValues[]={
	0x00000000, 0xFF000000, 0xFFFF0000, 0xFFFFFF00,0xFFFFFFFF, 0x00FFFFFF, 0x0000FFFF, 0x000000FF
};

/** Test all input order combinations in all phase */
static void testAllCombinations(uint8_t index)
{
	if(index<NSTEP)
	{
		for(inc[index]=-2;inc[index]<=2;++inc[index])
		{
			testAllCombinations(index+1);
		}
	}else{
		for(int i=0;i<sizeof(initialCounterValues)/sizeof(uint32_t);++i)
		{
			testFromAllStates(initialCounterValues[i]);
		}
	}
}
static uint8_t AVR_read_progmem_byte(uint32_t addr)
{
	if(addr>=PROGMEM_N_WORDS*2)
	{
		ASSERT(false, "Fail to read off limit progmem at address: 0x%x", addr);
		return 0;
	}
	uint16_t val=ctx->progmemContent[addr>>1];
	if((addr&1)!=0)
	{
		val>>=8;
	}
	progmemRead[addr]=true;
	return (uint8_t)val;
}


int main (int argc, char ** argv)
{
	inc[0]=0; inc[1]=0;inc[2]=0; inc[3]=0; inc[4]=0; inc[5]=0;
	AVR_simulator_t ctx;
	initializeCPU(&ctx);
	beforeStart(&ctx);
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==0, "INITIALIZE COUNTER to 0");
	executeOneCycle(&ctx);
	inc[0]=1; inc[1]=1;inc[2]=1; inc[3]=1; inc[4]=1; inc[5]=1;
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==3, "increment is not counted on the same cycle when set up: %d ",getCounterValue());
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==9, "increment is only counted in every second cycle %d", getCounterValue());
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==15, "increment 3+6+6 %d", getCounterValue());
	for(int i=0;i<1000;++i)
	{
		executeOneCycle(&ctx);
		ASSERT_SILENT(getCounterValue()==(i+1)*6+15, "increment %d %d", (i+1)*6+15, getCounterValue());
	}
	ASSERT(getCounterValue()==6015, "increment 6015 %d", getCounterValue());
	inc[0]=0; inc[1]=0;inc[2]=0; inc[3]=0; inc[4]=0; inc[5]=0;
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==6018, "increment 3 only %d", getCounterValue());
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==6018, "Counting stopped %d", getCounterValue());
	inc[0]=0; inc[1]=0;inc[2]=0; inc[3]=0; inc[4]=0; inc[5]=0;
	executeOneCycle(&ctx);
	setCounterValue(0);
	ASSERT(getCounterValue()==0, "Set counter value works");
	setCounterValue(0x12345678);
	ASSERT(getCounterValue()==0x12345678, "Set counter value works");
	setCounterValue(0);

	testAllCombinations(0);

	inc[0]=0; inc[1]=0;inc[2]=0; inc[3]=0; inc[4]=0; inc[5]=0;
	executeOneCycle(&ctx);	// Counter is stopped
	uint32_t zeroValue=0xABCDEF01;
	setCounterValue(zeroValue);
	clearCounterError();
	nZero=0;
	updatePins(&ctx);
	executeOneCycle(&ctx);
	nZero=ZERO_MASK;
	updatePins(&ctx);
	executeOneCycle(&ctx);
	uint32_t counterValue=0x12345678;
	setCounterValue(counterValue);
	testCommunication(counterValue, 2, zeroValue);

	setCounterValue(0);
	clearCounterError();
	inc[0]=0; inc[1]=0;inc[2]=1; inc[3]=0; inc[4]=0; inc[5]=0;
	nZero=0;
	updatePins(&ctx);
	// Test reading out counter while counting
	testCommunication(2, 2, 131);	// Counter is latched after two cycles, zero is latched after 131 cycles
	ASSERT(getCounterValue()==N_CYCLE_RX+9, "Counter value: %d required: %d", getCounterValue(), N_CYCLE_RX+9);	// Readout test takes N_CYCLE_SPI+26 cycles
	for(uint32_t i=0;i<CODE_ENDS;++i)
	{
		if((i>=CODE_ENDS&&i<0x100)||i>=0x200)
		{
			ASSERT_SILENT(!commandExecuted[i], "Unused command MUST NOT be executed at progmem index 0x%x", i);
		}else
		{
			ASSERT_SILENT(commandExecuted[i], "Command MUST BE executed at progmem index 0x%x", i);
		}
	}
	for(uint32_t i=0x200;i<0x300;++i)
	{
		ASSERT_SILENT(progmemRead[i], "Whole table must be read index 0x%x", i);
	}
	ASSERT(true, "Progmem coverage checked.");
	return error?1:0;
}
static void testCommunication(uint32_t counterValue, uint8_t errorValue, uint32_t zeroValue)
{
	nChipSelect=0;
	updatePins(ctx);
	executeOneCycle(ctx);
	nChipSelect=N_CS_MASK;
	updatePins(ctx);
	rxStart();
	bool rxReady=false;
	uint32_t counter=0;
	uint8_t error=0;
	uint32_t zero=0;
	for(uint32_t i=0;i<1000 && !rxReady;++i)
	{
		executeOneCycle(ctx);
		rxReady=rxRead(&counter, &error, &zero);
		if(rxReady)
		{
			ASSERT(i==N_CYCLE_RX, "RX data out takes %d cycles. Actual: %d", N_CYCLE_RX, i);
		}
	}
	ASSERT(rxReady, "RX readout happened before timeout.");
	ASSERT(counter==counterValue, "Counter value read correctly. Expected: %u (%x) value: %u (%x)", counterValue, counterValue, counter, counter);
	ASSERT(error==errorValue, "Error value read correctly. Expected: %u value: %u", errorValue, error);
	ASSERT(zero==zeroValue, "Zero value read correctly. Expected: %u (%x) value: %u (%x)", zeroValue, zeroValue, zero, zero);
	ASSERT(getReg(ctx, 24)==COMM_STATE_BYTESHIFT_BIT_STOP2, "Communication state is COMM_STATE_BYTESHIFT_BIT_STOP2 Actual: 0x%x", getReg(ctx, 24));
	executeOneCycle(ctx);
	ASSERT(getReg(ctx, 24)==COMM_STATE_FINISHED, "Communication state is COMM_STATE_FINISHED 0x%x", getReg(ctx, 24));
	executeOneCycle(ctx);
	ASSERT(getIO(ctx, DDRB)==0, "DDRB is turned off after communication + 2 cycles");
	ASSERT(getReg(ctx, 24)==COMM_STATE_OFF, "Communication state is COMM_STATE_OFF 0x%x", getReg(ctx, 24));
	for(uint32_t i=0;i<5;++i)
	{
		executeOneCycle(ctx);
		ASSERT(getReg(ctx, 24)==COMM_STATE_OFF, "Communication state is off after communication and chip selectput to high 0x%x 0x%x (%d)", getReg(ctx, 24), getIO(ctx, PINB), i);
	}
	rxEnd();
}

static void testNCycles(uint32_t nCycle, uint32_t initialCounter)
{
	executeOneCycle(ctx);	// First is not affected by the current setting but the previous.
	executeOneCycle(ctx);	// Second is affected - errors may be raised here
	clearCounterError();
	setCounterValue(initialCounter);
	int32_t v=initialCounter;
	bool problem=false;
	for(int i=0;i<NSTEP;++i)
	{
		problem=problem || inc[i]<-1||inc[i]>1;
	}
//	logJump=true;
	for(uint32_t i=0;i<nCycle;++i)
	{
		executeOneCycle(ctx);
		if(!problem)
		{
			for(int i=0;i<NSTEP;++i)
			{
				v+=inc[i];
			}
		}
		bool counterError=getCounterError();
		if(counterError!=problem)
		{
	for(int i=0;i<NSTEP;++i)
	{
		printf("inc[%d] %d\n", i, inc[i]);
	}
		}
		ASSERT_SILENT(counterError==problem, problem?"Problem samples raise error %s":"NO PROBLEM %s", counterError?"true":"false");
		ASSERT_SILENT(getCounterValue()==v, "Count once expected: %d %d", v, getCounterValue());
		clearCounterError();
	}
}
/// Test 5 cycles of the current increment pattern: each sample combination will happen once.
static void testFromAllStates(uint32_t initialCounter)
{
	for(uint8_t i=0;i<4;++i)
	{
		sindex=i;
		signalAB=signalPatterns[sindex];
		updatePins(ctx); // Required in cases when add is 0 then the value would not be updated
		testNCycles(5, initialCounter);
	}
}

static void updatePins(AVR_simulator_t * ctx)
{
	setIO(ctx, PINB, signalAB|nChipSelect|nZero);
}
static void beforeStart(AVR_simulator_t * _ctx)
{
	ctx=_ctx;
	signalAB=signalPatterns[sindex];
	updatePins(ctx);
}

static void debugUseCycle(AVR_simulator_t * ctx, uint32_t cycle)
{
}

static void incrementSample(AVR_simulator_t * ctx, int32_t add)
{
	// printf("increment sample: %d\n", add);
	if(add!=0)
	{
		sindex+=add+4;
		sindex%=4;
		signalAB=signalPatterns[sindex];
		updatePins(ctx);
	}
}

static void checkBreakpoint(AVR_simulator_t * ctx, uint32_t pc)
{
	commandExecuted[ctx->PC]=true;
	uint64_t cycle=ctx->cycle;
	uint8_t COMM_STATE=getReg(ctx, 24);
	if(pc==loop)
	{
		loopLabelTouched=true;
		ctx->breakpointActivated=true;
		//printf("1 cycle executed. PC: 0x%x\n", pc);
		if(rxOn)
		{
		uint8_t portb=getIO(ctx, PORTB);
		uint8_t ddrb=getIO(ctx, DDRB);
		bool rxval=((portb&MASK_RX)==0) && ((ddrb&MASK_RX)!=0);
		if(rxCtr!=0)
		{
			rxCtr++;
			for(uint8_t i=0;i<8;++i)
			{
				if(rxCtr==(i+1)*RX_BIT_CYCLES+1)
				{
					ASSERT_SILENT((i==7?COMM_STATE_BYTESHIFT_BIT_STOP1:COMM_STATE_BYTESHIFT_BIT1)==COMM_STATE, "COMM state is after bit shifting. Actual: 0x%x i: %d", COMM_STATE, i);
//					printf("bit rxCtr %d BIT: %d RECEIVED: %d\n", rxCtr, i, rxval);
					rxCurr>>=1;
					if(rxval)
					{
						rxCurr|=0b10000000;
					}
				}
			}
			if(rxCtr==(8+1)*RX_BIT_CYCLES)
			{
				rxCtr=0;
				rxNbits=0;
				if(rxNChars<RX_BUFFER_SIZE)
				{
					// printf("byte RECEIVED: 0x%x\n", rxCurr);
					rxBytes[rxNChars]=rxCurr;
				}
				rxNChars++;
			}
		}
		else if(rxval)
		{
			ASSERT_SILENT(COMM_STATE_BYTESHIFT_BIT1==COMM_STATE, "COMM state is after start bit shifting. Actual: 0x%x", COMM_STATE);
			rxCtr=1;
			rxCurr=0;
		}
		}
	}
#define CHECK(X) if(pc==X){printf("AT: " #X "\n");}
	if(pc==process3samples_a || pc==process3samples_b)
	{
		uint32_t v=getCounterValue();
		uint8_t zl=getReg(ctx, 30);
		if(logJump)
		{
		printf("PATTERN: 0x%x %c%c->%c%c->%c%c->%c%c %d\n", zl, 
			(zl & 0b01000000 ? '1' : '0'),
			(zl & 0b00010000 ? '1' : '0'),

			(zl & 0b10000000 ? '1' : '0'),
			(zl & 0b00100000 ? '1' : '0'),

			(zl & 0b00001000 ? '1' : '0'),
			(zl & 0b00000010 ? '1' : '0'),

			(zl & 0b00000100 ? '1' : '0'),
			(zl & 0b00000001 ? '1' : '0'),
			v
			);
			// logJump=false;
		}
	}
	// Trace sampling periods counted in cycles
	static bool initialized=false;
	if(pc==sample1a)
	{
		initialized=true;
	}
	static uint32_t prevSampleCycle=0;

	if(pc==sample0a || pc==sample1a || pc==sample2a ||
	pc==sample0b || pc==sample1b || pc==sample2b || pc==sample2b_b)
	{
		if(initialized)
		{
			uint64_t diff=cycle-prevSampleCycle;
			ASSERT_SILENT(diff==12, "Sampling cycles: %lu instead of 12 at: 0x%x COMM_STATE: 0x%x\n", diff, pc, COMM_STATE);
		}
		prevSampleCycle=cycle;
		if(pc==sample0a)
		{
			incrementSample(ctx, inc[0]);
		}
		if(pc==sample1a)
		{
			incrementSample(ctx, inc[1]);
		}
		if(pc==sample2a)
		{
			incrementSample(ctx, inc[2]);
		}
		if(pc==sample0b)
		{
			incrementSample(ctx, inc[3]);
		}
		if(pc==sample1b)
		{
			incrementSample(ctx, inc[4]);
		}
		if(pc==sample2b || pc==sample2b_b)
		{
			incrementSample(ctx, inc[5]);
		}
	}
}

