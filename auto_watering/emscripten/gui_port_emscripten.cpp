#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten.h>

#include <auto_watering.h>

/// Exported functions are available in JS
#define EMSCRIPTEN_EXPORT EMSCRIPTEN_KEEPALIVE

static uint64_t currentTimeMillis=0;

static uint8_t* dataCallback=NULL;
static int dataCallbackLength=0;
static bool dataCallbackDone=false;
static uint8_t fromHex(uint8_t ch);

static uint8_t state=0;

uint32_t getCurrentTimeMillis()
{
	return (uint32_t)currentTimeMillis;
}


/// In order to emscripten work simply the JS interfacing functions have to use
/// C calling convention.
extern "C" {

/// Draw the current screen into the canves buffer
void EMSCRIPTEN_EXPORT render(uint32_t width, uint32_t height, uint32_t * canvasRGB)
{
   state++;
   for (int y = 0; y < height; y++) {
     int yw = y * width;
     for (int x = 0; x < height; x++) {
       canvasRGB[yw + x] = (255 << 24) | state; // ABGR
     }
   }


	uint8_t * src=gui_getCurrentFrameBuffer();

   for (int y = 0; y < height; y++) {
     int yw = y * width;
     for (int x = 0; x < width; x++) {
	uint8_t b=src[(y/8)*128+x];
//	b=0b01010101;
	uint32_t col=(255 << 24) | (((b>>(y%8))&1)==1?0xFF00:0);  // ABGR
//	col=0xff00ff00|((y%8)*32);
       canvasRGB[yw + x] = col;
     }
   }

	// TODO implement resize
}

int EMSCRIPTEN_EXPORT main(int argc, char ** argv) {
	gui_init();
	// After program is started (main returned) then this will be executed in JS
	emscripten_run_script("setTimeout(jsSetup, 50);");
}

void EMSCRIPTEN_EXPORT setup()
{
	gui_setup();
}
void EMSCRIPTEN_EXPORT loop()
{
	gui_loop((uint32_t)currentTimeMillis);
}
void EMSCRIPTEN_EXPORT updateTime(uint64_t t)
{
	currentTimeMillis=t;
}
/**
 * The button was pressed. In simulated mode this is called from JS.
 * @param index of the button pressed
 */
void EMSCRIPTEN_EXPORT buttonPressed(uint8_t index)
{
	gui_buttonPressed(index);
}
void EMSCRIPTEN_EXPORT loadDataCallback(int32_t index, uint8_t v0, uint8_t v1)
{
	if(dataCallback!=NULL && index/2<dataCallbackLength)
	{
		dataCallback[index/2]=fromHex(v0)*16+fromHex(v1);
		if(index/2==dataCallbackLength-1)
		{
			dataCallbackDone=true;
		}
//		printf("%d %d -> %c", v0, v1, dataCallback[index/2]);
	}
//	printf("\n");
}
}

static uint8_t fromHex(uint8_t ch)
{
	if('0'<=ch && ch<='9')
	{
		return ch-'0';
	}else
	{
		return ch-'a'+10;
	}
}


static uint8_t toHex(uint8_t ch)
{
	if(ch<10)
	{
		return '0'+ch;
	}else
	{
		return 'a'+ch-10;
	}
}
void saveData(const uint8_t* data, uint8_t length)
{
	char formatted[512];
	for(uint8_t i=0;i<length;++i)
	{
		formatted[i*2]=toHex(data[i]/16);
		formatted[i*2+1]=toHex(data[i]%16);
	}
	char command[1024];
	sprintf(command, "saveData('%s');", formatted);
	emscripten_run_script(command);
}
bool loadData(uint8_t* data, uint8_t length)
{
	dataCallbackDone=false;
	dataCallback=data;
	dataCallbackLength=length;
	char command[1024];
	sprintf(command, "loadDataTrigger('%d');", length*2);
	emscripten_run_script(command);
	dataCallback=NULL;
	dataCallbackLength=0;
	return dataCallbackDone;
}

