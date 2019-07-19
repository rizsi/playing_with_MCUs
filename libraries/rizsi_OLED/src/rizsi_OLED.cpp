#include <Arduino.h>
#include <util/twi.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "characters.h"
#include <rizsi_TWI.h>

#define MAIN_ADDRESS 0B0111100

#define OLED_I2C_ADDRESS (MAIN_ADDRESS)
#define OLED_WIDTH 128



uint8_t * oledFramebuffer;


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
    case 23:
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
    case 0:
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
  // Serial.println("Wait for boot...");
  delay(1000);
  // Serial.println("Send first command");
  delay(100);
  oledCommand(0xaf); // Circuits on
  // Serial.println("Circuits on");
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

