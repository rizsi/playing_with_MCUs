#define OWIRE_GND 3
#define OWIRE_DATA 4
#define OWIRE_VCC 5




// 1 us: 16 instruction cycles
// Interrupt handling is in order of 4us (with pus and pop at the end)


uint8_t owireCRC(uint8_t data, boolean reset)
{
  static uint8_t crc=0;
  if(reset)
  {
    crc=0;
  }
//  Serial.println("CRC cycle");
  for(uint8_t i=0;i<8;++i)
  {
    uint8_t lsbXdataBit=(data&1)^(crc&1);
/*    Serial.print(lsbXdataBit);
    Serial.print(" ");
    Serial.print(data&1);
    Serial.print(" ");
    Serial.println(crc, BIN);*/
    crc=(crc>>1) | (crc<<7); // rotate 1 right
//    Serial.println(crc, BIN);
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
//      Serial.println("Send 1");
    }
    else
    {
      pinMode(OWIRE_DATA, OUTPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(90); // 60<T<120 us
      pinMode(OWIRE_DATA, INPUT);
      digitalWrite(OWIRE_DATA, LOW);
      delayMicroseconds(10); // Recovery 1us<T
//      Serial.println("Send 0");
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
//    Serial.println(sample);
    
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
  pinMode(OWIRE_DATA, OUTPUT);
  digitalWrite(OWIRE_DATA, LOW);
  delayMicroseconds(480);
  pinMode(OWIRE_DATA, INPUT);
  digitalWrite(OWIRE_DATA, LOW);
  delayMicroseconds(30);
  uint8_t presence=digitalRead(OWIRE_DATA);
  delayMicroseconds(450);
  return !presence; 
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
}


void loop() {
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
  delay(1000);
}
