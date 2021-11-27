
// Sensor handling of accelerometer and gyroscope used for the balancer robot project

// SDA, SCL: Sensor https://www.sparkfun.com/products/retired/10724 ADXL345 and ITG-3200


#include <avr/io.h>
#include <stdint.h>
#include <debug_uart0.h>
#include <util/delay.h>
#include <util/twi.h>

// Read address of the accelerometer ADXL345
// #define ACC_ADDR 0x3A
#define ACC_ADDR 0xA6

// Retry iterations in case of retriable error in communication
#define MAX_ITER 10

/* send start condition, wait for transmission, accept start, goto begin or return true in case of error */
#define TWI_START()   TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);  \
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */ \
  switch ((twst = TW_STATUS)) \
    { \
    case TW_REP_START:		/* OK, but should not happen */ \
    case TW_START: \
      break; \
    case TW_MT_ARB_LOST:	/* Note [9] */ \
      goto begin; \
    default: \
      return -1;		/* error: not in start condition */ \
				/* NB: do /not/ send stop condition */ \
    }

/* send re-start condition */
#define TWI_RESTART()   TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);  \
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */ \
  switch ((twst = TW_STATUS)) \
    { \
    case TW_REP_START:		/* OK, but should not happen */ \
    case TW_START: \
      break; \
    case TW_MT_ARB_LOST:	/* Note [9] */ \
      goto begin; \
    default: \
      rv=-2; \
      goto error;		/* error: send stop condition in case of error */ \
    }

#define TWI_SEND(VALUE, ONNACK)   TWDR = VALUE; \
  TWCR = _BV(TWINT) | _BV(TWEN); /* clear interrupt to start transmission */ \
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */ \
  switch ((twst = TW_STATUS)) \
    { \
    case TW_MT_SLA_ACK: \
    case TW_MR_SLA_ACK: \
    case TW_MT_DATA_ACK: \
      break; \
    case TW_MT_DATA_NACK: \
    case TW_MR_SLA_NACK: \
    case TW_MT_SLA_NACK:	/* nack during select: device busy writing */ \
				/* Note [11] */ \
      goto ONNACK; \
    case TW_MT_ARB_LOST:	/* re-arbitrate */ \
      goto begin; \
    default: \
      UART0_Send('F'); \
      UART0_Send_uint32(twst); \
      UART0_Send('U'); \
      rv=-3; \
      goto error;		/* must send stop condition */ \
    }


/// Initialize TWI bus hardware registers
static void twi_init()
{
	TWSR = 0;	// No prescaler
	TWBR = 70;	// divider
	// FCPU/(16+2(TWBR)*(PrescalerValue)) = 103kHz
}


/// Read n data bytes from slave device
/// @return number of bytes read or negative means error
static int8_t twi_read(uint8_t sla, uint8_t reg, uint8_t n, uint8_t * data)
{
  uint8_t nrestart = 0;
  int8_t rv=0;
  uint8_t twst; // Temp storage of TWST register
  restart:
  if (nrestart++ >= MAX_ITER)
    return -5;
  begin:

	TWI_START();

	/* send SLA+W */
	TWI_SEND(sla | TW_WRITE, restart);

	TWI_SEND(reg, quit);
	
	TWI_RESTART();
	
	TWI_SEND(sla | TW_READ, error);

	for(;n>0;n--)
	{
		if(n==1)
		{
			TWCR = _BV(TWINT) | _BV(TWEN); /* send NAK after receive to sign last byte */
		}else
		{
			TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA); /* send ACK after transmission to sign we want more */			
		}
		while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
		switch ((twst = TW_STATUS))
		{
			case TW_MR_DATA_NACK:
				n = 0;		/* force end of loop */
				/* FALLTHROUGH */
			case TW_MR_DATA_ACK:
				*data = TWDR;
				data++;
				rv++;
				if(twst == TW_MR_DATA_NACK) goto quit;
				break;
			default:
				rv=-4;
				goto error;
		}
	}
  quit:
  /* Note [14] */
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); /* send stop condition */
  while(TWCR & (1<<TWSTO)); /* Wait for transmission of stop condition. Could be omitted in some cases. */
  return rv;

  error:
  goto quit;
}

static int8_t twi_write(uint8_t sla, uint8_t reg, uint8_t n, uint8_t * data)
{
  uint8_t nrestart = 0;
  int8_t rv=0;
  uint8_t twst; // Temp storage of TWST register
  restart:
  if (nrestart++ >= MAX_ITER)
    return -5;
  begin:
	TWI_START();

	/* send SLA+W */
	TWI_SEND(sla | TW_WRITE, restart);

	TWI_SEND(reg, quit);
	for(;n>0;n--)
	{
		TWI_SEND(data[rv], quit);
		rv++;
	}
  quit:
  /* Note [14] */
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); /* send stop condition */
  while(TWCR & (1<<TWSTO)); /* Wait for transmission of stop condition. Could be omitted in some cases. */
  return rv;

  error:
  goto quit;
}


void sensor_init()
{
	twi_init();
}

static bool sensor_initialized=false;

bool sensor_poll(int16_t * xyz)
{
	uint8_t data[6];	// Temporary data buffer
	if(twi_read(0b11010000, 0x0, 1, data)!=1)
	{
		UART0_Send('X');
	}else
	{
		UART0_Send_Bin(data[0]);
	}
	if(twi_read(0b11010000, 0x1d, 6, data)==6)
	{
		uint8_t tmp=data[1];
		data[1]=data[0];
		data[0]=tmp;


		tmp=data[3];
		data[3]=data[2];
		data[2]=tmp;

		tmp=data[5];
		data[5]=data[4];
		data[4]=tmp;

//		UART0_Send(' ');
//		UART0_Send_Bin(data[1]);
//		UART0_Send(' ');
//		UART0_Send_Bin(data[0]);
//		UART0_Send(' ');
		UART0_Send(' ');
		uint8_t n=UART0_Send_int32(*((int16_t *)data));
		for(;n<7;++n)
		{
			UART0_Send(' ');
		}
		n=UART0_Send_int32(*(((int16_t *)data)+1));
		for(;n<7;++n)
		{
			UART0_Send(' ');
		}
		UART0_Send_int32(*(((int16_t *)data)+2));
	}
	UART0_Send('\n');
	if(!sensor_initialized)
	{
		data[0]=8; // Set measure mode in the POWER_CTL register
		if(twi_write(ACC_ADDR, 0x2D, 1, data)!=1)
		{
			return true;
		}
		data[0]=11; // Set data format to FULL_RES, +-16G
		if(twi_write(ACC_ADDR, 0x31, 1, data)!=1)
		{
			return true;
		}
		sensor_initialized=true;
	}
	int8_t ret=twi_read(ACC_ADDR, 0x32, 6, (uint8_t *)xyz);
	if(ret==6)
	{
		return false;
/*		int16_t x=*((int16_t *)&data[0]);
		int16_t y=*((int16_t *)&data[2]);
		int16_t z=*((int16_t *)&data[4]);
		UART0_Send_Bin(data[1]);
		UART0_Send(' ');
		UART0_Send_Bin(data[0]);
		UART0_Send(' ');
		uint8_t n=UART0_Send_int32(x);
		for(;n<5;++n)
		{
			UART0_Send(' ');
		}
		n=UART0_Send_int32(y);
		for(;n<5;++n)
		{
			UART0_Send(' ');
		}
		n=UART0_Send_int32(z);*/
	}else
	{
		return true;
	}
}

