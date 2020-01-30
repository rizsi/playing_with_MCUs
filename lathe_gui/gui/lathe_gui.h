#include <stdint.h>


#define DIGITS_K_INDEX 0
#define DIGITS_K_N 6
#define DIGITS_H_INDEX 6
#define DIGITS_H_N 6
#define DIGITS_UTKOZO_K_INDEX 12
#define DIGITS_UTKOZO_K_N 6
#define DIGITS_UTKOZO_H_INDEX 18
#define DIGITS_UTKOZO_K_N 6

#define DIGIT_MODE_INDEX 24

#define DIGITS_END_INDEX 25

#define LED_INDEX_UTKOZO_K 25
#define LED_INDEX_UTKOZO_H 26
#define LED_INDEX_TRANSISTOR 27
#define LED_INDEX_K 28
#define LED_INDEX_H 29


#define NUMBER_DISPLAY_NDIGIT 6
#define NUMBER_DISPLAY_ALLBYTES (DIGITS_END_INDEX+7)

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

