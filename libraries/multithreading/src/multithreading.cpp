#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
// #include "debug.h"

// This interrupt vector is used for context switching
#define CONTEXT_SWITCH_INTERRUPT TIMER2_OVF_vect

#include "multithreading-platform.h"
#include "multithreading.h"

#define low(x)   ((x) & 0xFF)
#define high(x)   (((x)>>8) & 0xFF)


/** The main thread */
static thread_t mainThread;

/** !=0 means that the thread is in a critical section and must not be switched to other thread.
 */
static uint8_t inCriticalSection=0;

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
static void (* toStartFunction )();

static schedulerFunction scheduler;

/**
 * timer/Software interrupt that does the context switch between threads.
 */
ISR(CONTEXT_SWITCH_INTERRUPT, ISR_NAKED)
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
		// *(stackPointer-2)=0;	// All named functions are mapped to below 128k by avrgcc

		toStart->currentStackpointer=(uint16_t)stackPointer-nByte;
		toStart=NULL;
	}else if(nextThread!=NULL)
	{
		// SW interrupt to switch to an other thread
	}else if(TIFR1&_BV(TOV1))	// HW interrupt
	{
		nextThread=scheduler();
	}
	if(nextThread!=NULL && !inCriticalSection)
	{
		uint8_t stpH=high(nextThread->currentStackpointer);
		uint8_t stpL=low(nextThread->currentStackpointer);
		currentThread->currentStackpointer=SPL+(SPH<<8);
		currentThread=nextThread;
		nextThread=NULL;
		SPL=stpL;
		SPH=stpH;
	}
	popAll();
	reti();
}

void thread_system_init(schedulerFunction myscheduler)
{
	scheduler=myscheduler;
	currentThread=&mainThread;

//  TCCR2A = 0;
//  TCCR2B = 0;
//  TCNT2  = 0;
//  TCCR2A |= (1 << WGM21);
//  TCCR2B |= (1 << CS22)| (1<<CS20);   // /128 prescaler - about 488 overflows per second
//  TIMSK2 |= (1 << TOIE2);	// Enable overflow
}
void thread_create(thread_t * startThread, void (* fun) (), uint16_t stackOffset)
{
	cli();
	toStart=startThread;
	toStartStackpointer=SPL+(SPH<<8);
	toStartFunction=fun;
	toStartStackOffset=stackOffset;
	CONTEXT_SWITCH_INTERRUPT();
}

void thread_switch(thread_t * thread_to)
{
	cli();
	nextThread=thread_to;
	CONTEXT_SWITCH_INTERRUPT();
}
thread_t * thread_get_main()
{
	return &mainThread;
}

void thread_critical_section_enter()
{
	cli();
	inCriticalSection++;
	sei();
}
extern void thread_critical_section_leave()
{
	cli();
	inCriticalSection--;
	if(nextThread!=NULL)
	{
		thread_switch(nextThread);
	}
	sei();
}


