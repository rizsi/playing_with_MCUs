
/**
 * Get the data to log.
 */
typedef uint16_t (*logContentProvider) (uint8_t * target, uint16_t sizeData);


/**
 * @param buffer will be overwritten with temporary data. Must be at least 512 bytes.
 */
void loggerSetup(uint8_t* buffer, uint16_t bufferSize);

/**
 * @param buffer will be overwritten with temporary data. Must be at least 512 bytes.
 */
void loggerLoop(uint8_t* buffer, uint16_t bufferSize, logContentProvider p, uint16_t requiredLength);
