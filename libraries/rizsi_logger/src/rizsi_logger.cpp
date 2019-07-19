#include <Arduino.h>
#include <rizsi_sdcard.h>
#include <rizsi_logger.h>

// Pattern to define the used blocks
static char pattern[]="// Log ";

// This is a static limit. Should be read from SD card instead.
// 4GB (8388608*512=2^32)
#define MAX_BLOCK_INDEX 8388607
#define STATE_RESET 0xFFFFFFFF

#define ERR_FULL 1
#define ERR_BUFFER_SMALL 2
#define ERR_NO_ID 3
#define ERR_SD 4

// Buffer to write data to/read data from
static uint8_t * logger_buffer;
// Index of current block to write. 0xFFFFFFFF means the logger system is uninitialized
static uint32_t currentBlock;
static uint32_t ptrWithinBlock;
static uint64_t logId;

static uint8_t logger_block_unused;
static uint8_t logger_block_unused_byte;
static uint8_t logger_block_close_byte;
static uint16_t logger_ptr;


/// Reset the state of the logger - on init or on error.
static void loggerReset()
{
	currentBlock=STATE_RESET;
	ptrWithinBlock=0;
}


void logSetId(uint64_t logId_)
{
	logId=logId_;
	loggerReset();
}
uint64_t logGetId()
{
	return logId;
}

uint64_t logGetCurrentLength()
{
	if(currentBlock==STATE_RESET)
	{
		return 0;
	}
	return ((uint64_t)currentBlock)*SD_BLOCK_SIZE+ptrWithinBlock;
}

static uint8_t loggerDataProvider(void * param)
{
	return logger_buffer[logger_ptr++];
}
static void loggerReader(uint8_t data, void * param)
{
	if(logger_buffer!=NULL && logger_ptr<SD_BLOCK_SIZE)
	{
		logger_buffer[logger_ptr++]=data;
	}
}
static char toHexDigit(uint8_t digit)
{
	return digit<10?('0'+digit):('A'+digit-10);
}
static void loggerUsedBlockChecker(uint8_t data, void* param)
{
	if(logger_ptr==0)
	{
		logger_block_unused=0;
	}
	if(logger_ptr<sizeof(pattern)-1)
	{
		if(data!=pattern[logger_ptr])
		{
			logger_block_unused=1;
		}
	}else if(!logger_block_unused && logger_ptr<sizeof(pattern)-1+16)
	{
		uint8_t index=logger_ptr-sizeof(pattern)+1;
		// Hex digit of log id
		uint8_t digit=logId>>(4*index);
		digit&=0xf;
		char c=toHexDigit(digit);
		if(c!=data)
		{
			logger_block_unused=1;
		}
	}
	logger_ptr++;
}
static void logger_setup_buffer()
{
	logger_ptr=0;
	for(uint16_t i=0;i<SD_BLOCK_SIZE-1;++i)
	{
		logger_buffer[i]=logger_block_unused_byte;
	}
	ptrWithinBlock=0;
	for(;ptrWithinBlock<sizeof(pattern)-1;++ptrWithinBlock)
	{
		logger_buffer[ptrWithinBlock]=pattern[ptrWithinBlock];
	}
	for(uint8_t i=0;i<16;++i)
	{
		uint8_t digit=logId>>i*4;
		digit&=0xF;
		char c=toHexDigit(digit);
		logger_buffer[ptrWithinBlock+i]=c;
	}
	ptrWithinBlock+=16;
	logger_buffer[ptrWithinBlock]='\n';
	ptrWithinBlock+=1;
	logger_buffer[SD_BLOCK_SIZE-1]=logger_block_close_byte;
	
	logger_ptr=0;
}

void loggerSetup(uint8_t block_unused_byte, uint8_t block_close_byte)
{
	logger_block_unused_byte=block_unused_byte;
	logger_block_close_byte=block_close_byte;

	logId=0;
	logger_buffer=NULL;
	loggerReset();
}
uint8_t isUnused(uint32_t block)
{
	logger_ptr=0;
	uint8_t err=sdReadBlock(block, loggerUsedBlockChecker, NULL);
	if(err)
	{
		PRINTLN("ERR-READ block");
		return 2;
	}
	return logger_block_unused;
}

uint8_t loggerLazyInit(uint8_t* buffer, uint16_t bufferSize, uint8_t sdChipSelectNegPin)
{
	if(logId==0)
	{
		return ERR_NO_ID;
	}
	if(currentBlock==STATE_RESET)
	{
		if(sdInit(sdChipSelectNegPin))
		{
			PRINTLN("ERR SD INIT");
			loggerReset();
			return ERR_SD;
		}
		uint32_t min=0;
		uint32_t max=MAX_BLOCK_INDEX;
		while(min!=max)
		{
			uint32_t test=min+((max-min)/2);
			PRINT("Test block for emptiness:");
			SPRINT(min);
			PRINT(", ");
			SPRINT(max);
			PRINT(", ");
			SPRINTLN(test);
			uint8_t un=isUnused(test);
			if(un>1)
			{
				PRINTLN("ERR FIND NUSED");
				loggerReset();
				return ERR_SD;
			}
			else if(un)
			{
				max=test;
			}else
			{
				min=test+1;
			}
		}
		currentBlock=min;
		PRINT("First empty block found:");
		SPRINTLN(currentBlock);
		ptrWithinBlock=0;
	}
	if(currentBlock>=MAX_BLOCK_INDEX)
	{
		// Card is full
		return ERR_FULL;
	}
	return 0;
}

uint8_t loggerLoop(uint8_t* buffer, uint16_t bufferSize, logContentProvider p, uint16_t requiredLength, uint8_t sdChipSelectNegPin)
{
	uint8_t err=loggerLazyInit(buffer, bufferSize, sdChipSelectNegPin);
	if(err!=0)
	{
		return err;
	}
	if(bufferSize<SD_BLOCK_SIZE)
	{
		return ERR_BUFFER_SMALL;
	}
	logger_buffer=buffer;
	if(ptrWithinBlock+requiredLength>SD_BLOCK_SIZE)
	{
		// New block required!
		ptrWithinBlock=0;
		currentBlock++;
	}
	if(ptrWithinBlock==0)
	{
		// Current block is empty - create a marker header
		logger_setup_buffer();
	}else
	{
		// Current block is not empty - load the current block
		logger_ptr=0;
		if(sdReadBlock(currentBlock, loggerReader, NULL))
		{
			PRINTLN("ERR READ BLOCK");
			loggerReset();
			return ERR_SD;
		}
	}
	ptrWithinBlock+=p(buffer+ptrWithinBlock, SD_BLOCK_SIZE-ptrWithinBlock);
	logger_ptr=0;
	if(sdWriteBlock(currentBlock, loggerDataProvider, NULL))
	{
		PRINTLN("ERR WRITE BLOCK");
		loggerReset();
		return ERR_SD;
	}
	logger_buffer=NULL;
	return 0;
}


#ifdef __AVR__

void rizsi_println(uint32_t ptr)
{
	rizsi_print(ptr);
//	Serial.println();
}
void rizsi_print(uint32_t ptr)
{
	char ch=pgm_read_byte(ptr);
	while(ch !=0)
	{
//		Serial.print(ch);
		ptr++;
		ch=pgm_read_byte(ptr);
	}
}
#endif
