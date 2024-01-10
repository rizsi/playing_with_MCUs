#include <bsp.h>
#include <fozolap.h>
#include <stdio.h>

void gui_init()
{
}

void gui_setup()
{
}

static uint8_t prev0=0;
static uint8_t state0=0;
static uint8_t prev1=0;
static uint8_t state1=0;
static uint8_t fel1=0;

#define STEP 5
void gui_loop(uint32_t currentTimeMillis)
{
	uint8_t button0=getButtonState(0);
	if( button0 == 1 && prev0!=1)
	{
	  if(state0==0)
	  {
	  	state0=1;
	  	setPower(0,255);
	  }else
	  {
	  	state0=0;
	  	setPower(0,0);
	  }
	}
	prev0=button0;

	uint8_t button1=getButtonState(1);
	if(!button1 && prev1)
	{
		fel1=!fel1;
  	printf("FEL: %d\n",fel1);
	}
	if(button1!=0)
	{
	  if(fel1)
	  {
			state1+=STEP;
			if(state1<STEP) state1=255;
		}else
		{
			state1-=STEP;
			if(state1>255-STEP) state1=0;
		}
	}
	setPower(1,state1);
	prev1=button1;
}


