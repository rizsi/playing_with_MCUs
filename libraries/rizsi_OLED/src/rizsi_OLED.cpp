#include <Arduino.h>
#include <util/twi.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "characters.h"

#define MAIN_ADDRESS 0B0111100
#define SLAVE_ADDRESS 0B00000000
#define READ_ADDRESS 0B00000001

#define OLED_I2C_ADDRESS (MAIN_ADDRESS|SLAVE_ADDRESS)
#define OLED_CONTROL_READ  (MAIN_ADDRESS|SLAVE_ADDRESS|READ_ADDRESS)
#define OLED_DATA_WRITE 0B00000000
#define OLED_WIDTH 128


/** 
 * @param address NULL means there was an error and send was cancelled
*/
typedef uint8_t (*twiFillCommand)(uint8_t * address, uint8_t ** getData, uint8_t *command);


#define cbi(port, bitindex) port*=~_BV(bitindex);
#define TWI_FREQ 400000

#define WAIT_TWCR(_VALUE, _REQUIREDSTATE, ERRCODE) if(internalErr=waitEvent(_VALUE, _REQUIREDSTATE, _REQUIREDSTATE, ERRCODE, 1)) return internalErr;

#define WAIT_TWCR2(_VALUE, _REQUIREDSTATE, _REQUIREDSTATE2, ERRCODE) if(internalErr=waitEvent(_VALUE, _REQUIREDSTATE, _REQUIREDSTATE2, ERRCODE, 1)) return internalErr;

uint8_t internalErr=0;

void twi_feed(uint8_t error);

uint8_t twiLastStatus;
twiFillCommand twiFeed;
uint8_t twiLength;
uint8_t * twiData;
uint8_t twiAt=0;
uint8_t twiAddress;
uint8_t twiCommand;

uint8_t * oledFramebuffer;

ISR(TWI_vect)
{
  switch(TW_STATUS){
      // All Master
    case TW_START:     // sent start condition
    case TW_REP_START: // sent repeated start condition
      // copy device address and r/w bit to output register and ack
      TWDR = (twiAddress<<1) | TW_WRITE;
      TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
      break;
          // Master Transmitter
    case TW_MT_SLA_ACK:  // slave receiver acked address
      TWDR = twiCommand;
      TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
      break;
    case TW_MT_DATA_ACK: // slave receiver acked data
      // if there is data to send, send it, otherwise stop 
      if(twiAt<twiLength){
        // copy data to output register and ack
        TWDR = twiData[twiAt];
        twiAt++;
        TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
      }else{
        // Send stop
          TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
          sei();
          // Send next packet
          twi_feed(0);
      }
      break;
    default:
      // ERROR - should never get here
      // Send stop to gracefully close any communication
      TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
      sei();
      // Tell feeder that there was an error so stream is cancelled.
      twi_feed(1);
      break;
  }
}


uint8_t waitEvent(uint8_t waitValue, uint8_t requiredState, uint8_t requiredState2, uint8_t errCode, uint8_t hasRequiredState)
{
//         digitalWrite(13, 0);
  uint32_t ctr=0;
  while((TWCR & waitValue )==0)
  {
    ctr++;
    if(ctr>16000)
    {
      Serial.print("TWI error - waitValue never received");
      Serial.print(errCode);
      Serial.print(" ");
      Serial.print(TWCR, HEX);
      Serial.print(" ");
      Serial.println(waitValue);
      digitalWrite(13,0);
      return 1;
    }
  }
//        digitalWrite(13, 1);
  if(hasRequiredState)
  {
    twiLastStatus=TW_STATUS;
    if(twiLastStatus!=requiredState&&twiLastStatus!=requiredState2)
    {
        digitalWrite(13, 0);
      Serial.print("TWI error!");
      Serial.print(errCode);
      Serial.print(" ");
      Serial.println(twiLastStatus, HEX);
      delay(1000);
      while(1);
      return errCode;
    }
  }
  return 0;
}

// Setup the TWI system
void twiInit()
{
  // Internal pullup is not used for TWI

  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  // activate internal pullups for twi.
  digitalWrite(SDA, 1);
  digitalWrite(SCL, 1);
  
  // initialize twi prescaler and bit rate
  cbi(TWSR, TWPS0);
  cbi(TWSR, TWPS1);
  TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
//  TWBR = 1;

  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA);

  /* twi bit rate formula from atmega128 manual pg 204
    SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR))
      note: TWBR should be 10 or higher for master mode
      It is 72 for a 16mhz Wiring board with 100kHz TWI */
}

