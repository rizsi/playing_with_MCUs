
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
		// Error
		_delay_ms(2);
		return err;
	}
	sensor_readout_callback(sensorIndex, q.count, q.status, q.zero);
	_delay_ms(2);
	return 0;
}

