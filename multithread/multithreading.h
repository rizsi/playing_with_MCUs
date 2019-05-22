
// Multithreading library for AVR 8 bit microcontrollers.

// Function pointers are two bytes. Instructions are aligned to 2 bytes so it addresses 128k
// Upper than 128k is not directly addressable using function pointers: functions that's
// pointers are used are located into the lower 128k by linker.
// (Or trampulins are used to jump to the higher area.)
typedef struct
{
	// When the thread is freezed the stack pointer to return to the thread is stored here
	uint16_t currentStackpointer;
} thread_t;

/**
 * Initialize the threading subsystem before anything else.
 */
extern void thread_system_init();
/**
 * Create a new thread.
 * @param startThread thread structure provided by caller.
 * @param fun function that executes the thread. (Current implementation it has to be an  endless loop, must not return!)
 * @param stackOffset Start the new thread stack with this offset to the _original_ stack offset (top of RAM)
 */
extern void thread_create(thread_t * startThread, void (*fun)(), uint16_t stackOffset);

/**
 * Switch execution to the thread.
 */
extern void thread_switch(thread_t * thread_to);

/**
 * Get the main thread - the one that called thread_system_init() and was not created but existed for eternity.
 */
extern thread_t * thread_get_main();

