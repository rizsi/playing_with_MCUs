/*
  infra receiver code for TSOP 4838
  The receiver can be connectd directly to the Ardino pins: 5-6-7
  facing outwards of the Arduino.
 */
 
// Current setting is written to EEPROM
#include <EEPROM.h>
#define EEADDR_DUTY 0

//   (direction is important, see datasheet of TSOP 4838
//    on the table facing up with the legs towards you)

/// IR input - left leg of TSOP 4838
#define datain 5
// GND - middle leg of TSOP 4838
#define gnd 6
// Vs - right leg of TSOP 4838
#define Vs 7
// LED pin
#define led 13
// PWM output
#define pwmOut 11
// Button input - internal pullup to 5V, button pulls to GND when pressed
#define button1 9
// Button input - internal pullup to 5V, button pulls to GND when pressed
#define button2 10

/// Repeat time of the button when user keeps it pressed
#define REPEATMILLIS 200

int16_t fadePwm=0; // Fading value - added to current PWM value to find the required power

#define PWMSTEP 32
#define PWMMIN 31
#define PWMMAX 255
#define FADEPERIODMILLIS 8
uint8_t pwmDuty=255;
uint8_t pwmDutyTarget=255;
uint32_t lampOnAtMillis;
//#define DEBUG

#define LAMPTIMEOUTMILLIS 900000l
// Maximum length of a single signal - in microseconds
#define MAXSIGNALTIME 500000

// Maximum number of signal segments - the measured pieces of a signal
#define MAXSIGNALSEGMENTS 160

//const uint16_t variableName[] PROGMEM = {data0, data1, data3...};
const uint16_t signalSamples[] PROGMEM={
#define NOELEC_BASE 0
#include "neoelec.h"
#define SAMSUNG_BASE NOELEC_N_BUTTONS
#include "samsung_ak59_00149a.h"
};
#define POSSIBLESIGNAL (sizeof(signalSamples)/2/MAXSIGNALSEGMENTS)
#define MAXERROR 160


// State of pulse length receiver:
long timeSignalLast;
uint8_t currentSegment=0;
uint16_t segments[256];
/// Previous input value on button1
uint8_t prevButton1=0;
/// Previous input value on button2
uint8_t prevButton2=0;

/// Based on http://playground.arduino.cc/Main/PinChangeInterrupt
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
   long t=micros();
   uint8_t input=digitalRead(datain);
   segments[currentSegment]=(uint16_t)(t-timeSignalLast);
   currentSegment++;
   timeSignalLast=t;
