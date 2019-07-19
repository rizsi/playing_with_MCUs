#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "../src/multithreading.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/** The main thread - not filled with real values because we do not really manage and switch threads
	because pthread does that.
	 */
static thread_t mainThread;


void thread_system_init()
{
	// NOOP on pthread implementation
}

void thread_set_scheduler(schedulerFunction myscheduler)
{
	// NOOP on pthread implementation
}
static void * mythreadfunc(void * param)
{
	thread_t * t=(thread_t *)param;
	t->fun();
}

// Thread create is moved to JNI so JNI callback is possible from these threads!

//void thread_create(thread_t * startThread, void (* fun) (), uint16_t stackOffset)
//{
//	startThread->fun=fun;
//	pthread_create(&(startThread->pthread), NULL, mythreadfunc, startThread);
//}

void thread_switch(thread_t * thread_to)
{
	// NOOP - On a normal operating system there is automatic preemption of tasks
}
thread_t * thread_get_main()
{
	return &mainThread;
}

void thread_critical_section_enter()
{
	pthread_mutex_lock(&mutex);
}
void thread_critical_section_leave()
{
	pthread_mutex_unlock(&mutex);
}


