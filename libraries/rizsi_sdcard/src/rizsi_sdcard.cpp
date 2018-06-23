#include <Arduino.h>

#include <rizsi_sdcard.h>
#include <SPI.h>
#include <Sd2Card.h>

Sd2Card card;

uint8_t sdInit(int _activatorPin)
{
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  return !card.init(SPI_HALF_SPEED, _activatorPin);
}

uint8_t sdWriteBlock(uint32_t blockIndex, sdBlockReader reader, void * param)
{
	return !card.writeBlock(blockIndex, reader, param);
}

uint8_t sdReadBlock(uint32_t blockIndex, sdBlockWriter writer, void * param)
{
	return !card.readBlock(blockIndex, writer, param);
}