//  Uncommenting this line helps debugging whether something happens or not
//   digitalWrite(led,input);
}
// the setup routine runs once when you press reset:
void setup() {
  pwmDuty=0;
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
  pinMode(pwmOut, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
#ifdef DEBUG
  Serial.begin(9600);
#endif
}
#ifdef DEBUG
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
#endif
uint16_t getSample(uint8_t sampleIndex, uint8_t segmentIndex)
{
  pgm_read_word_near(signalSamples+(((uint16_t)sampleIndex)*MAXSIGNALSEGMENTS)+segmentIndex);
}
void setPWM(uint8_t duty)
{
  fadePwm=((int16_t)pwmDuty)-duty;
  if(duty!=0)
  {
    EEPROM.write(EEADDR_DUTY, duty);
  }
  pwmDuty=duty;
  updateOutput();
}
void updateOutput()
{
    digitalWrite(led, pwmDuty!=0);
    if(fadePwm!=0||pwmDuty!=0)
    {
      int16_t val=fadePwm+pwmDuty;
      if(val<0) val=0;
      if(val>255) val=255;
      analogWrite(pwmOut, (uint8_t)val);
    }else
    {
      digitalWrite(pwmOut, 0);
    }
}
void setLamp(boolean value)
{
  if(value)
  {
    uint8_t duty=EEPROM.read(EEADDR_DUTY);
    if(duty==0) duty=255;
    setPWM(duty);
  }else
  {
    setPWM(0);
  }
}
void decodedInput(uint8_t buttonIndex)
{
  uint32_t t=millis();
  uint32_t diffT=t-lampOnAtMillis;
  // On each button touch we reset the timeout
  lampOnAtMillis=t;
  if(NOELEC_VOL_PLUS==buttonIndex || SAMSUNG_VOL_PLUS==buttonIndex)
  {
    uint8_t next=pwmDuty+PWMSTEP;
    if(next<pwmDuty)
    {
      next=PWMMAX;
    }
    setPWM(next);
  }else if(NOELEC_VOL_MINUS==buttonIndex|| SAMSUNG_VOL_MINUS==buttonIndex)
  {
    uint8_t next=pwmDuty-PWMSTEP;
    if(next>pwmDuty)
    {
      next=PWMMIN;
    }
    setPWM(next);
  }else if(NOELEC_POWER==buttonIndex|| SAMSUNG_POWER==buttonIndex)
  {
    // Prevent sensing a single button press twice when in a short time - issue was reported by users :-)
    if(diffT>250)
    {
      setLamp(pwmDuty==0);
    }
  }
}
void timeoutLamp()
{
  static uint32_t lastFadeStepT;
  uint32_t t=millis();
  if(pwmDuty!=0)
  {
    if((uint32_t)(t-lampOnAtMillis) > LAMPTIMEOUTMILLIS)
    {
      setLamp(false);
    }
  }
  if(t-lastFadeStepT>FADEPERIODMILLIS)
  {
    if(fadePwm<0)
    {
      fadePwm++;
      updateOutput();
    }else if (fadePwm>0)
    {
      fadePwm--;
      updateOutput();
    }
    lastFadeStepT=t;
  }
}

void decode()
{
  static uint8_t processed=0;
  static uint8_t signalStartAt=0;
  static uint8_t match[POSSIBLESIGNAL]={0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0
};
  boolean finished=false;
  boolean clearAll=false;
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
#ifdef DEBUG
             Serial.print("Decoded! ");
             Serial.print(match[i]);
             Serial.print(" ");
             Serial.println(i);
#endif
             decodedInput(i);
              signalStartAt=processed+1;
              match[i]=0;
              clearAll=true;
              goto decoderExit; // See: https://xkcd.com/292/
         }
       }else
       {
         match[i]=0;
       }
    }
//    Serial.println(val);
    processed++;
  }
  decoderExit:
  if(finished)
  {
#ifdef DEBUG
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
#endif
    signalStartAt=currentSegment;
    clearAll=true;
  }
  if(clearAll)
  {
        for(uint8_t i=0;i<POSSIBLESIGNAL;++i)
    {
      match[i]=0;
    }
  }
}


void handleButtons()
{
  uint32_t t=millis();
  uint8_t b1=digitalRead(button1);
  boolean repeat=lampOnAtMillis+REPEATMILLIS-t>REPEATMILLIS;
  // TODO prell avoidance necessary?
  if(b1==LOW)
  {
    if(b1!=prevButton1 || repeat)
    {
    // On each button touch we reset the timeout
    lampOnAtMillis=t;
    uint8_t next=pwmDuty+PWMSTEP;
    if(next<pwmDuty)
    {
      next=PWMMAX;
    }
    setPWM(next);
    }
  }
  prevButton1=b1;
  uint8_t b2=digitalRead(button2);
  // TODO prell avoidance necessary?
  if(b2==LOW)
  {
    if(b2!=prevButton2 || repeat)
    {
    // On each button touch we reset the timeout
    lampOnAtMillis=t;
    uint8_t next=pwmDuty-PWMSTEP;
    if(next>pwmDuty)
    {
      next=0;
    }
    setPWM(next);
    }
  }
  prevButton2=b2;
}

// the loop routine runs over and over again forever:
void loop() {
  decode();
  handleButtons();
  timeoutLamp();
}

