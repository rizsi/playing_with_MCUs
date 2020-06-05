#include <auto_watering.h>
#include <rizsi_DRAW.h>

#define GUIEV_REDRAW 0
#define GUIEV_BUTTON_DOWN 1
#define GUIEV_BUTTON_UP 2
#define GUIEV_BUTTON_PRESSED 3
#define GUIEV_LEAVE 4
#define GUIEV_ENTER 5

typedef void (*GUI_HANDLER) (uint8_t eventType, uint8_t eventParameter);

static void GUI_activateHandler(GUI_HANDLER handler);
static GUI_HANDLER currentHandler = NULL;

static void GUI_mainScreen(uint8_t ev, uint8_t p);
static void GUI_secondScreen(uint8_t ev, uint8_t p);


/// Framebuffer for OLED 128x64x1bit
static uint8_t frame[1024];
static int32_t counter=0;

void gui_init()
{
	RD_init(frame);
}
void gui_setup()
{
	GUI_activateHandler(GUI_mainScreen);
}
void gui_loop(uint32_t currentTimeMillis)
{
  currentHandler(GUIEV_REDRAW, 0);
}
void gui_buttonPressed(uint8_t index)
{
  currentHandler(GUIEV_BUTTON_PRESSED, index);
}
uint8_t * gui_getCurrentFrameBuffer()
{
	return frame;
}

static void GUI_mainScreen(uint8_t ev, uint8_t p)
{
  switch(ev)
  {
    case GUIEV_REDRAW:
      RD_clearScreen();
      RD_STRING("Öntöző\n");
      RD_drawNumber(counter, 10);
      counter++;
      break;
    case GUIEV_BUTTON_PRESSED:
      switch(p)
      {
       case 4:
        GUI_activateHandler(GUI_secondScreen);
        break;
      }
      break;
  }
}
static void GUI_secondScreen(uint8_t ev, uint8_t p)
{
  switch(ev)
  {
    case GUIEV_REDRAW:
      RD_clearScreen();
      RD_STRING("Öntöző második\n");
      RD_drawNumber(counter, 10);
      counter++;
      break;
    case GUIEV_BUTTON_PRESSED:
      switch(p)
      {
       case 4:
        GUI_activateHandler(GUI_mainScreen);
        break;
      }
      break;
  }
}


static void GUI_activateHandler(GUI_HANDLER handler)
{
	if(currentHandler!=NULL)
	{
		currentHandler(GUIEV_LEAVE, 0);
		currentHandler=NULL;
	}
	RD_clearScreen();
	currentHandler=handler;
	if(currentHandler!=NULL)
	{
		currentHandler(GUIEV_ENTER, 0);
	}
}

