#include <stdint.h>

#define NUMBER_DISPLAY_NDIGIT 6
#define NUMBER_DISPLAY_ALLBYTES (4*NUMBER_DISPLAY_NDIGIT+7)

#define EDIT_MEASURED_KERESZT 1
#define EDIT_MEASURED_HOSSZ 2
#define EDIT_UTKOZO_KERESZT 3
#define EDIT_UTKOZO_HOSSZ 4

typedef struct {
	uint8_t state; // 0:not active, 1:active
	int32_t value;
} utkozo_setup_t;

typedef struct {
	bool transistor; // Transistor is on?
	uint32_t at; // Timestamp when transistor was turned on
} utkozo_active_t;

extern utkozo_setup_t utkozo_setup[2];
extern utkozo_active_t utkozo_active;

extern uint8_t segmentValues[NUMBER_DISPLAY_ALLBYTES];
extern int32_t inputValues[2];
extern int32_t diffValues[2];
extern uint8_t mode; // 0:d (*2) 1:r


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

/**
 * This must be called from the main loop when a button was pressed.
 * @param index - index of the button pressed - see code for function of indexes
 */
void gui_buttonPressed(uint8_t index);

/**
 * This must be called from the main loop when the sensor subsystem
 * readout is updated.
 * Sets the current input value of a sensor subsystem.
 * @param index of the sensor subsystem: 0 kereszt, 1 hossz
 * @param value
 */
void gui_updateInput(uint8_t index, int32_t value);

/**
 * Show a number on a seven segment display.
 * @param target index of the target display
 * @param value to be shown on the display negative values light up the minus segment
 * @param dotMask bit mask the dot segment in these position is lighted up. 1<<n means n fractional digits
 */
void showNumber(uint8_t target, int32_t value, uint8_t dotMask);

/**
 * Set a decimal digit on a display.
 * @param target index of the number display
 * @param digitIndex index of the digit. 0 is right most digit
 * @param value decimal value to be shown on the digit. 0-9 are valid values. Other values turn all 7 segments off
 * @param dot boolean value true means the dot is lighted up
 */
void setDigit(uint8_t target, uint8_t digitIndex, uint8_t value, bool dot);

