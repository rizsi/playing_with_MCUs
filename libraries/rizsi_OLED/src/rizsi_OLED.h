/**
 * Configure OLED library. Must be called before anything else.
 */
extern void oledInit();

/**
 * Do initialization self-test sequence that shows the user
 * that all pixels work.
 *
 * Must be called before drawing frames.
 *
 * After the self-test sequence normal usage setup is applied.
 */
extern void oledTest();


/**
 * Query whether the last frame is already written to the device.
 * 
 * (Befure the first frame is sent it also returns true.)
 * @return true means that the last frame is written to the device.
 */
extern bool oledFinished();

/**
 * Send current content of the draw buffer to the display.
 * Data transfer is done in the background by I2C interrupts.
 * Result can be polled using oledFinished();
 * Until oledFinished the frame buffer must not be touched in order to
 * have a correct result on the screen.
 */
extern void oledData(const uint8_t * data);

