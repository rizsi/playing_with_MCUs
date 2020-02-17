#include <stdio.h>
#include <stdint.h>
#include <emscripten.h>

#include <lathe_gui.h>
#include <bsp.h>

static uint64_t currentTimeMillis=0;


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
void setInput(uint8_t index, int32_t value)
{
	gui_updateInput(index, value, 0);
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
}

