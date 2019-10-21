// Platform independent One Wire implementation

#include <onewire_bsp.h>
#include <onewire.h>

#define T_INVALID 0b1000000000000000

// Max conversion time:
// R1 R0 (configuration bits)
// 0  0  9 bits 93.75ms
// 0  1  10 bits 187.5ms
// 1  0  11 bits 375ms
// 1  1  12 bits 750 ms

// Reset: ~1ms
// command: 60-100 uS/bit -> ~1ms / byte
// Receive: 65 us/bit -> ~1ms / byte
// Konfig+konvert:
// reset+8 bájt küld+8 bájt fogad -> ~17ms


// Interface used: (may be functions or macros)

// Pull the OW interface to low
// #define BSP_OW_LOW()  asm("nop")
// Release OW and apply pullup resistor on OW
// #define BSP_OW_PULLUP()  asm("nop")
// Read current state of OW: LOW:0 HIGH:1
// #define BSP_OW_READ() asm("nop")
// delayMicroseconds - wait for the given microseconds


#define MAX_RETRY 3

/**
 * Count CRC
 * @param crc Current state of crc. Must be started from 0 and then always pass the previous value.
 * @param data the new data to ctc
 * @return the crc value of the data processed until now
 */
static uint8_t owireCRC(uint8_t crc, uint8_t data)
{
  for(uint8_t i=0;i<8;++i)
  {
    uint8_t lsbXdataBit=(data&1)^(crc&1);
    crc=(crc>>1) | (crc<<7); // rotate 1 right
    if(lsbXdataBit)
    {
      crc^=0b00001100;
    }
    if(data&1)
    {
      crc^=0b10000000;
    }
    data>>=1;
  }
  return crc;
}

/**
 * Send a single byte (not including reset cycle)
 */
static void owireSend(uint8_t data)
{
  for(int i=0;i<8;++i)
  {
    if(data&0x01)
    {
	CLI_BLOCK()
	{
		BSP_OW_LOW();
		owDelayMicroseconds(6); // 1<T<15 us
	        BSP_OW_HIGH();
	}
      owDelayMicroseconds(64); // Wait for the whole timeframe
    }
    else
    {
	BSP_OW_LOW();
      owDelayMicroseconds(60); // 60<T<120 us
        BSP_OW_HIGH();
      owDelayMicroseconds(10); // Recovery 1us<T
    }
    data>>=1;
  }
}

/**
 * Receive a single bit on a one wire interface.
 */
static uint8_t owireReceiveBit()
{
	uint8_t sample;
	CLI_BLOCK()
	{
		BSP_OW_LOW();
//		asm("nop");
//	asm("nop");
//	asm("nop");
//	asm("nop");
//	asm("nop");
//	asm("nop");
		owDelayMicroseconds(1); // 1<T<15 us
		BSP_OW_PULLUP();
		owDelayMicroseconds(3); // 1<T<15 us
		sample=BSP_OW_READ();
		owDelayMicroseconds(60); // T>45us
		BSP_OW_HIGH(); // Parasitic power is on
	}

//	asm("nop");
//	asm("nop");
//	asm("nop");

//	DEBUG_PIN_SIGNAL(1);   
//    owDelayMicroseconds(3); //  9+15
//    owDelayMicroseconds(24); //  9+15
//	DEBUG_PIN_SIGNAL(0);    
/*	if(sample)
	{
		BSP_OW_LOG_CH('H');
	}else
	{
		BSP_OW_LOG_CH('L');
	}
*/
  return sample;
}

/**
 * Receive a byte on the OW interface.
 */
static uint8_t owireReceive()
{
  uint8_t ret=0;
  for(int i=0;i<8;++i)
  {
    uint8_t sample=owireReceiveBit();
    ret>>=1;
    ret|=((sample!=0)?(uint8_t)0x80:0);
  }
  return ret;
}

/**
 * Receive N bytes in sequence. Check that the crc is fine.
 * @return true if crc is ok
 */
static bool owireReceiveBytes(uint8_t * tgBuffer, uint8_t nByte)
{
//    BSP_OW_LOG_NUM((uint16_t)(uint8_t *)tgBuffer);
//    BSP_OW_LOG_NUM(nByte);
//  for(uint8_t i=0;i<nByte;++i)
//  {
//     tgBuffer[i]='a';
//  }
  for(uint8_t i=0;i<nByte;++i)
  {
     tgBuffer[i]=owireReceive();
  }
  uint8_t crc=owireCRC(0, 0);
  for(uint8_t i=0;i<nByte-1;++i)
  {
    crc=owireCRC(crc, tgBuffer[i]);
  }
   BSP_OW_LOG_CH('S');
	BSP_OW_LOG_NUM(SPL);
   BSP_OW_LOG_CH(' ');
	BSP_OW_LOG_NUM(crc);
	BSP_OW_LOG_CH('L');
    BSP_OW_LOG_CH(' ');
    BSP_OW_LOG_NUM(crc);
    BSP_OW_LOG_CH(' ');
    BSP_OW_LOG_NUM(tgBuffer[nByte-1]);
    BSP_OW_LOG_CH(' ');
    BSP_OW_LOG_NUM(nByte);
    BSP_OW_LOG_CH(' ');
	BSP_OW_LOG_CH('L');
  return crc==tgBuffer[nByte-1];
}