void twiStop()
{
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}
void twiEndTransmission()
{
  twiStop();
}


void twiBeginTransmission(uint8_t sla)
{
  while(_BV(TWSTO)& TWCR)
  {
    // Wait until last stop condition is sent
    continue;
  }
    // Send start condition
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); //| _BV(TWIE);
  // while(1);
  WAIT_TWCR2(_BV(TWINT), TW_START, TW_REP_START, 100);

    // Send TWI Address
  TWDR = (sla<<1) | TW_WRITE;
  TWCR = _BV(TWINT) | _BV(TWEN);
  WAIT_TWCR2(_BV(TWINT), TW_MT_SLA_ACK,  TW_MT_SLA_ACK, 101);

}

void twiWrite(uint8_t data)
{
    TWDR = data;
    TWCR = _BV(TWINT) | _BV(TWEN);
    WAIT_TWCR2(_BV(TWINT), TW_MT_DATA_ACK, TW_MT_DATA_ACK, 1);
}

void twi_feed(uint8_t error)
{
  if(error)
  {
    twiFeed(NULL, NULL, NULL);
  }else{
    if((twiLength=twiFeed(&twiAddress, &twiData, &twiCommand))!=0)
    {
      twiAt=0;
      while(_BV(TWSTO)& TWCR)
      {
        // Wait until last stop condition is sent
        continue;
      }
      // Send start condition
      TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN)| _BV(TWIE);
    }
  }
}
void twiBulkData(twiFillCommand feed)
{
  twiFeed=feed;
  twi_feed(0);
}



void oledCommand(uint8_t command)
{
  twiBeginTransmission(OLED_I2C_ADDRESS);
  twiWrite(0x00); // Control
  twiWrite(command);
  twiEndTransmission();
}
void oledCommand2(uint8_t command, uint8_t d1)
{
//  oledCommand(command);
//  oledCommand(d1);
  twiBeginTransmission(OLED_I2C_ADDRESS);
  twiWrite(0x00); // Control
  twiWrite(command);
  twiWrite(d1);
  twiEndTransmission();
}
void oledCommand3(uint8_t command, uint8_t d1, uint8_t d2)
{
//  oledCommand(command);
//  oledCommand(d1);
//  oledCommand(d2);
  twiBeginTransmission(OLED_I2C_ADDRESS);
  twiWrite(0x00); // Control
  twiWrite(command);
  twiWrite(d1);
  twiWrite(d2);
  twiEndTransmission();
}
uint8_t contrast=0;
void oledStripe(int * ip, int n)
{
  int i=*ip;
  int endPtr=i+n;
    twiBeginTransmission(OLED_I2C_ADDRESS);
    twiWrite(0x40); // Data
    for(;i<endPtr;++i)
    {
      twiWrite(oledFramebuffer[i]);
    }
    twiEndTransmission();
  *ip=i;
}

volatile uint8_t oledState;
uint8_t oledContrast=0x81;
uint8_t oledPage;
uint16_t oledPointer;
uint16_t oledPagePointer;
/**
 * Feed I2C bus with data that refreshes the screen.
 * @param [out] command Command to send - first byte sent on TWI
 * @return size of data bytes 0 means nothing to send
 */
