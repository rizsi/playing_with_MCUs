
#ifdef __AVR__

	#if __AVR_ARCH__==5
		#include "multithreading-hwavr-arch5.h"
	#else
		#error Multithreading is not implemented for this processor
	#endif

//	#ifdef __AVR_ARCH__==
//	#ifdef 
//		#include "multithreading-hwavr2560.h"
//	#else
//		#error Multithreading is not implemented for this processor
//	#endif
#else
	#include "../src-pthread/multithreading-pthread.h"
#endif

