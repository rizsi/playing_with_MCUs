/**
 * Example that works on a D13-12864-SPI type OLED. Tested on a cheap crappy OLED module that has no CS pin.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <rizsi_DRAW.h>


#define RES 4
#define DC 3

static uint8_t frame[1024];

static uint8_t SPItransfer(uint8_t d)
{
  while(!(SPSR & (1<<SPIF)));
  uint8_t x=SPDR;
  SPDR = d;
  return x;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  DDRB |= (1<<2)|(1<<3)|(1<<5);    // SCK, MOSI and SS as outputs
  DDRB &= ~(1<<4);                 // MISO as input

  SPCR |= (1<<MSTR);               // Set as Master
  SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128
//  SPCR |= (1<<SPIE);               // Enable SPI Interrupt
  SPCR |= (1<<SPE);                // Enable SPI
  SPDR = 0xAF;

  pinMode(RES, OUTPUT);
  pinMode(DC, OUTPUT);
  digitalWrite(RES, LOW);
  digitalWrite(DC, LOW);
  RD_init(frame);
}
void setPage(uint8_t page)
{
  SPItransfer(0xB0|page);
  SPItransfer(0x02); // TODO hack - I don't really understand why it is not 0 but 2
  SPItransfer(0x10);
}
static int32_t counter=0;
void loop() {
  RD_clearScreen();
//  RD_STRING("demo\n");
  RD_drawNumber(counter, 10);
  digitalWrite(RES, HIGH);
  // 14MHz clock selected: it works but probably it is slower that is capable of an UNO
//  SPIbeginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));

//  SPI.transfer(0xAF);  // TURN on
  uint16_t index=0;
  for(uint8_t p=0;p<8;++p)
  {
    setPage(p);
    digitalWrite(DC, HIGH);
    for(uint16_t l=0;l<128;++l)
    {
      SPItransfer(frame[index]); 
//      SPI.transfer(0xff);
      index++;
    }
    digitalWrite(DC, LOW);
  }
  SPItransfer(0xC0);  // vertical flip
  SPItransfer(0xA4);  // All pixels from GRAM
  SPItransfer(0xA6);  // no invert
  SPItransfer(0xAF);  // TURN on
  delay(200);
//  SPIendTransaction();
//  digitalWrite(RES, LOW);
  // put your main code here, to run repeatedly:
  counter++;
}
