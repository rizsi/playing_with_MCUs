/*
  infra receiver code for TSOP 4838
  The receiver can be connectd directly to the Ardino pins: 5-6-7
  facing outwards of the Arduino.
 */

//   (direction is important, see datasheet of TSOP 4838
//    on the table facing up with the legs towards you)

int datain=5; // IR input - left leg of TSOP 4838
int gnd=6;    // GND - middle leg of TSOP 4838
int Vs=7;     // Vs - right leg of TSOP 4838
int led = 13; // LED pin

// Maximum length of a single signal - in microseconds
#define MAXSIGNALTIME 500000

// Maximum number of signal segments - the measured pieces of a signal
#define MAXSIGNALSEGMENTS 100

//const uint16_t variableName[] PROGMEM = {data0, data1, data3...};
#include "neoelec.h"
#define POSSIBLESIGNAL (sizeof(signalSamples)/2/MAXSIGNALSEGMENTS)
#define MAXERROR 150


// State of pulse length receiver:
long timeSignalLast;
uint8_t currentSegment=0;
uint16_t segments[256];

/// Based on http://playground.arduino.cc/Main/PinChangeInterrupt
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
   long t=micros();
   uint8_t input=digitalRead(datain);
   segments[currentSegment]=(uint16_t)(t-timeSignalLast);
   currentSegment++;
   timeSignalLast=t;
//  Uncommenting this line helps debugging whether something happens or not
   digitalWrite(led,input);
}
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the pins communicationg with the receiver.
  digitalWrite(datain, HIGH);
  pinMode(datain, INPUT);
  
   *digitalPinToPCMSK(datain) |= bit (digitalPinToPCMSKbit(datain));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(datain)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(datain)); // enable interrupt for the group 

  digitalWrite(gnd, LOW);
  pinMode(gnd, OUTPUT);
  digitalWrite(Vs, HIGH);
  pinMode(Vs, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
void printValue(uint8_t processed, uint16_t value)
{
    Serial.print(value);
    if((processed&0x0F)==0x0f)
    {
      Serial.println(',');
    }else
    {
      Serial.print(',');
    }
}
uint16_t getSample(uint8_t sampleIndex, uint8_t segmentIndex)
{
  pgm_read_word_near(signalSamples+(((uint16_t)sampleIndex)*MAXSIGNALSEGMENTS)+segmentIndex);
}

void decode()
{
  static uint8_t processed=0;
  static uint8_t signalStartAt=0;
  static uint8_t match[POSSIBLESIGNAL]={0,0,0,0,0,
0,0,0,0,
0,0,0,0,0,0,0,0,0};
  boolean finished=false;
  cli();
    long t=micros();
    if(t-timeSignalLast>MAXSIGNALTIME)
    {
      // TODO Too long wait time - log last code
      timeSignalLast=t;
      finished=signalStartAt!=currentSegment;
    }
  sei();

  while(processed!=currentSegment)
  {
    uint16_t val=segments[processed];
    for(uint8_t i=0;i<POSSIBLESIGNAL;++i)
    {
       uint16_t sample=getSample(i, match[i]);
       if(sample-MAXERROR <val && sample+MAXERROR>val)
       {
         match[i]++;
         // Decode is still ok for this sample
         if(match[i]<MAXSIGNALSEGMENTS && getSample(i, match[i])==0)
         {
             Serial.print("Decoded! ");
             Serial.print(match[i]);
             Serial.print(" ");
             Serial.println(i);
              signalStartAt=processed+1;
              match[i]=0;
         }
       }else
       {
         match[i]=0;
       }
    }
//    Serial.println(val);
    processed++;
  }
  if(finished)
  {
    uint8_t idx=0;
    Serial.println("Unkown: ");
    signalStartAt++;
    while(signalStartAt!=currentSegment)
    {
       uint16_t val=segments[signalStartAt];
       printValue(idx, val);
       signalStartAt++;
       idx++;
    }
    while(idx<MAXSIGNALSEGMENTS)
    {
       printValue(idx, 0);
       idx++;
    }
    Serial.println("");
    signalStartAt=currentSegment;
  }
  /*
  static uint8_t n=0;
  static uint32_t possibleDecodes=0xFFFFFFFFl;
  static uint32_t processSum=0;
  static uint16_t received[MAXSIGNALSEGMENTS];
  boolean finished=false;
  cli();
   while(currentSegment>n)
   {
     received[n]=segments[n];
     n++;
   }
   if(decoding&&(t-timeSignalStart)>MAXSIGNALTIME)
   {
     decoding=false;
     currentSegment=0;
     finished=true;
   }
  sei();
  while(n>processed)
  {
    uint16_t val=received[processed];
    processSum+=val;
    for(uint8_t i=0;i<POSSIBLESIGNAL;++i)
    {
      uint32_t mask=1<<i;
      if(possibleDecodes&mask)
      {
        uint16_t sample=getSample(i, processed);
        if(sample-MAXERROR <val && sample+MAXERROR>val)
        {
          // Decode is still ok for this sample
          if(processed<MAXSIGNALSEGMENTS-1)
          {
            if(getSample(i, processed+1)==0)
            {
              Serial.print("Decoded! ");
              Serial.print(processed);
              Serial.print(" ");
              Serial.println(i);
            }
          }
        }else
        {
              Serial.print("FAIL ");
              Serial.print(processed);
              Serial.print(" ");
              Serial.println(i);
          // Clear this possibility from the mask!
          possibleDecodes&=~mask;
        }
      }
    }
    processed++;
  }
  if(finished)
  {
    if(1)
    {
      Serial.print("processed: ");
      Serial.println(processed);
      processed=0;
      Serial.println("uint16_t diffs[]={");
      while(n>processed)
      {
        uint16_t val=received[processed];
        printValue(processed, val);
        received[processed]=0;
        processed++;
      }
      while(processed<MAXSIGNALSEGMENTS)
      {
        printValue(processed, 0);
        received[processed]=0;
        processed++;
      }
      Serial.println();
      Serial.print("}; // N samples, sum:");
      Serial.print(n);
      Serial.print(" ");
      Serial.println(processSum);
      Serial.println(sizeof(signalSamples));
    }
    processed=0;
    processSum=0;
    possibleDecodes=0xFFFFFFFFl;
    n=0;
  }
  */
}

// the loop routine runs over and over again forever:
void loop() {
  decode();
}

