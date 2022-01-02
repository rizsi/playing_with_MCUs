
#ifndef RIZSI_TWI_H
#define RIZSI_TWI_H

#define TWI_WRITE_ADDRESS 0B00000000
#define TWI_READ_ADDRESS 0B00000001

/**
 * Callback method to provide TWI task to the IT callback based tWI communicator.
 * @param address the address has to be set by the callee
 * @param getData the pointer to the data to send is set by the callee
 * @param command the command to send - this is the first byte to be sent
 
  NULL parameters means there was an error and send was cancelled
*/
typedef uint8_t (*twiFillCommand)(uint8_t * address, const uint8_t ** getData, uint8_t *command);

/** Initialize TWI hardware. */
extern void twiInit();
/** Stop all activity and Uninitialize TWI hardware. */
extern void twiStop();
/** Same as twiStop */
extern void twiEndTransmission();
/// @param sla - slave address without shifting left one and write bit cleared
extern uint8_t twiBeginTransmission(uint8_t sla);
/// @param sla - slave address without shifting left one and read bit set
// extern uint8_t twiBeginRead(uint8_t sla);
/// Send a byte using TWI
extern uint8_t twiWrite(uint8_t data);
/// Read 1 byte of data
/// @param lastByte means this is the last byte of the transfer so ask for an acknowledgement from the
/// slave
/// @return lo8 is the data read, hi8 is error (0 means ok)
//extern uint16_t twiRead(uint8_t lastByte);
/// Send data using the callback interface. The callback will be called from interrupt context.
extern void twiBulkData(twiFillCommand feed);

#endif // RIZSI_TWI_H
