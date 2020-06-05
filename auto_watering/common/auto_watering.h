#include <stdint.h>

extern void gui_init();
extern void gui_setup();
extern void gui_loop(uint32_t currentTimeMillis);
extern void gui_buttonPressed(uint8_t index);
extern uint8_t * gui_getCurrentFrameBuffer();
