#include <stdint.h>

extern void gui_init();
extern void gui_setup();
extern void gui_loop(uint32_t currentTimeMillis);
extern void gui_updateInput(uint8_t index, int32_t value, int32_t dummy, int32_t zero, bool zeroed);
extern void gui_buttonPressed(uint8_t index);
extern uint8_t * gui_getCurrentFrameBuffer();
