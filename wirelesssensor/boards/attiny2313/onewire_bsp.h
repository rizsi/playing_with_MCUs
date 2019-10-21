/**
 * Board specific mapping of OW protocol handling to pins.
 */
#include <onewire_bsp.h>

/// Cleared interrupt blocks - interrupts are disabled while reading temp in this program
#define CLI_BLOCK()

// Pull the OW interface to low
#define BSP_OW_LOW()  {DDRA|=_BV(0);PORTA&=~_BV(0);}
// Release OW and apply pullup resistor on OW
#define BSP_OW_PULLUP()  {DDRA&=~_BV(0);PORTA|=_BV(0);}
// DQ Active HIGH power mode (when parasitic power is used. Otherwise same as pullup.)
#define BSP_OW_HIGH()  {DDRA&=~_BV(0);PORTA|=_BV(0);}
// Read current state of OW: LOW:0 HIGH:1
#define BSP_OW_READ() ((PINA&_BV(0))!=0)
// delayMicroseconds - wait for the given microseconds

#define owDelayMillis(x) _delay_ms(x)
#define owDelayMicroseconds(x) _delay_us(x)



// Logging is disabled
#define BSP_OW_LOG_CH(A)
#define BSP_OW_LOG_NUM(A)
#define BSP_OW_LOG_LN()


/*
// Logging is enabled
#define BSP_OW_LOG_CH(A) USART_sendChar(A)
#define BSP_OW_LOG_NUM(A) debugDecimal(A)
#define BSP_OW_LOG_LN() USART_sendChar('\n')
*/

