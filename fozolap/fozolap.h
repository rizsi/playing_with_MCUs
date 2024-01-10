#include <stdint.h>


/**
 * This must be called first.
 * Initializes all state of the GUI.
 */
void gui_init();
/**
 * This must be called after init but before looping.
 * Initializes all state of the GUI.
 */
void gui_setup();

/**
 * This must called in an endless loop by the main program.
 * @param currentTimeMillis
 */
void gui_loop(uint32_t currentTimeMillis);



