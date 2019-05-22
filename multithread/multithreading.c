#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include "debug.h"

#include "multithreading-hwavr2560.h"
#include "multithreading.h"

#define low(x)   ((x) & 0xFF)
#define high(x)   (((x)>>8) & 0xFF)


/** The main thread */
static thread_t mainThread;

/** If not NULL and interrupt is executed then it is a Start this thread command */
static thread_t * toStart=NULL;
/** If not NULL and interrupt is executed then switch to the given thread from the current thread */
static thread_t * nextThread=NULL;
/** Store the current thread */
static thread_t * currentThread=NULL;
/** Current stack pointer just before calling the interrupt handler. Used to locate 
    the return address to overwrite in the interrupt handler. */
static uint16_t toStartStackpointer;
/** Start the new thread stack with this offset to the _original_ stack offset (top of RAM) */
static uint16_t toStartStackOffset;
void (* toStartFunction )();

/**
 * timer/Software interrupt that does the context switch between threads.
 */
ISR(TIMER1_OVF_vect, ISR_NAKED)
{
	pushAll();
	if(toStart!=NULL)	// SW interrupt to create a new thread
	{
		uint16_t currentStackPointer=SPL+(SPH<<8);
		uint16_t nByte=toStartStackpointer-currentStackPointer;
		uint8_t * stackPointer=(uint8_t *)ORIGINAL_STACK_TOP-toStartStackOffset;
		memcpy(stackPointer-nByte+1, (void *)currentStackPointer+1, nByte-FUNCTION_POINTER_BYTES);
		*(stackPointer)=low((uint16_t)toStartFunction);
		*(stackPointer-1)=high((uint16_t)toStartFunction);
		*(stackPointer-2)=0;	// All named functions are mapped to below 128k by avrgcc

		toStart->currentStackpointer=(uint16_t)stackPointer-nByte;
		toStart=NULL;
	}else if(nextThread!=NULL)	// SW interrupt to switch to an other thread
	{
		uint8_t stpH=high(nextThread->currentStackpointer);
		uint8_t stpL=low(nextThread->currentStackpointer);
		currentThread->currentStackpointer=SPL+(SPH<<8);
		currentThread=nextThread;
		nextThread=NULL;
		SPL=stpL;
		SPH=stpH;
	}

	if(TIFR1&_BV(TOV1))	// HW interrupt
	{
		sendByte('X');
		// TODO implement round robin or whatever
	}
	popAll();
	reti();
}

void thread_system_init()
{
	currentThread=&mainThread;
}
void thread_create(thread_t * startThread, void (* fun) (), uint16_t stackOffset)
{
	cli();
	toStart=startThread;
	toStartStackpointer=SPL+(SPH<<8);
	toStartFunction=fun;
	toStartStackOffset=stackOffset;
	TIMER1_OVF_vect();
}

void thread_switch(thread_t * thread_to)
{
	cli();
	nextThread=thread_to;
	TIMER1_OVF_vect();
}
thread_t * thread_get_main()
{
	return &mainThread;
}


