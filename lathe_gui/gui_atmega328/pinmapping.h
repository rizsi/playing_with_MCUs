

#define DIGITS_LATCH_OFF() PORTC|=_BV(1); DDRC|=_BV(1)
#define DIGITS_LATCH_ON() PORTC&=~_BV(1); DDRC|=_BV(1)

#define PINPAD_INPUT() PORTC&=~_BV(0); DDRC&=_BV(0)

/// Parallel input enable - read values from buttons - active low
#define SHIFT_IN_LATCH_OFF() PORTD|=_BV(2); DDRD|=_BV(2)
#define SHIFT_IN_LATCH_ON() PORTD&=~_BV(2); DDRD|=_BV(2)

#define PORT_SPI PORTB
#define DDR_SPI DDRB
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5
#define DD_SS 2

/**
 * Configure the pins as output and put them into high. (When timer OCRXX is activated that will override the values.)
 * TODO configured to low instead - this version is always on because this is just a test program for now.
 */
#define CONFIG_PWM_PINS() PORTD&=~_BV(3); DDRD|=_BV(3); PORTD&=~_BV(5); DDRD|=_BV(5)

#define SS_PIN_IN(PINID) PORT_SPI&=~_BV(PINID); DDR_SPI&=~_BV(PINID)
#define SS_PIN_OUT(PINID) PORT_SPI&=~_BV(PINID); DDR_SPI|=_BV(PINID)
#define SS_PIN_OUT_HIGH(PINID) PORT_SPI|=_BV(PINID); DDR_SPI|=_BV(PINID)
/**
 * Turn SS to output! Otherwise low SS would transition SPI into slave mode!
 */
#define SPI_SS_MASTER() SS_PIN_OUT_HIGH(DD_SS); SS_PIN_OUT(DD_MOSI); SS_PIN_OUT(DD_SCK); SS_PIN_IN(DD_MISO)
#define SPI_SS_SLAVE() SS_PIN_IN(DD_SS);         SS_PIN_IN(DD_MOSI);  SS_PIN_IN(DD_SCK); SS_PIN_OUT(DD_MISO)

#define NCS_SENSOR_OFF(index) if(index==0){PORTB|=_BV(1);DDRB|=_BV(1);}else{PORTD|=_BV(4);DDRD|=_BV(4);}
#define NCS_SENSOR_ON(index) if(index==0){PORTB&=~_BV(1);DDRB|=_BV(1);}else{PORTD&=~_BV(4);DDRD|=_BV(4);}


