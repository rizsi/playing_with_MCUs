#include <bsp.h>
#include <fozolap.h>
#include <stdio.h>

void gui_init()
{
}

void gui_setup()
{
}

static uint8_t prev[2]={0};
static uint8_t state[2]={0};
static uint8_t fel[2]={1,1};

#define STEP 10
void gui_loop(uint32_t currentTimeMillis)
{
	for(uint8_t i=0;i<2;++i)
	{
		uint8_t button=getButtonState(i);
		if(!button && prev[i])
		{
			fel[i]=!fel[i];
			printf("FEL: %d\n",fel[i]);
		}
		if(button!=0)
		{
			if(fel[i])
			{
				state[i]+=STEP;
				if(state[i]<STEP) state[i]=255;
			}else
			{
				state[i]-=STEP;
				if(state[i]>255-STEP) state[i]=0;
			}
		}
		setPower(i,state[i]);
		prev[i]=button;
	}
}


