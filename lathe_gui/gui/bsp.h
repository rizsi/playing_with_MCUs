/**
 * Board support package API of the Lathe GUI.
 * These are functions provided by HAL that are called by the
 * portable business logic of the program.
 */
#include <inttypes.h>
#include <stdbool.h>

/**
 * Get the current time in milliseconds since an arbitrary epoch.
 * (On uC epoch is power on, on PC epoch is Unix epoch)
 */
uint32_t getCurrentTimeMillis();

