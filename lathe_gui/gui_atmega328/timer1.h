
void initTimer1();

/**
 * @param must be smaller than 64000/8=8000; Must be at least a few millisecs so timeout does not happen while setting it up.
 */
void timer1_setupTimeout(uint16_t timeoutMillis);
bool timer1_isTimeout();
void timer1_cancelTimeout();


