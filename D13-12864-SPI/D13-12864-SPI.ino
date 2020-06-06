/**
 * Example that works on a D13-12864-SPI type OLED. Tested on a cheap crappy OLED module that has no CS pin.
 * 
 * Implementation updates screen in background implemented by SPI interrupts.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/// In-memory monochrome pixel draw library
#include <rizsi_DRAW.h>

/// Reset line of OLED module
#define RES 4
/// Data/Command select line of OLED module
#define DC 3

/// Storage of a single frame 128x64 pixels 1 bit/pixel
static uint8_t frame[1024];

static bool flipY=true;
static bool flipX=true;

/// State machine state of screen update
static volatile uint8_t st=0;
/// Current byte within the current page
static uint8_t byteIndex=0;
/// Current page
static uint8_t pageIndex=0;
/// Current byte index to send from the framebuffer
static uint16_t OLEDindex=0;

inline static void SPIsend(uint8_t d)
{
  SPDR = d;
}

ISR (SPI_STC_vect)
{
  switch(st)
  {
    case 0:
      SPIsend(0x00);
      st++;
      break;
    case 1:
      SPIsend(0x10);
      st++;
      break;
    case 2:
      digitalWrite(DC, LOW);
      SPIsend(0xB0|pageIndex);
      st++;
      break;
    case 3:
      digitalWrite(DC, HIGH);
      SPIsend(0);
      st++;
      break;
    case 4:
      SPIsend(0);
      st++;
      break;
    case 5:
      SPIsend(frame[OLEDindex]);
      OLEDindex+=flipX?((uint16_t)0xFFFF):((uint16_t)1);
      byteIndex++;
      if(byteIndex>127)
      {
        byteIndex=0;
        pageIndex++;
        if(pageIndex>7)
        {
               st=100;
        }else
        {
          st++;
          if(flipX)
          {
            OLEDindex+=256;
          }
        }
      }
      break;
    case 6:
      SPIsend(0);
      st++;
      break;
    case 7:
      SPIsend(0);
      st=2;
      break;
    case 100:
      digitalWrite(DC, LOW);
      if(flipY)
      {
        SPIsend(0xC8);  // vertical flip ON
      }else
      {
        SPIsend(0xC0);  // vertical flip OFF
      }
      st++;
      break;
    case 101:
     SPIsend(0xA4);  // All pixels from GRAM
      st++;
      break;
    case 102:
      SPIsend(0xA6);  // no invert
      st++;
      break;
    case 103:
      SPIsend(0xAF);  // TURN on
      st=127;
      break;
    case 127:
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  DDRB |= (1<<2)|(1<<3)|(1<<5);    // SCK, MOSI and SS as outputs
  DDRB &= ~(1<<4);                 // MISO as input

  // MAx freq: 400kHz
  SPCR |= (1<<MSTR);               // Set as Master
  // if divider is 4 if not set up: about 100FPS is achieved and it works even though it is much higher than specification
  SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128 -> 125kHz: within specification about 10FPS
  SPCR |= (1<<SPIE);               // Enable SPI Interrupt
  SPCR |= (1<<SPE);                // Enable SPI

  pinMode(RES, OUTPUT);
  pinMode(DC, OUTPUT);
  digitalWrite(RES, LOW);
  digitalWrite(DC, LOW);
  RD_init(frame);
}
static int32_t counter=0;
void loop() {
  // Draw the screen in memory
  RD_clearScreen();
  RD_STRING("AAA\nalma\nkorte\nszilva---------\n");
  RD_drawNumber(counter, 10);
  digitalWrite(RES, HIGH);

  // Setup state machine intial states
  st=0;
  byteIndex=0;
  pageIndex=0;
  OLEDindex=flipX?127:0;
  SPI_STC_vect(); // Start ISR to trigger the state machine
  
  while(st!=127); // Wait until screen was refreshed (In a real program we do useful stuff here)
  counter++;
}
