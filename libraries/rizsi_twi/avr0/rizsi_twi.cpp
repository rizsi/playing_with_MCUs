#include <Arduino.h>
#include <configure_twi.h>
#include <rizsi_TWI.h>
#include <util/twi.h>
#include <avr/interrupt.h>



#define TWI_FREQ 100000

/// When the bus is idle fill the current buffers and start a new sending cycle with interrupts enabled.
static void twi_feed(uint8_t error);

static uint8_t twiInited=0;
static twiFillCommand twiFeed;
static uint8_t twiLength;
static const uint8_t * twiData;
static uint8_t twiAt=0;
static uint8_t twiAddress;
static uint8_t twiCommand;


// Wait until the bus is idle
static bool waitIdle();

// Wait for a TWI state with timeout
// @return non zero means error
static uint8_t waitState(uint8_t waitValue);


static bool waitIdle()
{
	while(1)
	{
		uint8_t v=TWI0.MSTATUS&0b11;
		if(v==0 || v==1)
		{
			// Bus state unknown or idle
			return false;
		}
		// twiDebugMessage("WI\n");
		// owener, busy: do not return
	}
	// TODO timeout and return error
}


////////////////////////////////////////////////////////////////
// I2C Interrupt
////////////////////////////////////////////////////////////////
ISR(TWI0_TWIM_vect){
	uint8_t currentStatus = TWI0.MSTATUS;

	// If arbitration lost
	if (currentStatus & TWI_ARBLOST_bm) {
		TWI0.MSTATUS |=	TWI_ARBLOST_bm | TWI_BUSERR_bm | TWI_WIF_bm;
		twiDebugMessage("TWI ArbLoss\r\n");
		twi_feed(1);
	}

	// If  bus error
	if (currentStatus & TWI_BUSERR_bm) {
		TWI0.MSTATUS |=	TWI_ARBLOST_bm | TWI_BUSERR_bm | TWI_WIF_bm;
		twiDebugMessage("TWI BusErr\r\n");
		twiDebugMessageNumber(currentStatus);
		twi_feed(1);
	}

	// If master write
	else if (currentStatus & TWI_WIF_bm) {
		twiDebugMessage("TWI WIF\r\n");
		// Is NAK
		if (currentStatus & TWI_RXACK_bm) {
			TWI0.MCTRLB = TWI_MCMD_STOP_gc;
			twiDebugMessage("TWI NACK\r\n");
			twi_feed(1);
		}
		
		// Send next
		if(twiAt==255)
		{
			TWI0.MDATA = twiCommand;
			twiAt++;
		}else if(twiAt<twiLength)
		{
			TWI0.MDATA = twiData[twiAt];
			twiAt++;
		}else
		{
			twiDebugMessage("TWI FEED\r\n");
			// Sent completely - set up next send cycle
			twi_feed(0);
		}
	}
	/* If unexpected state */
	else {
		twiDebugMessage("TWI UNEXP\r\n");
		twiDebugMessageNumber(currentStatus);
		twi_feed(1);
	}
}

static uint8_t waitState(uint8_t waitValue)
{
  uint32_t ctr=0;
  while((TWI0.MSTATUS & waitValue )==0)
  {
    twiDebugMessageNumber(TWI0.MSTATUS);
    twiDebugMessage("\r\n");
    ctr++;
    if(ctr>16000)
    {
    	twiDebugMessage("TWI error - waitValue never received waitfor:");
    	twiDebugMessageNumber(waitValue);
    	twiDebugMessage(" MSTATUS: ");
    	twiDebugMessageNumber(TWI0.MSTATUS);
    	twiDebugMessage("\r\n");
	return 1;
    }
  }
  if(TWI0.MSTATUS & TWI_BUSERR_bm)
  {
    	twiDebugMessage("BUSERR MSTATUS: ");
    	twiDebugMessageNumber(TWI0.MSTATUS);
  }
  return 0;
}

// Setup the TWI system
void twiInit()
{
  if(!twiInited)
  {
	  twiInited=1;
	  
	  // Setting up the pins have to be done by caller
	  

	  TWI0.MBAUD = (uint8_t)((F_CPU / 2 / TWI_FREQ) - 5);
	  TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
//	  TWI0.MCTRLA =	TWI_RIEN_bm | TWI_WIEN_bm | TWI_ENABLE_bm;
	  TWI0.MCTRLA =	TWI_ENABLE_bm;
  }
}

void twiStop()
{
  TWI0.MCTRLA =	0;
}
void twiEndTransmission()
{
	if(waitState(TWI_WIF_bm))
	{
		return; // TODO report error
	}
	TWI0.MCTRLB = TWI_MCMD_STOP_gc;
	waitIdle();
	twiStop();
	return;
}


uint8_t twiBeginTransmission(uint8_t sla)
{
  TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
  TWI0.MCTRLA =	TWI_ENABLE_bm;
  if(waitIdle())
  {
	twiDebugMessage("WIERR\n");
  	return 1;
  }
  twiDebugMessage("TWIBEGINWRITE\r\n");
  twiDebugMessageNumber(TWI0.MSTATUS);
  // Send TWI Address
  TWI0.MADDR = (sla<<1) | TW_WRITE;
  return 0;
}

uint8_t twiWrite(uint8_t data)
{
	twiDebugMessage("TWIWrite\r\n");
	if(waitState(TWI_WIF_bm))
	{
		return 1;
	}
	twiDebugMessage("TWIWrite2\r\n");
	TWI0.MDATA=data;
	return 0;
}
static void twi_feed(uint8_t error)
{
  if(error)
  {
    twiDebugMessage("TWIFeed ERROR\r\n");
    twiFeed(NULL, NULL, NULL);
    TWI0.MCTRLA &= ~TWI_WIEN_bm;
  }else{
    if((twiLength=twiFeed(&twiAddress, &twiData, &twiCommand))!=0)
    {
      twiAt=255;
      twiDebugMessage("TWIFeed Send address...\r\n");
      twiDebugMessageNumber(TWI0.MSTATUS);
      // Send start condition and address
      TWI0.MSTATUS |=	TWI_ARBLOST_bm | TWI_BUSERR_bm | TWI_WIF_bm; // Clear interrupt condition and error markers
      twiDebugMessageNumber(TWI0.MSTATUS);
      TWI0.MCTRLA = TWI_WIEN_bm | TWI_ENABLE_bm;
      TWI0.MADDR = (twiAddress<<1) | TW_WRITE;
    }else
    {
	twiDebugMessage("TWIFeed END\r\n");
	TWI0.MCTRLA &= ~TWI_WIEN_bm;
	TWI0.MCTRLB = TWI_MCMD_STOP_gc;
    }
  }
}
void twiBulkData(twiFillCommand feed)
{
  TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
  TWI0.MCTRLA =	TWI_ENABLE_bm;
  if(waitIdle())
  {
	twiDebugMessage("WIERR\n");
	twi_feed(1);
  	return;
  }
  twiFeed=feed;
  twiDebugMessage("twiBulkData: ");
  TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
  twi_feed(0);
}
