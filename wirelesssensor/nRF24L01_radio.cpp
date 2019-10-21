#include <bsp.h>
#include <nRF24L01_radio.h>
#include <nRF24L01_radio_bsp.h>

#define low(x)   ((x) & 0xFF)
#define high(x)   (((x)>>8) & 0xFF)


// Radio power usage: transmit 7-11mA
// RX: settling 8.4mA, max 12mA
// -> Maybe it is not worth to listen to a reply but just send the message 3 times with a random delay


// Bit mask for 1: RX 0:TX
#define STATUS_PRIM_RX 1
// Bit mask for power
#define STATUS_POWER 2
// Bit mask for CRC mode. Use 1: 2 bytes (0: 1 byte)
#define STATUS_CRC_MODE 4
// Bit mask for CRC enable. Use: 1 enable
#define STATUS_CRC_ENABLE 8

// The status register
#define REG_CONFIG 0
#define REG_STATUS 7

static uint8_t radioMode;

static void writeReg(uint8_t reg, uint8_t value);
static uint16_t readFifoStatus();
static void radioActivateMode();


static uint8_t processStatus(uint16_t fifostatus)
{
//  uint8_t status=fifostatus&0xFF;
  uint8_t ret=0;
  if(low(fifostatus)!=0b00001110)
  {
	RADIO_DEBUG_CH('\n');
	RADIO_DEBUG_CH('S');
	RADIO_DEBUG_BIN(high(fifostatus));
	RADIO_DEBUG_CH(' ');
	RADIO_DEBUG_BIN(low(fifostatus));
	RADIO_DEBUG_CH('\n');
  }
  if((low(fifostatus)&0b00010000) !=0)
  {
      writeReg(REG_STATUS, 0b00010000); // Clear IRQ
  }
  if((low(fifostatus)&0b01000000) !=0)
  {
    RADIO_DEBUG_CH('R');
    // Data received in FIFO
    while((high(fifostatus) & 1) == 0)
    {
      RADIO_DEBUG_CH('M');
      // While RX is not empty
      RADIO_BEGIN();
      RADIO_SPI(0b01100001); // Read RX register
      uint8_t data[33];
      for(uint8_t dataIndex=0;dataIndex<32;++dataIndex)
      {
        data[dataIndex]=RADIO_SPI(0);
      }
      RADIO_END();
      writeReg(REG_STATUS, 0b01000000); // Clear IRQ
      data[32]=0;
      RADIO_DEBUG_CH('D');
      RADIO_DEBUG_STR((const char *)data);
      radioReceiveCallback(data);
      fifostatus=readFifoStatus();
      ret|=RADIO_RET_RECEIVED;
    }
  }
  if((low(fifostatus)&0b00100000)!=0)
  {
    RADIO_DEBUG_CH('%');
//    RADIO_DEBUG_CH('%');
//    RADIO_DEBUG_CH('%');
 //   RADIO_DEBUG_CH('%');
//    RADIO_DEBUG_CH('%');
    // Radio send done
    writeReg(REG_STATUS, 0b00100000); // Clear IRQ
    if((high(fifostatus) & 0b00010000)!=0)
    {
      // TX FIFO emptyu
      RADIO_SET_ENABLED(0); // Moves the state machine back to 
      // Data in TX was sent - back to the requested mode
      radioActivateMode();
      ret|=RADIO_RET_SENT;
    }else{
       // Send one more data
       RADIO_SET_ENABLED(1);
	_delay_us(10);
       RADIO_SET_ENABLED(0);
    }
  }
  return ret;
}

// Read the status byte from the radio chip - read FIFO status is better because FIFO status is also important

uint8_t radioReadStatus()
{
  RADIO_BEGIN();
  uint8_t ret=RADIO_SPI(0b11111111); // NOP - status read command
  RADIO_END();
  return ret;
}

uint16_t radioFifoStatus()
{
	return readFifoStatus();
}
/**
 * FIFO and basic status in a single 16 bit variable.
 * High byte is the FIFO status
 */
static uint16_t readFifoStatus()
{
  RADIO_BEGIN();
  uint8_t ret=RADIO_SPI(0x17); // read FIFO status register
  uint8_t rethigh=RADIO_SPI(0);
  RADIO_END();
  return ((uint16_t)ret)+(((uint16_t)rethigh)<<8);
}

