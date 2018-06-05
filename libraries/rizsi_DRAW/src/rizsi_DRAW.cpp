#include <Arduino.h>
#include <avr/pgmspace.h>
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
void RD_drawString(const char * str)
{
  char temp[3];
  uint8_t l=strlen(str);
  uint8_t prevl=0;
  while(l>0)
  {
    if(*str=='\n')
    {
      l--;
      str++;
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
      int j=0;
      for(j=0;j<CHAR_LENGTH;++j)
      {
        temp[j]=pgm_read_byte_near(values+i*CHAR_LENGTH+j);
      }
      temp[j]=0;
      uint8_t lc=pgm_read_byte_near(char_lengths+i);
      if(lc<3 && strncmp(str, temp, lc)==0)
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
        str+=lc;
      }
    }
  }
}

void RD_drawNumber(int32_t value, uint8_t base)
{
	char buffer[33];
	snprintf(buffer, 33, "%d", value);
	RD_drawString(buffer);
}
void RD_drawFloat(float value, uint8_t width, uint8_t precision)
{
	char buffer[33];
	snprintf(buffer, 33, "%.1f", value);
// TODO precision!
//	dtostrf(value, width, precision, buffer);
	RD_drawString(buffer);
}
void RD_drawFixPoint(uint32_t whole, uint32_t partial, uint8_t precision, bool neg)
{
	char buffer[33];
	char * b=buffer;
	if(neg)
	{
		*b='-';
		b++;
	}
//	itoa(whole,b,10);
	*b=',';
	b++;
//	itoa(partial,b,10);	
}




