/**
 * Sd card block I/O API. Callback API makes it possible to not store the whole 512 bytes at once but generate it on the fly
 * when writing and process when reading.
 *
 * See: https://github.com/arduino-libraries/SD/blob/master/src/utility/SdInfo.h
 */


// Block size of the SD cards
#define SD_BLOCK_SIZE 512

// There is no card detected in the slot
#define SD_ERROR_NO_CARD 1

/**
 * Get the next byte of the block.
 * @param param user defined parameter object that was passed to writeBlock.
 */
typedef uint8_t (*sdBlockReader) (void * param);

/**
 * The next byte read from the block.
 * @param param user defined parameter object that was passed to writeBlock.
 * @param data the data read from the SD card block
 */
typedef void (*sdBlockWriter) (uint8_t data, void * param);

/**
 * Initialize the SD card subsystem.
 * Does not communicate to the card yet only sets up the IO pins and initializes the internal data structures.
 */
uint8_t sdInit();

/**
 * Write a block of data to an SD card.
 *
 * This is a blocking call.
 * 
 * @param reader Will be called exactly 512 times to send each bytes of the block
 * @param param any user defined data that is passed to the reader
 * @return 0 - OK nonzero is an error code.
 */
uint8_t sdWriteBlock(uint32_t blockIndex, sdBlockReader reader, void * param);

/**
 * Read a block of data from an SD card.
 * 
 * This is a blocking call.
 *
 * @param writer Will be called exactly 512 times to receive each bytes of the block
 * @param param any user defined data that is passed to the writer
 * @return 0 - OK nonzero is an error code.
 */
uint8_t sdReadBlock(uint32_t blockIndex, sdBlockWriter writer, void * param);
