// nRF24L01 Radio hardware bindings

// Chip select for the radio SPI
#define RADIO_BEGIN() {PORTB&=~_BV(4);DDRB|=_BV(4);}
// Chip deselect for the radio SPI
#define RADIO_END() {PORTB|=_BV(4);DDRB|=_BV(4);}
// Enable Radio RX or TX
#define RADIO_SET_ENABLED(enabled) if(enabled){PORTB|=_BV(3);DDRB|=_BV(3);}else{PORTB&=~_BV(3);DDRB|=_BV(3);}

extern void RADIO_PINS_INIT();


//   SPI.begin();
//  SPI.setClockDivider(SPI_CLOCK_DIV128);


// Debug logging disabled
#define RADIO_DEBUG_CH(x) USART_sendChar(x)
#define RADIO_DEBUG_BIN(x) debugDecimal(x)
#define RADIO_DEBUG_STR(x) debugString(x)
#define RADIO_DEBUG_DEC(x) debugDecimal(x)
#define RADIO_DEBUG_HEX(x) debugDecimal(x)

extern uint8_t RADIO_SPI(uint8_t transmit);


