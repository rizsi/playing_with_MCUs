
/// Initialize hardware to communicate with the sensor
void sensor_init();

/// Poll latest values from the sensor
/// @param xyz result is stored in the xyz array in x, y, z order. Value may be overwritten even in case of error
/// @return true means error in reading value
bool sensor_poll(int16_t * xyz);

