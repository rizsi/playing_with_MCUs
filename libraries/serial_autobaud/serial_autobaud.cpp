// Auto calibrate serial baud rate on MCU's that don't have serial auto-calibration feature

// Calibration byte is S01010101s - all alternating signals 9 baud time
// Wait for down directing pin change
// count pin changes until 10(including the first start bit and first edge of the stop bit)
//  * Set up a timeout: if calibration fails then timeout and restart calibration logic
//  * if calibration worked:
// Validate:
//  * each signal is similar in time
//  * altogether time is about the required
//  * Time of start bit and last bit (both down edge) is used to count baud time
//  * Set up receiver with baud and use that to communicate.
//  * After communication go back to auto calibrate mode

// BAUD = Fosc/measuredticks
// BAUD = Fosc/(16*(UBRRn+1))
// measuredticks = (16*(UBRRn+1))
// UBRRn = measuredticks/16-1

// Divisor is about 2048. baud is about 3906

/// This is executed on pin change ISR
PINCHANGE_ISR()
{
 uint16_t t=TCNT1; // 16 bit time yeah
 diff=t-prevt;
 N=diff/2048;
 part=diff%2048;
 if(N>7<9)
 {
 	// calibration signal is 
 	// possible calibration value
 	// If there are no changes in the future then this was a calib value
 }
}

