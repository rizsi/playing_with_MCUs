// Two wheeler Balancer project



// Connections:
// 3, 11: PWM of motors
// A2-A1 switch
// SDA, SCL: Sensor https://www.sparkfun.com/products/retired/10724 ADXL345 and 
// Pullup to 3.3V


#include <avr/io.h>
#include <stdint.h>
#include <debug_uart0.h>
#include <sensor.h>
#include <util/delay.h>


/** Initialize HW for switch sensing */
static void switch_init()
{
	PORTC&=~_BV(1);  // PC1 - A01 drive to low
	DDRC|=_BV(1);
	
	DDRC&=~_BV(2); // PC2 - A02 drive to input+pullup
	PORTC|=_BV(2);

	DDRC&=~_BV(0); // PC2 - A02 drive to input+pullup
	PORTC|=_BV(0);
}

static bool switch_on()
{
	return (PINC&_BV(2))==0;
}

int main ()
{
	UART0_Init();
	switch_init();
	sensor_init();
	while(1)
	{
		sensor_poll();
		if(switch_on())
		{
			UART0_Send('A');
		}else
		{
			UART0_Send('B');
		}
		_delay_ms(100);
	}
	return 0;
}

