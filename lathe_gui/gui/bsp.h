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


/**
 * Save current settings data to EEPROM.
 * @param data pointer to data
 * @param length length of data in bytes
 */
void saveData(const uint8_t* data, uint8_t length);
/**
 * Load current settings data from EEPROM.
 * @param data pointer to data
 * @param length length of data in bytes
 * @return true if there is a valid save file in the EEPROM
 */
bool loadData(uint8_t* data, uint8_t length);

