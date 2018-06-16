
#ifndef RIZSI_TWI_H
#define RIZSI_TWI_H

#define TWI_WRITE_ADDRESS 0B00000000
#define TWI_READ_ADDRESS 0B00000001

/**
 * Callback method to provide TWI task to the IT callback based tWI communicator.
 * @param address NULL means there was an error and send was cancelled
*/
typedef uint8_t (*twiFillCommand)(uint8_t * address, uint8_t ** getData, uint8_t *command);

extern void twiInit();
extern void twiStop();
extern void twiEndTransmission();
/// @param sla - slave address without shifting left one and write bit cleared
extern void twiBeginTransmission(uint8_t sla);
/// @param sla - slave address without shifting left one and read bit set
extern void twiBeginRead(uint8_t sla);
extern void twiWrite(uint8_t data);
/// Read 1 byte of data
/// @param lastByte means this is the last byte of the transfer so ask for an acknowledgement from the
/// slave
/// @return lo8 is the data read, hi8 is error (0 means ok)
extern uint16_t twiRead(uint8_t lastByte);
extern void twiBulkData(twiFillCommand feed);

#endif // RIZSI_TWI_H