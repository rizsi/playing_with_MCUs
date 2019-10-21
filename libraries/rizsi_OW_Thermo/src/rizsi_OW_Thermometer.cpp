#include <Arduino.h>
#include <util/atomic.h>


// 1 us: 16 instruction cycles
// Interrupt handling is in order of 4us (with pus and pop at the end)

// Max conversion time:
// R1 R0 (configuration bits)
// 0  0  9 bits 93.75ms
// 0  1  10 bits 187.5ms
// 1  0  11 bits 375ms
// 1  1  12 bits 750 ms

// Reset: ~1ms
// command: 60-100 uS/bit -> ~1ms / byte
// Receive: 65 us/bit -> ~1ms / byte
// Konfig+konvert:
// reset+8 bájt küld+8 bájt fogad -> ~17ms


//uint32_t tot_overflow=0;

/// Trigger timer us - prescaler: 1
#define TIMER_TRIGGER(us, handler) timer_handler=handler; TCCR1B &=~(B00000111 <<CS10); TCCR1B |= (B00000001 << CS10); TCNT1=-((int16_t)us*16); TIFR1|=_BV(TOV1); TIMSK1 |= _BV(TOIE1)
/// Trigger timer ms - prescaler: 1024
#define TIMER_TRIGGER_MS(ms, handler) timer_handler=handler; TCCR1B &=~(B00000111 <<CS10); TCCR1B |= (B00000101 << CS10); TCNT1=-(int16_t)((int32_t)ms*16*1000/1024); TIFR1|=_BV(TOV1); TIMSK1 |= _BV(TOIE1)

#define OW_LOW()  pinMode(owPin, OUTPUT)
#define OW_RELEASE() pinMode(owPin, INPUT)
#define OW_READ() digitalRead(owPin)

static uint8_t owPin;



typedef void (*TIMEOUT_HANDLER)(void);
typedef void (*OW_HANDLER)(void);
TIMEOUT_HANDLER timer_handler;
// TIMER1 overflow interrupt service routine
// called whenever TCNT1 overflows
ISR(TIMER1_OVF_vect)
{
  // Disable overflow interrupt
  TIMSK1 &= ~_BV(TOIE1);
  timer_handler();
}

// initialize timer, interrupt and variable. Timer1 no prescaler runs at 16MHz
void timer1_init()
{
    // set up timer with prescaler = 1
    TCCR1B &=~(B00000111 <<CS10);
    TCCR1A&=0;
    TCCR1B |= (B00000001 << CS10);
   OCR1A=0xFFFF;
   OCR1B=0xFFFF;
 
    // initialize counter
    TCNT1 = 0;
 
    // disable overflow interrupt
    TIMSK1 &= ~_BV(TOIE1);
 
    // enable global interrupts
    sei(); 
}



uint8_t owireCRC(uint8_t data, boolean reset)
{
  static uint8_t crc=0;
  if(reset)
  {
    crc=0;
  }
  for(uint8_t i=0;i<8;++i)
  {
    uint8_t lsbXdataBit=(data&1)^(crc&1);
    crc=(crc>>1) | (crc<<7); // rotate 1 right
    if(lsbXdataBit)
    {
      crc^=B00001100;
    }
    if(data&1)
    {
      crc^=B10000000;
    }
    data>>=1;
  }
  return crc;
}

void owireSend(uint8_t data)
{
  for(int i=0;i<8;++i)
  {
    if(data&0x01)
    {
      pinMode(owPin, OUTPUT);
      digitalWrite(owPin, LOW);
      delayMicroseconds(2); // 1<T<15 us
      pinMode(owPin, INPUT);
      digitalWrite(owPin, LOW);
      delayMicroseconds(15+15+30); // Recovery 1us<T
    }
    else
    {
      pinMode(owPin, OUTPUT);
      digitalWrite(owPin, LOW);
      delayMicroseconds(90); // 60<T<120 us
      pinMode(owPin, INPUT);
      digitalWrite(owPin, LOW);
      delayMicroseconds(10); // Recovery 1us<T
    }
    data>>=1;
  }
}

uint8_t owireReceiveBit()
{
    pinMode(owPin, OUTPUT);
    digitalWrite(owPin, LOW);
    delayMicroseconds(2); // 1<T<15 us
    pinMode(owPin, INPUT);
    digitalWrite(owPin, LOW);
    
    delayMicroseconds(2); //  58>T>13us
    
    uint8_t sample=digitalRead(owPin);
    
    delayMicroseconds(60); // T>45us
  return sample;
}

uint8_t owireReceive()
{
  uint8_t ret=0;
  for(int i=0;i<8;++i)
  {
    uint8_t sample=owireReceiveBit();
    ret>>=1;
    ret|=(sample?(uint8_t)0x80:0);
  }
  return ret;
}

