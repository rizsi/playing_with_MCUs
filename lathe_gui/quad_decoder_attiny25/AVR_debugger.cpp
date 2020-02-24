#include <stdarg.h>
#include <sim_labels.h>

#include <sim_progmem.cpp>

#define PIN_NCS 1
#define PIN_SPI_CLK 4
#define PIN_SPI_DATA 3
#define MASK_CLK (1<<PIN_SPI_CLK)
#define MASK_DATA (1<<PIN_SPI_DATA)
#define N_CYCLE_SPI 151

static uint8_t sindex=0;
static uint8_t signalAB;
#define N_CS_MASK 2
static uint8_t nChipSelect=N_CS_MASK;
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
static int32_t inc0=0;
static int32_t inc1=0;
static int32_t inc2=0;

#define SPI_BUFFER_SIZE 128
static uint8_t spiBytes[SPI_BUFFER_SIZE];
static uint8_t spiNChars=0;
static uint8_t spiNbits=0;
static bool spiPrevClk=false;
static bool spiOn=false;
static uint8_t spiCurr=0;

/// Store which commands were executed - used to find untested paths of the program.
static bool commandExecuted[PROGMEM_N_WORDS];


static void spiStart()
{
	spiOn=true;
	spiNbits=0;
	spiNChars=0;
	spiPrevClk=false;
}
static void spiEnd()
{
	spiOn=false;
	spiNbits=0;
	spiNChars=0;
	spiPrevClk=false;
}

static bool spiRead(uint32_t * outCounter, uint8_t *outError)
{
	if(spiNChars>=5)
	{
		*outCounter=(((uint32_t)spiBytes[0])<<0)|
				(((uint32_t)spiBytes[1])<<8)|
			(((uint32_t)spiBytes[2])<<16)|
			(((uint32_t)spiBytes[3])<<24);
		*outError=spiBytes[4];
		return true;
	}else
	{
		*outCounter=0;
		*outError=0;
		return false;
	}
}


static void initializeCPU(AVR_simulator_t* ctx)
{
	ctx->PC=0;
	setSP(ctx, ADDR_SRAM+N_SRAM-1);
	ctx->cycle=0;
	for(uint32_t i=0;i<PROGMEM_N_WORDS; ++i)
	{
		commandExecuted[i]=false;
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
//if(!ok) {fflush(stdout); fflush(stderr); exit(1);}

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
	return getReg(ctx,17)!=0;
}
static void clearCounterError()
{
	setReg(ctx,17,0);
}

/// Test starting from all states with current incX settings. The initial counter value is set up by the function. Then a few cycles are executed and results are checked so all combinations occur at least once.
static void testFromAllStates(uint32_t initialCounter);
static void testNCycles(uint32_t nCycle, uint32_t initialCounter);
static void updatePins(AVR_simulator_t * ctx);
/// Initiate communication and read out counter and error values
static void testCommunication(uint32_t counterValue, uint8_t errorValue);

/// Initial counter values for test cases to test each overflow arrangements to happen correctly:
/// Overflow up, overflow down in each configuration
static uint32_t initialCounterValues[]={
	0x00000000, 0xFF000000, 0xFFFF0000, 0xFFFFFF00,0xFFFFFFFF, 0x00FFFFFF, 0x0000FFFF, 0x000000FF
};

/** Test all input order combinations in all phase */
static void testAllCombinations()
{
	for(inc0=-2;inc0<=2;++inc0)
	{
		for(inc1=-2;inc1<=2;++inc1)
		{
			for(inc2=-2;inc2<=2;++inc2)
			{
				for(int i=0;i<sizeof(initialCounterValues)/sizeof(uint32_t);++i)
				{
					testFromAllStates(initialCounterValues[i]);
				}
			}
		}
	}
}

int main (int argc, char ** argv)
{
	AVR_simulator_t ctx;
	initializeCPU(&ctx);
	beforeStart(&ctx);
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==0, "INITIALIZE COUNTER to 0");
	executeOneCycle(&ctx);
	inc0=1; inc1=1;inc2=1;
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==0, "increment is not counted on the same cycle when set up");
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==3, "increment 3");
	/*
	for(int i=0;i<1000;++i)
	{
		executeOneCycle(&ctx);
	}
	ASSERT(getCounterValue()==3003, "increment 3000");
	inc0=0; inc1=0;inc2=0;
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==3006, "increment 3 again");
	executeOneCycle(&ctx);
	ASSERT(getCounterValue()==3006, "Counting stopped");
	*/
	inc0=0; inc1=0;inc2=0;
	executeOneCycle(&ctx);
	setCounterValue(0);
	ASSERT(getCounterValue()==0, "Set counter value works");
	setCounterValue(0x12345678);
	ASSERT(getCounterValue()==0x12345678, "Set counter value works");
	setCounterValue(0);

	testAllCombinations();

	inc0=0; inc1=0;inc2=0;
	executeOneCycle(&ctx);	// Counter is stopped
	uint32_t counterValue=0x12345678;
	uint8_t errorValue=0;
	setCounterValue(counterValue);
	clearCounterError();
	testCommunication(counterValue, errorValue);	

	setCounterValue(0);
	clearCounterError();
	inc0=0; inc1=0;inc2=1;
	// Test reading out counter while counting
	testCommunication(2, 0);	// Counter is latched after two cycles
	ASSERT(getCounterValue()==N_CYCLE_SPI+27, "Counter value: %d required: %d", getCounterValue(), N_CYCLE_SPI+27);	// Readout test takes N_CYCLE_SPI+26 cycles
	for(uint32_t i=0;i<PROGMEM_N_WORDS;++i)
	{
		if((i>=CODE_ENDS&&i<0x100)||i>=0x200)
		{
			ASSERT_SILENT(!commandExecuted[i], "Unused command MUST NOT be executed at progmem index 0x%x", i);
		}else
		{
			ASSERT_SILENT(commandExecuted[i], "Command MUST BE executed at progmem index 0x%x", i);
		}
	}
	ASSERT(true, "Progmem coverage checked.");
	return error?1:0;
}
static void testCommunication(uint32_t counterValue, uint8_t errorValue)
{
	nChipSelect=0;
	updatePins(ctx);
	spiStart();
	bool spiReady=false;
	uint32_t counter=0;
	uint8_t error=0;
	for(uint32_t i=0;i<1000 && !spiReady;++i)
	{
		executeOneCycle(ctx);
		spiReady=spiRead(&counter, &error);
		if(spiReady)
		{
			ASSERT(i==N_CYCLE_SPI, "SPI data out takes %d cycles. Actual: %d", N_CYCLE_SPI, i);
		}
	}
	ASSERT(spiReady, "SPI readout happened before timeout.");
	ASSERT(counter==counterValue, "Counter value read correctly. Expected: %u (%x) value: %u (%x)", counterValue, counterValue, counter, counter);
	ASSERT(error==errorValue, "Error value read correctly. Expected: %u value: %u", errorValue, error);
	ASSERT(getReg(ctx, 24)==COMM_STATE_BYTESHIFT_DATA_END, "Communication state is COMM_STATE_BYTESHIFT_DATA_END Actual: 0x%x", getReg(ctx, 24));
	for(uint8_t i=0;i<17;++i)
	{
		executeOneCycle(ctx);
	}
	ASSERT(getReg(ctx, 24)==COMM_STATE_FINISHED, "Communication state is COMM_STATE_FINISHED 0x%x", getReg(ctx, 24));
	for(uint32_t i=0;i<5;++i)
	{
		executeOneCycle(ctx);
		ASSERT(getIO(ctx, DDRB)==0, "DDRB is turned off after communication + 2 cycles (%d)", i);
		ASSERT(getReg(ctx, 24)==COMM_STATE_FINISHED, "Communication state is COMM_STATE_FINISHED 0x%x (%d)", getReg(ctx, 24), i);
	}
	nChipSelect=N_CS_MASK;
	updatePins(ctx);
	for(uint32_t i=0;i<5;++i)
	{
		executeOneCycle(ctx);
		ASSERT(getReg(ctx, 24)==COMM_STATE_OFF, "1Communication state is off after communication and chip selectput to high 0x%x 0x%x (%d)", getReg(ctx, 24), getIO(ctx, PINB), i);
	}
	spiEnd();
}

