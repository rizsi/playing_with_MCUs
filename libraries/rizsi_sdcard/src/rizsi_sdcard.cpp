#include <Arduino.h>

#include <rizsi_sdcard.h>

uint8_t sdInit()
{
return 0;
}

uint8_t sdWriteBlock(uint32_t blockIndex, sdBlockReader reader, void * param)
{
return 0;
}

uint8_t sdReadBlock(uint32_t blockIndex, sdBlockWriter writer, void * param)
{
for(int i=0;i<512;++i)
{
	writer(param, 0);
}
return 0;
}