/**
 * @return true if there is at least one client on the line
 */
static bool owireReset()
{
  uint8_t presence;
  BSP_OW_LOW();
  owDelayMicroseconds(480);
  CLI_BLOCK()
  {
    BSP_OW_PULLUP();
    owDelayMicroseconds(70);
    presence=BSP_OW_READ();
  }
  owDelayMicroseconds(450);
  BSP_OW_HIGH(); // Parasitic power is on
  return !presence;
}


bool owInitialize()
{
	if(!owireReset())
	{
		return 0;
	}
	BSP_OW_LOG_CH('a');
	owireSend(0xCC);// Skip ROM command - we have only one sensor on the line.
	owireSend(0x4E); // Write scratchpad - Configure the device
	owireSend(0x0);
	owireSend(0x0);
	owireSend(0b01100000);
//	if(!owireReset())
//	{
//		return 0;
//	}
	BSP_OW_LOG_CH('b');
	return 1;
}
uint16_t owReadTemp()
{
	if(!owireReset())
	{
		return T_INVALID;
	}
	BSP_OW_LOG_CH('c');
	uint8_t retryCounter=0;
	while(retryCounter<MAX_RETRY)
	{
		retryCounter++;
		owireSend(0xCC);// Skip ROM command - we have only one sensor on the line.
		owireSend(0x44); // Convert temperature
		deepSleepConversionTime();
		if(!owireReset())
		{
			return T_INVALID;
		}
		BSP_OW_LOG_CH('d');
		owireSend(0xCC);// Skip ROM command - we have only one sensor on the line.
		owireSend(0xBE); // Read scratchpad
		uint8_t tlow, thigh;
		uint8_t crc=owireCRC(0,0);
		crc=owireCRC(crc, tlow=owireReceive());
		crc=owireCRC(crc, thigh=owireReceive());

		uint8_t current;
		crc=owireCRC(crc, current=owireReceive());
//		BSP_OW_LOG_CH('S');
//		BSP_OW_LOG_NUM(current);
//		BSP_OW_LOG_CH(' ');

		crc=owireCRC(crc, current=owireReceive());
//		BSP_OW_LOG_CH('S');
//		BSP_OW_LOG_NUM(current);
//		BSP_OW_LOG_CH(' ');
		crc=owireCRC(crc, current=owireReceive());
//		BSP_OW_LOG_CH('S');
//		BSP_OW_LOG_NUM(current);
//		BSP_OW_LOG_CH(' ');
		crc=owireCRC(crc, owireReceive());
		crc=owireCRC(crc, owireReceive());
		crc=owireCRC(crc, owireReceive());
		uint8_t crccheck=owireReceive();
		BSP_OW_LOG_CH('e');
		if(!owireReset())
		{
			return T_INVALID;
		}
		BSP_OW_LOG_CH('f');
		if(crc==crccheck)
		{
			  uint16_t data=thigh;
			  data<<=8;
			  data|=tlow;

			BSP_OW_LOG_CH('i');
			BSP_OW_LOG_NUM(crc);
			BSP_OW_LOG_CH(' ');
			BSP_OW_LOG_NUM(tlow);
			BSP_OW_LOG_CH(' ');
			BSP_OW_LOG_NUM(thigh);
			BSP_OW_LOG_CH('\n');
			return data;
		}
		BSP_OW_LOG_CH('g');
	}
	BSP_OW_LOG_CH('h');
	return T_INVALID;
}

static void clearAddress(uint8_t * address)
{
	for(uint8_t i=0;i<8;++i)
	{
		address[i]=0;
	}
}

void owReadROMAddress(uint8_t * address)
{
/*
	uint8_t toggle=0;
	while(1)
	{
		DEBUG_PIN_SIGNAL(1);
		toggle=!toggle;
		bool ok=owireReset();
		if(ok)
		{
//		DEBUG_PIN_SIGNAL(0);
			owireSend(0x33);// Read ROM address
//			_delay_ms(1);
			DEBUG_PIN_SIGNAL(0);
			owireReceiveBytes(address, 8);
		}
		BSP_OW_LOG_LN();
//		_delay_ms(1);
	}
*/
	if(!owireReset())
	{
		clearAddress(address);
		return;
	}
	owireSend(0x33);// Read ROM address
	if(owireReceiveBytes(address, 8))
	{
		BSP_OW_LOG_CH('O');
		BSP_OW_LOG_LN();
		return;
	}
	BSP_OW_LOG_CH('C');
	BSP_OW_LOG_LN();
	clearAddress(address);
	return ;
}


