#include <Arduino.h>

/**
 * Configure DRAW library. Must be called before anything else.
 * @param framebuffer 1024 bytes (128x64 mono pixels)
 */
extern void RD_init(uint8_t * framebuffer);

/**
 * Set all pixels in the frame buffer to dark (0 bit).
 * Executes a memset(...) on the framebuffer.
 * Also reset the current character pointer to 0,0
 */
extern void RD_clearScreen();

/**
 * Draw a string onto the screen.
 * Each character is looked up from the characters table. (UTF-8 characters are possible to handle.)
 * At the end of a line auto CR LF is applied.
 * \n is handled as CR LF
 */
extern void RD_drawString(const char * str);

extern void RD_drawNumber(int32_t value, uint8_t base);
extern void RD_drawFloat(float value, uint8_t wholeWidth, uint8_t precision);

/**
 * Set blink state to true/false. When true then all drawn characters are blinking.
 */
extern void RD_setBlink(uint8_t blink);


