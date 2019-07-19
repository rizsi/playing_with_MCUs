#include <pthread.h>

#define THREAD_PLATFORM_FIELDS 	pthread_t pthread; \
	void (* fun) ();


