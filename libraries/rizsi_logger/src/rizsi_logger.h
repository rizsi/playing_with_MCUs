
#define LOGGER_HEADER_SIZE (16+1+7)

/**
 * Get the data to log. Callback function called by the logger subsystem on the fly while writing the log
 * to the SD card. Implementation uses this callback so that the data may be generated on the fly
 * and not use further memory.
 * @param target copy the data into this buffer
 * @param sizeData the available size in the current block. Will be at least requiredLength in the loggerLoop call
 * @return the number of bytes written to the log
 */
typedef uint16_t (*logContentProvider) (uint8_t * target, uint16_t sizeData);


/**
 * Initialize the logger library.
 * Sane defaults in case of textual logging: block_unused_byte=' ' block_close_byte='\n'
 * Sane defaults in case of binary logging: block_unused_byte='\0' block_close_byte='\0'
 * 
 * @param block_unused_byte when opening a new block all unwritten data will be initialized with this byte
 * @param block_close_byte when opening a new block the last byte will be initialized with this byte
 */
void loggerSetup(uint8_t block_unused_byte, uint8_t block_close_byte);

void logSetId(uint64_t logId);
uint64_t logGetId();

uint64_t logGetCurrentLength();
uint8_t loggerLazyInit(uint8_t* buffer, uint16_t bufferSize, uint8_t sdChipSelectNegPin);
/**
 * Write a single block Onto the SD card.
 *
 * On first call after boot or logger subsystem reset the system is lazy inited: index of last written block is searched using binary search
 *
 * @param buffer will be overwritten with temporary data. Must be at least 512 bytes.
 * @param bufferSize size of the buffer checked for being at least 512
 * @param p callback that generated the data to be stored into the SD card data block.
 * @param requiredLength The number of bytes to be written into the logs. This number of bytes is appended to the current log block or
 *                       a new block is opened and data is written to the new block if necessary
 * @param sdChipSelectNegPin Where chip select of the SD card is found
 * @return return value 0 means no problem
 */
uint8_t loggerLoop(uint8_t* buffer, uint16_t bufferSize, logContentProvider p, uint16_t requiredLength, uint8_t sdChipSelectNegPin);

/// Simple log to Serial - do not use SRAM for string constants!
#ifdef __AVR__
#define PRINT(s) (rizsi_print((uint32_t)PSTR(s)))
#define PRINTLN(s) (rizsi_println((uint32_t)PSTR(s)))

//#define SPRINT(s) (Serial.print(s))
//#define SPRINTLN(s) (Serial.println(s))

#define SPRINT(s)
#define SPRINTLN(s)

void rizsi_print(uint32_t pgmPtr);
void rizsi_println(uint32_t pgmPtr);
#else
#define SPRINT(s) (rizsi_sprint(s))
#define SPRINTLN(s) (rizsi_sprintln(s))
#define PRINT(s) (rizsi_print(s))
#define PRINTLN(s) (rizsi_println(s))
void rizsi_print(const char * s);
void rizsi_println(const char * s);
void rizsi_sprint(uint32_t value);
void rizsi_sprintln(uint32_t value);
#endif
