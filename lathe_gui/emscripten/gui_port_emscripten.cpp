#include <stdio.h>
#include <stdint.h>
#include <emscripten.h>

#include <lathe_gui.h>
#include <bsp.h>

static uint64_t currentTimeMillis=0;

static uint8_t* dataCallback=NULL;
static int dataCallbackLength=0;
static bool dataCallbackDone=false;
static uint8_t fromHex(uint8_t ch);

uint32_t getCurrentTimeMillis()
{
	return (uint32_t)currentTimeMillis;
}


/// In order to emscripten work simply the JS interfacing functions have to use
/// C calling convention.
extern "C" {

int main(int argc, char ** argv) {
	gui_init();
	// After program is started (main returned) then this will be executed in JS
	emscripten_run_script("setTimeout(jsSetup, 50);");
}

void setup()
{
	gui_setup();
}
void loop()
{
	gui_loop((uint32_t)currentTimeMillis);
}
/**
 * Get the current segment values of a digit - called from JS to update the UI.
 * @param index of the digit
 * @return bitmask pattern of the 8 segment display
 */
uint8_t getSegmentValues(uint8_t index)
{
	if(index<sizeof(segmentValues))
	{
		return segmentValues[index];
	}
	return 0;
}

/**
 * Set the current input value of a sensor subsystem.
 * @param index of the sensor subsystem: 0 kereszt, 1 hossz
 * @param value
 */
void setInput(uint8_t index, int32_t value, int32_t zero, bool zeroed)
{
	gui_updateInput(index, value, 0, zero, zeroed);
}

void updateTime(uint64_t t)
{
	currentTimeMillis=t;
}
/**
 * The button was pressed. In simulated mode this is called from JS.
 * @param index of the button pressed
 */
void buttonPressed(uint8_t index)
{
	gui_buttonPressed(index);
}
void loadDataCallback(int32_t index, uint8_t v0, uint8_t v1)
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

