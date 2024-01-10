#include <stdio.h>
#include <stdint.h>
#include <emscripten.h>

#include <fozolap.h>
#include <bsp.h>
#include <stdarg.h>

#define N_BUTTON 2

static uint64_t currentTimeMillis=0;

static uint8_t* dataCallback=NULL;
static int dataCallbackLength=0;
static bool dataCallbackDone=false;
static uint8_t fromHex(uint8_t ch);
static uint8_t s_buttonstate[N_BUTTON]={0};
static uint8_t s_power[N_BUTTON]={0};

static void js_printf(const char *format, ...) {
   va_list aptr;
   int ret;
	char buffer[1024];

   va_start(aptr, format);
   vsnprintf(buffer, 1024, format, aptr);
   va_end(aptr);
   printf("jsexec: %s\n", buffer);
   emscripten_run_script(buffer);
}

uint32_t getCurrentTimeMillis()
{
	return (uint32_t)currentTimeMillis;
}
uint8_t getButtonState(uint8_t index)
{
	if(index<N_BUTTON)
	{
		return s_buttonstate[index];
	}else return 0;
}
void setPower(uint8_t index, uint8_t power)
{
if(index<N_BUTTON)
{
 if(s_power[index]!=power)
 {
 	s_power[index]=power;
				printf("Set power %d %d\n", index, power);
				js_printf("document.getElementById('tuzhelyout%d').style='background-color: #%02x0000;';", index, power);
 }
				}
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

void updateTime(uint64_t t)
{
	currentTimeMillis=t;
}
/**
 * The button was pressed. In simulated mode this is called from JS.
 * @param index of the button pressed
 */
void buttonPressed(uint8_t state, uint8_t index)
{
		printf("Button %d %d\n", index, state);
	if(index<N_BUTTON)
	{	s_buttonstate[index]=state; }
}
}