static boolean owireReceiveBytes(uint8_t * tgBuffer, uint8_t nByte)
{
  for(uint8_t i=0;i<nByte;++i)
  {
     tgBuffer[i]=owireReceive();
  }
  uint8_t crc=owireCRC(0, 1);
  Serial.print("T: ");
  for(uint8_t i=0;i<nByte-1;++i)
  {
  	Serial.print(tgBuffer[i], DEC);
    crc=owireCRC(tgBuffer[i], 0);
  }
  Serial.println();
  return crc==tgBuffer[nByte-1];
}

boolean owireReset()
{
  OW_LOW();
  delayMicroseconds(480);
  OW_RELEASE();
  delayMicroseconds(30);
  uint8_t presence=OW_READ();
  delayMicroseconds(450);
  return !presence; 
}

#define OW_STEP_RESET_CONVERSION 0
#define OW_STEP_INITIALIZE 1
#define OW_STEP_START_CONVERSION 2
#define OW_STEP_READ_SCRATCHPAD 3
#define OW_STEP_CHECK_SCRATCHPAD 4
#define OW_STEP_READ_SCRATCHPAD_RESET 5
#define OW_STEP_READ_ROM 6
#define OW_STEP_CHECK_ROM 7
#define OW_STEP_RESET_READ_ROM 8
#define OW_STEP_READ_SCRATCHPAD_REQ_RESET 9

#define OW_ERROR_UNKNOWN -1
#define OW_ERROR_PRESENCE -2
#define OW_ERROR_CRC -3
#define OW_ERROR_UNINITIALIZED -4

struct
{
  volatile int8_t state;
  uint8_t data[9];
  uint8_t bit;
  uint8_t nByte;
  uint8_t currentByte;
  int8_t istate;
  uint8_t presence;
  uint8_t initialized=0;
  int16_t tempM16;
} owStatus;

void owInit(uint8_t pin)
{
  owPin=pin;
  pinMode(owPin, INPUT);
  digitalWrite(owPin, LOW);
  
  timer1_init();
  owStatus.initialized=0;
  owStatus.state=OW_ERROR_UNINITIALIZED;
}

void ow_ActionFinished();
void ow_Send();
void ow_Read();
void ow_Reset();

void ow_Send_pulse3()
{
  sei();

    if(owStatus.bit>=8)
    {
      owStatus.currentByte++;
      if(owStatus.currentByte<owStatus.nByte)
      {
        owStatus.bit=0;
        ow_Send();
      }else
      {
        ow_ActionFinished();
      }
    }else
    {
      ow_Send();
    }
}

void ow_Send_pulse2()
{
  OW_RELEASE();
  TIMER_TRIGGER(10, ow_Send_pulse3);
}

void ow_Send_pulse1()
{
  if(owStatus.data[owStatus.currentByte]&1)
  {
    OW_RELEASE();
  }
  owStatus.data[owStatus.currentByte]>>=1;
  owStatus.bit++;
  TIMER_TRIGGER(80, ow_Send_pulse2);
}
void ow_Send()
{
  OW_LOW();
  TIMER_TRIGGER(2, ow_Send_pulse1);
}

void ow_Read_pulse3()
{
  sei();
  if(owStatus.bit<8)
  {
    ow_Read();
  }else
  {
    owStatus.currentByte++;
    if(owStatus.currentByte<owStatus.nByte)
    {
      owStatus.bit=0;
      ow_Read();
    }else
    {
      ow_ActionFinished();
    }
  }
}


