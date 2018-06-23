#include <Arduino.h>
#include <avr/pgmspace.h>
#include <rizsi_DRAW.h>
#include "characters.h"

#define OLED_WIDTH 128

uint8_t * RD_frame;
uint8_t RD_charX=0;
uint8_t RD_charY=0;
uint8_t RD_blink=0;

void RD_init(uint8_t * framebuffer)
{
	RD_frame=framebuffer;
}
void RD_setBlink(uint8_t blink)
{
	RD_blink=blink&&((millis()%1000)<500);
}

void RD_clearScreen()
{
 for(int i=0;i<1024;++i)
 {
   RD_frame[i]=0; //B10101010;
 }
  RD_charX=0;
  RD_charY=0;
}
void RD_chechNextCharPosition()
{
  if(RD_charX+CHAR_WIDTH>OLED_WIDTH)
  {
    RD_charX=0;
    RD_charY++;
  }
}
/** Write to framebuffer but avoid overflow */
#define putFrame(index, value) if(((uint16_t)(index))<1024){RD_frame[(uint16_t)index]=value;}
#define getFrame(index) ((((uint16_t)(index))<1024)?RD_frame[(uint16_t)index]:0);

typedef char (*charGetter) (uint8_t at);

static uint8_t strncmppgm(charGetter get, uint8_t at, const PROGMEM uint8_t * ptr, uint8_t lc)
{
	for(uint8_t i=0;i<lc;++i)
	{
		char c0=get(at+i);
		char c1=pgm_read_byte_near(ptr+i);
		if(c0!=c1)
		{
			return c0-c1;
		}
	}
	return 0;
}

static void RD_drawString2(charGetter get, int l)
{
//  char temp[3];
  uint8_t at=0;
  uint8_t prevl=0;
  while(l>0)
  {
    if(get(at)=='\n')
    {
      l--;
      at++;
      RD_charY++;
      RD_charX=0;
      continue;
    }
    if(prevl==l)
    {
      return;
    }
    prevl=l;
    for(uint8_t i=0;i<N_CHARS;++i)
    {
//      int j=0;
//      for(j=0;j<CHAR_LENGTH;++j)
//      {
//        temp[j]=pgm_read_byte_near(values+i*CHAR_LENGTH+j);
//      }
//      temp[j]=0;
      uint8_t lc=pgm_read_byte_near(char_lengths+i);
      if(lc<3 && strncmppgm(get, at, values+i*CHAR_LENGTH, lc)==0)
      {
        RD_chechNextCharPosition();
	uint16_t ycoo=RD_charY*CHAR_HEIGHT;
	uint8_t displacement=ycoo%8;
	uint8_t bank=ycoo/8;
	uint32_t mask=(1<<CHAR_HEIGHT);
	mask-=1;
	mask<<=displacement;
        for(int j=0;j<CHAR_WIDTH;++j)
        {
		uint8_t d0=pgm_read_byte_near(pixels+i*CHAR_WIDTH*2+j*2);
		uint8_t d1=pgm_read_byte_near(pixels+i*CHAR_WIDTH*2+j*2+1);
		// uint16_t index=
		if(displacement==0)
		{
			if(!RD_blink)
			{
				  putFrame((128*(bank))+RD_charX, d1);
				  putFrame((128*(bank+1))+RD_charX, d0);
			}
		}else
		{
			uint32_t pattern=((uint16_t)d0<<8)|d1;
			pattern<<=displacement;
			uint8_t prev0=getFrame((128*(bank))+RD_charX);
			uint8_t prev1=getFrame((128*(bank+1))+RD_charX);
			uint8_t prev2=getFrame((128*(bank+2))+RD_charX);
			uint32_t v=prev0|((uint16_t)prev1<<8)|((uint32_t)prev2<<16);
			v&=~mask;
			v|=pattern;
			if(!RD_blink)
			{
				putFrame((128*(bank))+RD_charX, (uint8_t)v);
				putFrame((128*(bank+1))+RD_charX, (uint8_t)(v>>8));
				putFrame((128*(bank+2))+RD_charX, (uint8_t)(v>>16));
			}
		}
          RD_charX++;
        }
        i=N_CHARS;
        l-=lc;
        at+=lc;
      }
    }
  }
}


