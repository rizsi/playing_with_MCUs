#include <Arduino.h>
#include <rizsi_TWI.h>
#include <util/twi.h>
#include <avr/interrupt.h>



#define cbi(port, bitindex) port*=~_BV(bitindex);
#define TWI_FREQ 400000

#define WAIT_TWCR(_VALUE, _REQUIREDSTATE, ERRCODE) if(internalErr=waitEvent(_VALUE, _REQUIREDSTATE, _REQUIREDSTATE, ERRCODE, 1)) return internalErr;

#define WAIT_TWCR2(_VALUE, _REQUIREDSTATE, _REQUIREDSTATE2, ERRCODE) if(internalErr=waitEvent(_VALUE, _REQUIREDSTATE, _REQUIREDSTATE2, ERRCODE, 1)) return internalErr;

static uint8_t internalErr=0;

static void twi_feed(uint8_t error);

static uint8_t twiInited=0;
static uint8_t twiLastStatus;
static twiFillCommand twiFeed;
static uint8_t twiLength;
static uint8_t * twiData;
static uint8_t twiAt=0;
static uint8_t twiAddress;
static uint8_t twiCommand;

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


static uint8_t waitEvent(uint8_t waitValue, uint8_t requiredState, uint8_t requiredState2, uint8_t errCode, uint8_t hasRequiredState)
{
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
  if(!twiInited)
  {
  twiInited=1;
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
void twiBeginRead(uint8_t sla)
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
  TWDR = (sla<<1) | TW_READ;
  TWCR = _BV(TWINT) | _BV(TWEN);
  WAIT_TWCR2(_BV(TWINT), TW_MT_SLA_ACK,  TW_MT_SLA_ACK, 101);
}
uint16_t twiRead(uint8_t lastByte)
{
	if(lastByte)
	{
		TWCR = _BV(TWINT) | _BV(TWEN);
	}
	else
	{
		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	}
	// TODO error case is not handled.
	WAIT_TWCR2(_BV(TWINT), TW_MR_DATA_ACK, TW_MR_DATA_NACK, 102);
	return TWDR;
}

static void twi_feed(uint8_t error)
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