uint8_t fillCommand(uint8_t * address, uint8_t ** getData, uint8_t *command)
{
  static uint8_t data[4];
  *address=OLED_I2C_ADDRESS;
  *getData=data;
  *command=0;
  if(address==NULL)
   {
     oledState=10;
     return 0;
   }
  switch(oledState)
  {
    case 0:
      data[0]=0xaf; // Circuits on
      oledState=20;
      return 1;
    case 20:
      data[0]=0xa4; // Entire display from GRAM
      oledState=21;
      return 1;
    case 21:
      data[0]=0xa6; // Normal (non-inverted)
      oledState=22;
      return 1;
    case 22:
      data[0]=0x81; // Set contrast
      data[1]=oledContrast;
      oledState=1;
      return 2;
    case 1:
      data[0]=0x2E; // Deactivate scroll
      oledState=2;
      return 1;
    case 2:
      data[0]=0xA0; // Segment remap
      oledState=3;
      return 1;
    case 3:
      data[0]=0xD3; // Set display offset
      data[1]=0x0; // Set display offset
      oledState=4;
      return 2;
    case 4:
      data[0]=0x20;
      data[1]=0xB00000010;
      oledState=5;
      oledPage=0;
      oledPagePointer=0;
      oledPointer=0;
      return 2;
    // In cycle
    case 5:
      // Set page to write data to:
      data[0]=0xb0|oledPage;
      oledState=6;
      return 1;
    case 6:
      // Set horizontal position to write data to:
        // lower half of byte
      data[0]=0x02; // TODO hack - I don't really understand why it is not 0 but 2
      oledState=7;
      return 1;
    case 7:
    // high half of byte
      data[0]=0x10;
      oledState=8;
      return 1;
    case 8:
      *getData=&oledFramebuffer[oledPointer];
      oledPointer+=16;
      oledPagePointer+=16;
      if(oledPagePointer>=128)
      {
        oledPagePointer=0;
        oledPage++;
        if(oledPage>7)
        {
          oledState=9;
        }else
        {
          oledState=5;
        }
      }else
      {
        oledState=8;
      }
      *command=0x40;
      return 16;
    case 9:
      oledState=10;
      return 0;
    case 10:
      return 0;
  }
}

void oledData(const uint8_t * fb)
{
  oledFramebuffer=fb;
  oledState=0;
  twiBulkData(fillCommand);
}
boolean oledFinished()
{
  return oledState==10;
}
void _oledData(const uint8_t * fb)
{
  oledFramebuffer=fb;
  contrast=0xa7;
  oledCommand2(0x81, contrast);
//   Serial.print("contrast: ");
//   Serial.println(contrast);
   contrast+=32;
//  oledCommand2(0xA8, 63);
  oledCommand(0x2E); // Deactivate scroll
  oledCommand(0xA0); // Set segment re-map
  oledCommand2(0xD3, 0); // Set display offset
/*
 oledCommand2(0x20, 01); // Memoy access mode: horizontal
//  oledCommand3(0x21, 0, 127); // Set column address
  oledCommand3(0x22, 1, 6); // Page address
//  oledCommand(0);   // Column start address (0 = reset)
 // oledCommand(127); // Column end address (127 = reset)
*/
  oledCommand2(0x20, 0B00000010);
//  oledCommand(0xb0);
  int i=0;
  uint8_t page=0;
  for(int i=0;i<1024;)
  {
    // Set page to write data to:
   oledCommand(0xb0|page);
    // Set horizontal position to write data to:
    // lower half of byte
    oledCommand(0x02); // TODO hack - I don't really understand why it is not 0 but 2
    // high half of byte
    oledCommand(0x10);
    oledStripe(&i, 16);
    oledStripe(&i, 16);
    oledStripe(&i, 16);
    oledStripe(&i, 16);
    oledStripe(&i, 16);
    oledStripe(&i, 16);
    oledStripe(&i, 16);
    oledStripe(&i, 16);
    page++;
  }
  oledState=10;
}
// Does not work
void oledStatus()
{
  twiBeginTransmission(OLED_I2C_ADDRESS);
  twiWrite(0x00); // Control
//  Wire.requestFrom(0, 0);
  twiEndTransmission();
}

void oledTest()
{
  Serial.println("Wait for boot...");
  delay(1000);
  Serial.println("Send first command");
  delay(100);
  oledCommand(0xaf); // Circuits on
  Serial.println("Circuits on");
  oledCommand(0xa5); // Entire display (each pixel) on
  delay(250);
  oledCommand(0xae); // Circuits OFF
  delay(250);
  oledCommand(0xaf); // Circuits OFF
  oledCommand(0xa4); // Entire display from GRAM
  oledCommand(0xa6); // Normal (non-inverted)
  //Serial.println("Send all data!");
  // oledState=0;
  //  oledData();
  //while(!oledFinished());
  //Serial.println("Send all data finished");
  
  delay(250);

  oledCommand(0xa7); // Inverted (non-inverted)
  delay(250);

  // Setup normal usage parameters
  oledCommand(0xaf); // Circuits on
  oledCommand(0xa4); // Entire display from GRAM
  oledCommand(0xa6); // Normal (non-inverted)
}

void oledInit()
{
  oledState=10;
  twiInit(); // Initiate the Wire library
}

