/**
 * Initialize One Wire library.
 * Must be called once before averything else.
 * Pin is configured by the configure_onewire.h header.
 */
void owInit();

/**
 * Is last query finished? True may mean error code!
 * When true a new query can be started.
 * After init this return true and there is an error code
 */
bool owReady();

/**
 * Was the last query a thermo query and did it finish without errors?
 */
bool owIsThermoReady();

/**
 * Was the last query a ROM id query and did it finish without errors?
 */
bool owIsROMReady();


/**
 * Get the last read T value. Celsius multiplied by 16.
 * Valid to call if owIsThermoReady();
 */
int16_t owGetTM16();

/**
 * Start a thermo read sequence. After about 1s the result is available.
 * Valid to call id owReady();
 */
void owReadThermo();

/**
 * Get the current error code of the OW state.
 * @return negative numbers sign an error
 */
int8_t owErrorCode();


