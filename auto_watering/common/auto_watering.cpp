#include <auto_watering.h>
#include <rizsi_DRAW.h>


/// Framebuffer for OLED 128x64x1bit
static uint8_t frame[1024];
static int32_t counter=0;

void gui_init()
{
	RD_init(frame);
}
void gui_setup()
{
}
void gui_loop(uint32_t currentTimeMillis)
{
  RD_clearScreen();
  RD_drawNumber(counter, 10);
  counter++;
}
void gui_updateInput(uint8_t index, int32_t value, int32_t dummy, int32_t zero, bool zeroed)
{
}
void gui_buttonPressed(uint8_t index)
{
}
uint8_t * gui_getCurrentFrameBuffer()
{
	return frame;
}

