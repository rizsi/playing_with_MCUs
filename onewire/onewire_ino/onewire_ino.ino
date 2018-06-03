#define OWIRE_GND 3
#define OWIRE_DATA 4
#define OWIRE_VCC 5




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

#define OW_LOW()  pinMode(OWIRE_DATA, OUTPUT)
#define OW_RELEASE() pinMode(OWIRE_DATA, INPUT)
#define OW_READ() digitalRead(OWIRE_DATA)



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
    // initialize overflow counter variable
    //tot_overflow = 0;
    // set up timer with prescaler = 0
    TCCR1B &=~(B00000111 <<CS10);
    Serial.print("TCCR1B ");
    Serial.println(TCCR1B, BIN);
    Serial.print("TCCR1A ");
    Serial.println(TCCR1A, BIN);
    TCCR1A&=0;
    TCCR1B |= (B00000001 << CS10);
    // TODO prescaler=64
//    TCCR1B |= (B00000011 << CS10);
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
      pinMode(OWIRE_DATA, OUTPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(2); // 1<T<15 us
      pinMode(OWIRE_DATA, INPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(15+15+30); // Recovery 1us<T
    }
    else
    {
      pinMode(OWIRE_DATA, OUTPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(90); // 60<T<120 us
      pinMode(OWIRE_DATA, INPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(10); // Recovery 1us<T
    }
    data>>=1;
  }
}

uint8_t owireReceiveBit()
{
    pinMode(OWIRE_DATA, OUTPUT);
    digitalWrite(OWIRE_DATA, LOW);
    delayMicroseconds(2); // 1<T<15 us
    pinMode(OWIRE_DATA, INPUT);
    digitalWrite(OWIRE_DATA, LOW);
    
    delayMicroseconds(2); //  58>T>13us
    
    uint8_t sample=digitalRead(OWIRE_DATA);
    
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

boolean owireReceiveBytes(uint8_t * tgBuffer, uint8_t nByte)
{
  for(uint8_t i=0;i<nByte;++i)
  {
     tgBuffer[i]=owireReceive();
  }
  uint8_t crc=owireCRC(0, 1);
  for(uint8_t i=0;i<nByte-1;++i)
  {
    crc=owireCRC(tgBuffer[i], 0);
  }
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

void owInit()
{
  owStatus.initialized=0;
}

void ow_ActionFinished();
void ow_Send();

void ow_Send_pulse3()
{
  sei();

    if(owStatus.bit>=8)
    {
      owStatus.currentByte++;
      if(owStatus.currentByte<owStatus.nByte)
      {
        owStatus.bit=0;
  Serial.print("Send: ");
  Serial.println(owStatus.data[owStatus.currentByte], HEX);
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
/*  
  for(int i=0;i<8;++i)
  {
    if(data&0x01)
    {
      pinMode(OWIRE_DATA, OUTPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(2); // 1<T<15 us
      pinMode(OWIRE_DATA, INPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(15+15+30); // Recovery 1us<T
    }
    else
    {
      pinMode(OWIRE_DATA, OUTPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(90); // 60<T<120 us
      pinMode(OWIRE_DATA, INPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(10); // Recovery 1us<T
    }
    data>>=1;
  }
*/
}

void ow_Read_pulse3()
{
  sei();
  if(owStatus.bit<8)
  {
    ow_Read();
  }else
  {
//    Serial.print("Received: ");
//    Serial.println(owStatus.data[owStatus.currentByte]);
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

/*void ow_Read_pulse2()
{
  uint8_t sample=OW_READ();
  owStatus.data[owStatus.currentByte]>>=1;
  owStatus.data[owStatus.currentByte]|=sample?(uint8_t)0x80:0;
  owStatus.bit++;
  TIMER_TRIGGER(60, ow_Read_pulse3);
}
*/

/*void ow_Read_pulse1()
{
  OW_RELEASE();  
  TIMER_TRIGGER(2, ow_Read_pulse2);
}
*/

void ow_Read()
{
  OW_LOW();
//  TIMER_TRIGGER(2, ow_Read_pulse1);
// TODO this part is best executed without interrupts - by hand timing

  OW_RELEASE();  
  uint8_t sample=OW_READ();
  owStatus.data[owStatus.currentByte]>>=1;
  owStatus.data[owStatus.currentByte]|=sample?(uint8_t)0x80:0;
  owStatus.bit++;
  TIMER_TRIGGER(60, ow_Read_pulse3);
}
void ow_SendAll()
{
  owStatus.bit=0;
  owStatus.currentByte=0;
  Serial.print("Send: ");
  Serial.println(owStatus.data[owStatus.currentByte], HEX);
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
  for(uint8_t i=0;i<owStatus.nByte-1;++i)
  {
    Serial.print(owStatus.data[i], HEX);
    Serial.print(", ");
    crc=owireCRC(owStatus.data[i],0);
  }
  Serial.print("CRC ");
  Serial.print(crc, HEX);
  Serial.print(" ");
  Serial.println(owStatus.data[owStatus.nByte-1], HEX);
  return crc!=owStatus.data[owStatus.nByte-1];
}
void ow_ActionFinished()
{
  sei();
    Serial.print("OW state: ");
  Serial.println(owStatus.istate);
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
          Serial.println("Wait a lot of time!");
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
        Serial.println(err);
        owStatus.state=err?OW_ERROR_CRC:6;
        break;
      }
      case OW_STEP_CHECK_SCRATCHPAD:
      {
        boolean err=ow_CheckCRC();
        Serial.println(err);
        if(!err)
        {
          uint16_t data=owStatus.data[1]&B00000111;
          uint8_t signum=owStatus.data[1]&B11111000;
          data<<=8;
          data|=owStatus.data[0];
          if(signum)
          {
            data=-data;
          }
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

uint8_t sensorState=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  digitalWrite(OWIRE_GND, LOW);
  pinMode(OWIRE_GND, OUTPUT);
  digitalWrite(OWIRE_GND, LOW);
  
  pinMode(OWIRE_DATA, INPUT);
  digitalWrite(OWIRE_DATA, LOW);
  
  pinMode(OWIRE_VCC, OUTPUT);
  digitalWrite(OWIRE_VCC, HIGH);
  sensorState=0;
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  timer1_init();
  owInit();
}

void handle_println()
{
  sei();
  Serial.println("From handler!");
}


void loop() {
  /*
  uint8_t buffer[9];
  boolean presence=owireReset();
  
  if(presence)
  {
    owireSend(0x33); // Read ROM command
  
    if(owireReceiveBytes(buffer, 8))
    {
      Serial.println("ROM ID received!");
      Serial.print("{");
      for(int i=0;i<7;++i)
      {
        Serial.print(buffer[i], HEX);
        Serial.print(", ");
      }
      Serial.println("}");
    }else
    {
      Serial.println("ROM ID CRC error!");
    }
  }else
  {
    sensorState=0;
    Serial.println("Device present not received");
  }
  presence=owireReset();
  if(presence)
  {
      if(!sensorState)
      {
        Serial.println("Reconfigure sensor!");
        owireSend(0xCC); // Skip ROM command - we have only one sensor on the line.
        owireSend(0x4E); // Write scratchpad - Configure the device
        owireSend(0);
        owireSend(0);
        owireSend(B01100000);
        sensorState=1;
        presence=owireReset();
      }
      if(presence)
      {
        owireSend(0xCC); // Skip ROM command - we have only one sensor on the line.
        owireSend(0x44); // Convert temperature
        while(owireReceiveBit()==0)
        {
           // wait for temperature read ready. TODO this point is possible deadlock if device fails
        }
        presence=owireReset();
        owireSend(0xCC); // Skip ROM command - we have only one sensor on the line.
        owireSend(0xBE); // Read scratchpad
        if(owireReceiveBytes(buffer, 9))
        {
          uint16_t data=buffer[1]&B00000111;
          uint8_t signum=buffer[1]&B11111000;
          data<<=8;
          data|=buffer[0];
          float valueT=((float)data)/16.0f;
          if(signum)
          {
            valueT=-valueT;
          }
          Serial.println("Scratchpad read successfully!");
          Serial.println(valueT);
        }else
        {
          for(uint8_t i=0;i<9;++i)
          {
            Serial.println(buffer[i],HEX);
          }
          Serial.println("Error reading scratchpad");
        }
      }else
      {
        sensorState=0;
      }
  }else
  {
    sensorState=0;
  }
  */
//  Serial.println(tot_overflow);
//static uint32_t t;
//uint32_t a=micros();
 // Serial.println(a-t);
  //t=a;
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