static void testNCycles(uint32_t nCycle, uint32_t initialCounter)
{
	executeOneCycle(ctx);	// First is not affected by the current setting but the previous.
	executeOneCycle(ctx);	// Second is affected - errors may be raised here
	clearCounterError();
	setCounterValue(initialCounter);
	int32_t v=initialCounter;
	bool problem=inc0<-1||inc0>1||inc1<-1||inc1>1||inc2<-1||inc2>1;
//	logJump=true;
	for(uint32_t i=0;i<nCycle;++i)
	{
		executeOneCycle(ctx);
		if(!problem)
		{
			v+=inc0+inc1+inc2;
		}
		bool counterError=getCounterError();
		ASSERT_SILENT(counterError==problem, problem?"Problem samples raise error %s %d %d %d":"NO PROBLEM %s %d %d %d", counterError?"true":"false", inc0, inc1, inc2);
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
	setIO(ctx, PINB, signalAB|nChipSelect);
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
	if(spiOn)
	{
		uint8_t portb=getIO(ctx, PORTB);
		uint8_t ddrb=getIO(ctx, DDRB);
		bool spiClk=((portb&MASK_CLK)==0) && ((ddrb&MASK_CLK)!=0);
		if(!spiPrevClk && spiClk)
		{
			ASSERT_SILENT((ddrb&MASK_DATA)!=0, "DATA is driven when CLK is changed");
			bool bit=(portb&MASK_DATA)!=0;
			spiCurr>>=1;
			if(bit)
			{
				spiCurr|=0b10000000;
			}
			spiNbits++;
			if(spiNbits>7 && spiNChars<SPI_BUFFER_SIZE)
			{
				spiNbits=0;
				spiBytes[spiNChars]=spiCurr;
				spiNChars++;
			}
//			spiBytes[];
		}
		spiPrevClk=spiClk;
	}
	uint64_t cycle=ctx->cycle;
	if(pc==loop)
	{
		loopLabelTouched=true;
		ctx->breakpointActivated=true;
	}
#define CHECK(X) if(pc==X){printf("AT: " #X "\n");}
	if(pc==process3samples_ijmp)
	{
		uint32_t v=getCounterValue();
		uint8_t zl=getReg(ctx, 30);
		if(logJump)
		{
		printf("PATTERN: %c%c->%c%c->%c%c->%c%c %d\n", 
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
			logJump=false;
		}
	}
//	uint16_t currentCommand=progMemContent[pc];

	// Trace sampling periods counted in cycles
	static bool initialized=false;
	if(pc==process3samples)
	{
		initialized=true;
	}
	static uint32_t prevSampleCycle=0;

	if(pc==loop || pc==sample1 || pc==sample2)
	{
		if(initialized)
		{
			uint64_t diff=cycle-prevSampleCycle;
			ASSERT_SILENT(diff==12, "Sampling cycles: %lu instead of 12\n", diff);
		}
		prevSampleCycle=cycle;
		if(pc==loop)
		{
			incrementSample(ctx, inc0);
		}
		if(pc==sample1)
		{
			incrementSample(ctx, inc1);
		}
		if(pc==sample2)
		{
			incrementSample(ctx, inc2);
		}
	}
}

