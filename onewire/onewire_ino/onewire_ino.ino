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

#define TIMER_TRIGGER(us, handler) timer_handler=handler; TCNT1=-((int16_t)us*16); TIFR1|=_BV(TOV1); TIMSK1 |= _BV(TOIE1)
//#define TIMER_TRIGGER(us, handler) timer_handler=handler; TCNT1=0x0; TIFR1=_BV(TOV1); TIMSK1 |= _BV(TOIE1); TCCR1B |= B00000001

#define OW_LOW()  pinMode(OWIRE_DATA, OUTPUT); digitalWrite(OWIRE_DATA, LOW)
#define OW_RELEASE() pinMode(OWIRE_DATA, INPUT); digitalWrite(OWIRE_DATA, LOW)
#define OW_READ() digitalRead(OWIRE_DATA)



typedef void (*TIMEOUT_HANDLER)(void);
TIMEOUT_HANDLER timer_handler;
// TIMER1 overflow interrupt service routine
// called whenever TCNT1 overflows
ISR(TIMER1_OVF_vect)
{
  // Disable counter
//  TCCR1B &=~(B00000111 <<CS10);

//  TCNT1H=0;
//    TCCR1B &= ~(B00000111 << CS10);
  // Disable overflow interrupt
    TIMSK1 &= ~_BV(TOIE1);
    // keep a track of number of overflows
    //tot_overflow++;
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
    /*
    Serial.print(i);
    Serial.print(" ");
    Serial.print(data&1);
    Serial.print(" bit CRC ");
    Serial.println(crc, BIN);*/
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

uint32_t t=0;
volatile uint8_t owStatus;

void owReset_read()
{
//  sei();
 // Serial.println("owRead");
  uint8_t presence=OW_READ();
  owStatus=presence?1:2;
}
void owReset_release()
{
  uint32_t a=micros();
  t=a-t;
  sei();
  Serial.println("owRelease");
  Serial.println(t);
//  Serial.println(a);

  OW_RELEASE();
  TIMER_TRIGGER(30, owReset_read);
}

void owReset()
{
  sei();
 // Serial.println("owReset");
//  Serial.println(((int16_t)480*16));
  
  owStatus=0;
  OW_LOW();
  t=micros();
  TIMER_TRIGGER(1, owReset_release);  
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
static uint32_t t;
uint32_t a=micros();
  Serial.println(a-t);
  t=a;
  owReset();
  while(owStatus==0);
//  Serial.print("Presence: ");
//  Serial.println(owStatus);
//  TIMER_TRIGGER(1000, handle_println);
  delay(1000);
}