#ifdef __AVR__
static uint32_t strProgmemPtr;
uint16_t strlenpgm(uint32_t strPgm)
{
	for(uint16_t i=0;i<16000;++i)
	{
		if(pgm_read_byte_near(strPgm+i)==0)
		{
			return i;
		}
	}
	return 0;
}
char strGetterPgm(uint8_t ptr)
{
	return pgm_read_byte_near(strProgmemPtr+ptr);
}
void RD_drawStringPgm(uint32_t strPgm)
{
	strProgmemPtr=strPgm;
	RD_drawString2(strGetterPgm, strlenpgm(strPgm));
}
#endif


static const char * strPtr;
char strGetter(uint8_t ptr)
{
return strPtr[ptr];
}

void RD_drawString(const char * str)
{
	strPtr=str;
	RD_drawString2(strGetter, strlen(str));
}

char digitToChar(uint8_t digit, uint8_t base)
{
	if(digit<10)
	{
		return '0'+digit;
	}else
	{
		return 'A'+digit-10;
	}
}

uint8_t fillLeftToWidth(char * tg, uint8_t width, uint8_t reqWidth, char fill)
{
	if(width<reqWidth)
	{
		uint8_t diff=reqWidth-width;
		for(uint8_t i=1;i<=width;++i)
		{
			tg[reqWidth-i]=tg[width-i];
		}
		for(uint8_t i=0;i<diff;++i)
		{
			tg[i]=fill;
		}
		return diff;
	}
	return 0;
}

void reverseChars(char * tg, uint8_t length)
{
	uint8_t n=length/2;
	for(uint8_t i=0;i<n;++i)
	{
		uint8_t x=tg[i];
		tg[i]=tg[length-i-1];
		tg[length-i-1]=x;
	}
}

uint8_t numToBuffer(char * tg, uint32_t n, uint8_t minWidth, uint8_t base)
{
	uint8_t at=0;
	while(n>0)
	{
		uint8_t digit=n%base;
		tg[at]=digitToChar(digit, base);
		at++;
		n=n/base;
	}
	reverseChars(tg, at);
	at+=fillLeftToWidth(tg, at, minWidth, '0');
	return at;
}

void RD_drawNumber(int32_t value, uint8_t base)
{
	RD_drawNumber(value, base, 1);
}
void RD_drawNumber(int32_t value, uint8_t base, uint8_t minWidth)
{
	char buffer[33];
	uint8_t at=numToBuffer(buffer, value, 1, base);
	at+=fillLeftToWidth(buffer, at, minWidth, '0');
	buffer[at]='\0';
	RD_drawString(buffer);
}
uint8_t RD_formatFloat(char* buffer, uint8_t dtsSize, float value, uint8_t width, uint8_t precision)
{
	uint32_t partsMultiplier=10;
	for(int i=1;i<precision;++i)
	{
		partsMultiplier*=10;
	}
	uint8_t ptr=0;
	if(value<0)
	{
		buffer[0]='-';
		ptr++;
		value=-value;
	}
	uint32_t whole=(uint32_t)value;
	uint32_t part=(uint32_t)((value-whole)*partsMultiplier);
	ptr+=numToBuffer(&buffer[ptr], whole, width, 10);
	buffer[ptr]=',';
	ptr++;
	ptr+=numToBuffer(&buffer[ptr], part, precision, 10);
	buffer[ptr]='\0';
	return ptr;
}

void RD_drawFloat(float value, uint8_t width, uint8_t precision)
{
	char buffer[33];
	RD_formatFloat(buffer, 33, value, width, precision);
	RD_drawString(buffer);
}