static void writeReg(uint8_t reg, uint8_t value)
{
  reg&=0b00011111;
  RADIO_BEGIN();
  uint8_t ret=RADIO_SPI(0b00100000+reg); // write register command
  RADIO_SPI(value);
  RADIO_END();
}
static void writeRegCheck(uint8_t reg, uint8_t value)
{
  writeReg(reg, value);
}
void radioReadData()
{
    uint8_t data[9];
//  RADIO_BEGIN();
  uint8_t initialAddress=0;
//  {
//    uint8_t ret=SPI.transfer(initialAddress);
//  }
//  RADIO_END();
  for(uint8_t i=0;i<8;++i)
  {
    RADIO_BEGIN();
    uint8_t ret0=RADIO_SPI(initialAddress+i);
    uint8_t ret1=RADIO_SPI(0);
	data[i]=ret1;
    if(i==0)
    {
      data[8]=ret0;
    }
    RADIO_END();
  }

  RADIO_DEBUG_CH('\n');
  RADIO_DEBUG_CH('s');
  RADIO_DEBUG_BIN(data[8]);
  for(uint8_t i=0;i<8;++i)
  {
    RADIO_DEBUG_CH('r');
    RADIO_DEBUG_DEC(i);
    RADIO_DEBUG_CH(' ');
    RADIO_DEBUG_BIN(data[i]);
    RADIO_DEBUG_CH('\n');
  }
  for(uint8_t i=0;i<7;++i)
  {
    RADIO_BEGIN();
    uint8_t ret=RADIO_SPI(0xa+i);
    for(uint8_t j=0;j<5;++j)
    {
      data[i]=RADIO_SPI(0);
    }
    RADIO_END();
    RADIO_DEBUG_CH('\n');
    RADIO_DEBUG_CH('r');
    RADIO_DEBUG_CH('x');
    RADIO_DEBUG_DEC(i);
    RADIO_DEBUG_CH(' ');
    for(uint8_t j=0;j<5;++j)
    {
      RADIO_DEBUG_HEX(data[i]);
    }
    RADIO_DEBUG_CH('\n');
  }
  for(uint8_t i=0;i<6;++i)
  {
    RADIO_BEGIN();
    uint8_t ret=RADIO_SPI(0x11+i);
	data[i]=RADIO_SPI(0);
    RADIO_END();
  }
    RADIO_DEBUG_CH('\n');
  for(uint8_t i=0;i<6;++i)
  {
    RADIO_DEBUG_CH('d');
    RADIO_DEBUG_DEC(i);
    RADIO_DEBUG_CH(' ');
    RADIO_DEBUG_DEC(data[i]);
    RADIO_DEBUG_CH('\n');
  }
}

static void radioSetRxTx(uint8_t power, uint8_t isRx)
{
//  power=0;
  writeRegCheck(REG_CONFIG, 0b00001100|(power?0b10:0) |(isRx?1:0)); // Write Config register
  // And set up RX or TX mode
}
/*
void radioOn(bool on)
{
  Serial.print("Turn radio ");
  Serial.println(on?"on":"off");
  if(on)
  {
    RADIO_SET_ENABLED(1);
  }else
  {
    RADIO_SET_ENABLED(0);
  }
}
*/
static void radioActivateMode()
{
  if(radioMode==RADIO_MODE_RECEIVE)
  {
    radioSetRxTx(1, 1); // Configure all and set receive mode, turn on Radio
    RADIO_SET_ENABLED(1);
  }else
  {
    radioSetRxTx(0, 1); // Configure all and set receive mode, turn on Radio
    RADIO_SET_ENABLED(0);
  }
}
void radioSetup(uint8_t mode, uint8_t messageSize)
{
  radioMode=mode;
  RADIO_SET_ENABLED(0);
  radioSetRxTx(0, 1); // Configure all and set receive mode, turn off Radio
//  delay(2);
//  radioSetRxTx(1, 1); // turn on and still on receive mode
//  delay(2);
  writeRegCheck(1, 0); // EN_AA - auto acknowledge is disabled
  writeRegCheck(2, 1); // EN_RXADDR - only ADDR0 is used
  // SETUP_AW - 5 byte address width is used which is the default - NOP
  writeRegCheck(4, 0); // SETUP_RETR - disable auto retransmit
  // RF_CH - receive channel is left on default
  writeRegCheck(6, 0b111); // RF_SETUP - 1Mbps air data rate, max transmit power, enable LNA gain
  for(uint8_t i=0;i<6;++i)
  {
    writeRegCheck(0x11+i, messageSize); // Receive data size as set in parameter
  }
  radioActivateMode();
}
void radioSend(uint8_t * data, uint8_t nByte, uint8_t modeAfter)
{
  radioMode=modeAfter;
  RADIO_SET_ENABLED(0);
//    RADIO_SET_ENABLED(0);
    radioSetRxTx(1, 0); // Set TX mode
    RADIO_BEGIN();
    RADIO_SPI(0b10100000); // Write TX payload
    for(uint8_t i=0;i<nByte;++i)
    {
      RADIO_SPI(data[i]);
    }
    RADIO_END();
  RADIO_SET_ENABLED(1);
	_delay_us(10);
  RADIO_SET_ENABLED(0);
}


void radioPinsInit()
{
	RADIO_PINS_INIT();
	RADIO_END();
	RADIO_SET_ENABLED(0);
}

//void setup() {
//  readData();
//  radioSetup();
//  while(1)
//  {
//    uint8_t status=readStatus();
//    Serial.println(status, BIN);
//   readData();
//  }
//  readData();
//  radioOn(1);
//}

uint8_t radioLoop()
{
	USART_sendChar('\n');
	USART_sendChar('z');
	USART_sendChar('\n');
    uint16_t ret=readFifoStatus();
//    Serial.println(ret, BIN);
    return processStatus(ret);
}
void radioLoopUntilSent()
{
	while((radioLoop()&RADIO_RET_SENT)==0);
}

/*
void loop() {
  uint32_t t=millis();
  while(millis()-t<2000)
  {
  }
//  Serial.println(status, BIN);
  Serial.println("looping...");
  static char message[32]="CICAmica";
  radioSend((uint8_t *)message, 32);
//  radioSend("CICA\0", 5);
  uint16_t stat=readFifoStatus();
//  status=readStatus();
  Serial.println(stat, BIN);
//  delay(2000);
//  writeReg(REG_STATUS, );
//  Serial.print("Status bit received: ");
//  Serial.println(ret, BIN);
}
*/
