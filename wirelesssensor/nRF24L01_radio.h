
#define RADIO_MODE_SLEEP 0
#define RADIO_MODE_RECEIVE 1

#define RADIO_RET_RECEIVED 1
#define RADIO_RET_SENT 2

/**
 * Initialize the radio pins.
 */
extern void radioPinsInit();
/**
 * Initialize the radio chip and start in the selected mode.
 * @param mode the mode to set the radio to
 * @param messageSize size of the message to receive
 */
extern void radioSetup(uint8_t mode, uint8_t messageSize);

/**
 * Send a single packet through the radio.
 * The function returns immediately.
 * Must loop radioLoop so that the MCU receives the packet sent message from the radio chip and resets the radio state to modeAfter
 * @param data pointer to raw data to be sent
 * @param nByte number of bytes to send
 * @param modeAfter the selected mode after the package have been sent
 */
extern void radioSend(uint8_t * data, uint8_t nByte, uint8_t modeAfter);

/**
 * Read configuration and status data and print it through debug serial line.
 */
extern void radioReadData();
extern uint8_t radioReadStatus();
extern uint16_t radioFifoStatus();


/**
 * Loop execute radio code: check status and execute the necessary thing if something happened on the radio.
 * @return 
 */
extern uint8_t radioLoop();
/**
 * Loop execute radio code until the current message was sent and all status of the radio is properly set to the required modeAfter.
 * @return 
 */
extern void radioLoopUntilSent();

/**
 * This callback must be implemented by the user of the library.
 * @param data the data of the received message allocated on stack. Buffer is 33 bytes long and the last byte is always 0 independent of the content of the message.
 */
extern void radioReceiveCallback(uint8_t * data);

