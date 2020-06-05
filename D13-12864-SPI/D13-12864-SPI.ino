/**
 * Example that works on a D13-12864-SPI type OLED. Tested on a cheap crappy OLED module that has no CS pin.
 */
#include <SPI.h>
#include <rizsi_DRAW.h>


#define RES 4
#define DC 3

static uint8_t frame[1024];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  pinMode(RES, OUTPUT);
  pinMode(DC, OUTPUT);
  digitalWrite(RES, LOW);
  digitalWrite(DC, LOW);
  RD_init(frame);
}
void setPage(uint8_t page)
{
  SPI.transfer(0xB0|page);
  SPI.transfer(0x02); // TODO hack - I don't really understand why it is not 0 but 2
  SPI.transfer(0x10);
}
static int32_t counter=0;
void loop() {
  RD_clearScreen();
  RD_drawNumber(counter, 10);
  digitalWrite(RES, HIGH);
  // 14MHz clock selected: it works but probably it is slower that is capable of an UNO
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));

//  SPI.transfer(0xAF);  // TURN on
  uint16_t index=0;
  for(uint8_t p=0;p<8;++p)
  {
    setPage(p);
    digitalWrite(DC, HIGH);
    for(uint16_t l=0;l<128;++l)
    {
      SPI.transfer(frame[index]); 
//      SPI.transfer(0xff);
      index++;
    }
    digitalWrite(DC, LOW);
  }
  SPI.transfer(0xC0);  // vertical flip
  SPI.transfer(0xA4);  // All pixels from GRAM
  SPI.transfer(0xA6);  // no invert
  SPI.transfer(0xAF);  // TURN on
  SPI.endTransaction();
//  digitalWrite(RES, LOW);
  // put your main code here, to run repeatedly:
  counter++;
}

