#include <stdint.h>
#include <stdbool.h>


/** Initialize the one wire temp sensor.
	@return true if the sensor is present and properly initialized
 */
extern bool owInitialize();

/**
 * Read ROM address of the thermo sensor.
 * @param address area provided by caller to store the address
 * @return address is set to 0 if device is not present or crc is not ok
 */
void owReadROMAddress(uint8_t * address);

/**
 * Read temperature through the OW.
 * @return 0 means error. Other values are valid readings in their raw format.
 */
uint16_t owReadTemp();

