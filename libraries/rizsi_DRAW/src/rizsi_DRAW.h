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
extern void RD_drawStringPgm(uint32_t pgmPtr);


#ifdef __AVR__
#define RD_STRING(s) (RD_drawStringPgm((uint32_t)PSTR(s)))
#else
#define RD_STRING(s) (RD_drawString(s))
#endif


extern void RD_drawNumber(int32_t value, uint8_t base);
extern void RD_drawNumber(int32_t value, uint8_t base, uint8_t minWidth);
extern void RD_drawFloat(float value, uint8_t wholeWidth, uint8_t precision);
extern uint8_t RD_formatFloat(char* buffer, uint8_t dtsSize, float value, uint8_t width, uint8_t precision);

extern uint8_t numToBuffer(char * tg, uint32_t n, uint8_t minWidth, uint8_t base);

/**
 * Set blink state to true/false. When true then all drawn characters are blinking.
 */
extern void RD_setBlink(uint8_t blink);


