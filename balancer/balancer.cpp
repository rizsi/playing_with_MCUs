// Two wheeler Balancer project


// At the end copying this: https://github.com/TKJElectronics/BalancingRobot
// Very good looking: https://www.youtube.com/watch?v=Kd2kJxBkPmk
// http://blog.tkjelectronics.dk/2012/03/the-balancing-robot/


// Connections:
// 3, 11: PWM of motors
// A2-A1 switch
// SDA, SCL: Sensor https://www.sparkfun.com/products/retired/10724 ADXL345 and ITG-3200
// Pullup to 3.3V


#include <avr/io.h>
#include <stdint.h>
#include <debug_uart0.h>
#include <sensor.h>
#include <util/delay.h>
#include <motor.h>


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

static uint8_t x=0;
int main ()
{
	int16_t zTarget=0;
	int16_t xyz[3];
	UART0_Init();
	switch_init();
	sensor_init();
	motor_init();
	while(1)
	{
		if(sensor_poll(xyz))
		{
			motor_set(0, 0);
			continue;
		}
//		UART0_Send_int32(zTarget);
//		UART0_Send(' ');
//		UART0_Send_int32(xyz[2]);
		if(switch_on())
		{
			int16_t diff=zTarget-xyz[2];
//		UART0_Send(' ');
//		UART0_Send_int32(diff);
			motor_set(-diff*4, -diff*4);
//			UART0_Send('A');
		}else
		{
			motor_set(0, 0);
//			UART0_Send('B');
			zTarget=xyz[2];
		}
		x++;
		if(x==100)
		{
			x=0;
			UART0_Send('A');
		}
//		UART0_Send('\n');
//		_delay_ms(100);
	}
	return 0;
}

