/**
 * Get the data to log.
 */
typedef uint16_t (*logContentProvider) (uint8_t * target, uint16_t sizeData);


/**
 * Initialize the logger library.
 */
void loggerSetup();

void logSetId(uint64_t logId);
uint64_t logGetId();

uint64_t logGetCurrentLength();
/**
 * @param buffer will be overwritten with temporary data. Must be at least 512 bytes.
 * @param sdChipSelectNegPin Where chip select of the SD card is found
 * @return return value 0 means no problem
 */
uint8_t loggerLoop(uint8_t* buffer, uint16_t bufferSize, logContentProvider p, uint16_t requiredLength, uint8_t sdChipSelectNegPin);

/// Simple log to Serial - do not use SRAM for string constants!
#ifdef __AVR__
#define PRINT(s) (rizsi_print((uint32_t)PSTR(s)))
#define PRINTLN(s) (rizsi_println((uint32_t)PSTR(s)))
#define SPRINT(s) (Serial.print(s))
#define SPRINTLN(s) (Serial.println(s))

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
