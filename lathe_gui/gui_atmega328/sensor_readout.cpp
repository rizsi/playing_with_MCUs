
#include <receiver.h>

/**
 * Read out Quad sensor counter value.
 * If readout happens without error gui_updateInput is called with the value as parameter.
 * @return non-zero is error code.
 */
uint16_t sensor_readout(uint8_t sensorIndex)
{
	quad_receiver_t q;
	uint16_t err=quad_receive(sensorIndex, &q);
	if(err!=0)
	{
		// Error wait until the communication line is released by sender if communication has started.
		_delay_ms(2);
		return err;
	}
	sensor_readout_callback(sensorIndex, q.count, q.status, q.zero);
	return 0;
}

