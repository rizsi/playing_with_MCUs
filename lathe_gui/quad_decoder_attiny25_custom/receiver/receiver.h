#include <stdint.h>
typedef struct
{
	union{
		uint32_t count;
		uint8_t count_bytes[4];
	};
	uint8_t status;
	union{
		uint32_t zero;
		uint8_t zero_bytes[4];
	};
} quad_receiver_t;

/**
 * @return error code - 0 means ok
 */
extern uint16_t quad_receive(uint8_t index, quad_receiver_t * ret);

