#include <Arduino.h>
#include <rizsi_sdcard.h>
#include <rizsi_logger.h>

uint8_t lctr;
static char pattern[]="// Log";
uint8_t * logger_buffer;
static uint32_t currentBlock;
static uint32_t ptrWithinBlock;

static uint8_t logger_block_unused;
static uint16_t logger_ptr;
uint8_t loggerDataProvider(void * param)
{
	return logger_buffer[logger_ptr++];
}
void loggerReader(uint8_t data, void * param)
{
	logger_buffer[logger_ptr++]=data;
}
void loggerUsedBlockChecker(uint8_t data, void* param)
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
	}
	logger_ptr++;
}
void logger_clear_buffer(uint8_t data)
{
	logger_ptr=0;
	for(int i=0;i<SD_BLOCK_SIZE-1;++i)
	{
		logger_buffer[i]=data;
	}
	logger_ptr=0;
}

void loggerSetup(uint8_t* buffer, uint16_t bufferSize)
{
	if(bufferSize<SD_BLOCK_SIZE)
	{
		return;
	}
	logger_buffer=buffer;
	sdInit();
	uint32_t i=0;
	for(i=0;;++i)
	{
		logger_ptr=0;
		sdReadBlock(i, loggerUsedBlockChecker, NULL);
		if(logger_block_unused)
		{
			break;
		}
	}
	currentBlock=i;
	ptrWithinBlock=0;
	logger_buffer=NULL;
}

void loggerLoop(uint8_t* buffer, uint16_t bufferSize, logContentProvider p, uint16_t requiredLength)
{
	if(bufferSize<SD_BLOCK_SIZE)
	{
		return;
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
		logger_clear_buffer(' ');
		ptrWithinBlock+=sprintf((char *)buffer, "%s\n", pattern);
		logger_buffer[SD_BLOCK_SIZE-1]='\n';
	}else
	{
		// Current block is not empty - load the current block
		logger_ptr=0;
		sdReadBlock(currentBlock, loggerReader, NULL);
	}
	ptrWithinBlock+=p(buffer+ptrWithinBlock, SD_BLOCK_SIZE-ptrWithinBlock);
	logger_ptr=0;
	sdWriteBlock(currentBlock, loggerDataProvider, NULL);
	logger_buffer=NULL;
}