void ow_Read()
{
  uint8_t sample;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
	  OW_LOW();
	// TODO this part is best executed without interrupts - by hand timing. Hand timing could be refined
	  OW_RELEASE();
	  sample=OW_READ();
  }
  owStatus.data[owStatus.currentByte]>>=1;
  owStatus.data[owStatus.currentByte]|=sample?(uint8_t)0x80:0;
  owStatus.bit++;
  TIMER_TRIGGER(60, ow_Read_pulse3);
}
void ow_SendAll()
{
  owStatus.bit=0;
  owStatus.currentByte=0;
  ow_Send();
}
void ow_ReadAll()
{
  for(uint8_t i=0;i<owStatus.nByte;++i)
  {
    owStatus.data[i]=0;
  }
  owStatus.bit=0;
  owStatus.currentByte=0;
  ow_Read();
}
boolean ow_CheckCRC()
{
  uint8_t crc=owireCRC(0,1);
#ifdef DEBUG_OW
  Serial.print("T: ");
#endif
  for(uint8_t i=0;i<owStatus.nByte-1;++i)
  {
#ifdef DEBUG_OW
  	Serial.print(owStatus.data[i], DEC);
  	Serial.print(", ");
#endif
    crc=owireCRC(owStatus.data[i],0);
  }
#ifdef DEBUG_OW
  Serial.println();
#endif
  return crc!=owStatus.data[owStatus.nByte-1];
}
void ow_ActionFinished()
{
  sei();
  if(owStatus.istate<0)
  {
    // ERRORS
    owStatus.state=owStatus.istate;
        owStatus.initialized=0;
  }else
  {
    switch(owStatus.istate)
    {
      case OW_STEP_RESET_READ_ROM:
        if(!owStatus.presence)
        {
          owStatus.state=OW_ERROR_PRESENCE;
          break;
        }else
        {
          owStatus.data[0]=0x33;
          owStatus.nByte=1;
          owStatus.istate=OW_STEP_READ_ROM;
          ow_SendAll();
          break;
        }
      case OW_STEP_RESET_CONVERSION:
        if(!owStatus.presence)
        {
          owStatus.state=OW_ERROR_PRESENCE;
          break;
        }else
        {
          if(!owStatus.initialized)
          {
            owStatus.istate=OW_STEP_INITIALIZE;
            owStatus.data[0]=0xCC; // Skip ROM command - we have only one sensor on the line.
            owStatus.data[1]=0x4E; // Write scratchpad - Configure the device
            owStatus.data[2]=0;
            owStatus.data[3]=0;
            owStatus.data[4]=B01100000;
            owStatus.nByte=5;
            owStatus.initialized=1;
            ow_SendAll();
          }else
          {
            owStatus.data[0]=0xCC;
            owStatus.data[1]=0x44; // Convert temperature
            owStatus.nByte=2;
            owStatus.istate=OW_STEP_START_CONVERSION;
            ow_SendAll();
          }
        }
        break;
      case OW_STEP_READ_ROM:
          owStatus.nByte=8;
          owStatus.istate=OW_STEP_CHECK_ROM;
          ow_ReadAll();
        break;
      case OW_STEP_START_CONVERSION:
          // Wait 1sec (minimum by spec: 750 ms)
        owStatus.istate=OW_STEP_READ_SCRATCHPAD_REQ_RESET;
        TIMER_TRIGGER_MS(1000, ow_ActionFinished);      
        break;
      case OW_STEP_READ_SCRATCHPAD_REQ_RESET:
        owStatus.istate=OW_STEP_READ_SCRATCHPAD_RESET;
        ow_Reset();
        break;
      case OW_STEP_READ_SCRATCHPAD_RESET:
        if(!owStatus.presence)
        {
          owStatus.state=OW_ERROR_PRESENCE;
          break;
        }else
        {
            owStatus.data[0]=0xCC;
            owStatus.data[1]=0xBE; // Read Scratchpad
            owStatus.nByte=2;
            owStatus.istate=OW_STEP_READ_SCRATCHPAD;
            ow_SendAll();
        }
        break;
      case OW_STEP_READ_SCRATCHPAD:
         owStatus.nByte=9;
         owStatus.istate=OW_STEP_CHECK_SCRATCHPAD;
         ow_ReadAll();
        break;
      case OW_STEP_CHECK_ROM:
      {
        boolean err=ow_CheckCRC();
        owStatus.state=err?OW_ERROR_CRC:6;
        break;
      }
      case OW_STEP_CHECK_SCRATCHPAD:
      {
        boolean err=ow_CheckCRC();
        if(!err)
        {
          uint16_t data=owStatus.data[1];
          data<<=8;
          data|=owStatus.data[0];
          owStatus.tempM16=data;
        }
        owStatus.state=err?OW_ERROR_CRC:5;
        break;
      }
      case OW_STEP_INITIALIZE:
        // TODO check initialized state by re-reading configuration.
        owStatus.istate=OW_STEP_RESET_CONVERSION;
        ow_Reset();
        break;
      default:
        owStatus.initialized=0;
        owStatus.state=OW_ERROR_UNKNOWN;
        break;
    }
  }
}

void ow_Reset_read()
{
  uint8_t presence=OW_READ();
  owStatus.presence=!presence;
  TIMER_TRIGGER(450, ow_ActionFinished);
}
void ow_Reset_release()
{
  OW_RELEASE();
  TIMER_TRIGGER(30, ow_Reset_read);
}

void ow_Reset()
{
  OW_LOW();
  TIMER_TRIGGER(480, ow_Reset_release);  
}

void owReadThermo()
{
   owStatus.state=0;
   owStatus.istate=OW_STEP_RESET_CONVERSION;
   ow_Reset();
}

void owReadROM()
{
   owStatus.state=0;
   owStatus.istate=OW_STEP_RESET_READ_ROM;
   ow_Reset();
}
boolean owReady()
{
  return owStatus.state!=0;
}
boolean owIsThermoReady()
{
	return owStatus.state==5;
}
boolean owIsROMReady()
{
	return owStatus.state==6;
}
uint16_t owGetTM16()
{
	return owStatus.tempM16;
}
int8_t owErrorCode()
{
	return owStatus.state;
}

/*
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  owInit();
}
*/

/*
void loop() {
  owReadROM();
  while(owStatus.state==0);
  Serial.print("OW read ROM return code: ");
  Serial.println(owStatus.state);
  owReadThermo();
  while(owStatus.state==0);
  Serial.print("OW read thermo return code: ");
  Serial.println(owStatus.state);
  if(owStatus.state>0)
  {
    float valueT=((float)owStatus.tempM16)/16.0f;
    Serial.print("Temperature read successfully: ");
    Serial.println(valueT);
  }
  delay(1000);
}
*/


