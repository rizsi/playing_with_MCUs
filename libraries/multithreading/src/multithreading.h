
// Multithreading library for AVR 8 bit microcontrollers.

#include "multithreading-platform.h"

// Function pointers are two bytes. Instructions are aligned to 2 bytes so it addresses 128k
// Upper than 128k is not directly addressable using function pointers: functions that's
// pointers are used are located into the lower 128k by linker.
// (Or trampulins are used to jump to the higher area.)
typedef struct
{
	THREAD_PLATFORM_FIELDS
} thread_t;

/// This function is called on each HW timer interrupt.
/// @return thread id to switch to or NULL means no switch is necessary.
typedef thread_t *(* schedulerFunction )();

/**
 * Initialize the threading subsystem before anything else.
 */
extern void thread_system_init(schedulerFunction myscheduler);
/**
 * Create a new thread.
 * @param startThread thread structure provided by caller.
 * @param fun function that executes the thread. (Current implementation it has to be an  endless loop, must not return!)
 * @param stackOffset Start the new thread stack with this offset to the _original_ stack offset (top of RAM).
 *						The usable stack size of the thread can be counted using this number.
 *						35 bytes (depends on CPU type) is used to store thread state.
 */
extern void thread_create(thread_t * startThread, void (*fun)(), uint16_t stackOffset);

/**
 * Switch execution to the thread.
 */
extern void thread_switch(thread_t * thread_to);

/**
 * Enter critical section - thread switch is not possible inside this section.
 * (On preemptive implementation in simulation (pthread) these sections are protected by a single mutex)
 * Interrupts are not disbled within the critical section but all thread switches will be postponed until
 * critical section is left.
 */
extern void thread_critical_section_enter();
/**
 * Leave critical section - thread switch is not possible inside this section.
 * (On preemptive implementation in simulation (pthread) these sections are protected by a single mutex)
 */
extern void thread_critical_section_leave();

/**
 * Get the main thread - the one that called thread_system_init() and was not created but existed for eternity.
 *
 * If it is used as a scheduler function then on each timer interrupt the main thread is activated.
 */
extern thread_t * thread_get_main();

