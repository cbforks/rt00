#include "rt00.h"

# ifdef __x86_64__
#  include "x86_64/rt00.c"
# elif defined(__i386__)
#  include "x86_32/rt00.c"
# elif defined(__ILP32__)
#  include "x86_32/rt00.c"
# else
#  error Unsupported platform.
# endif

void _exit( int r ) {
	syscall1( __NR_exit, r );
	*((unsigned*)1) = 0xdead; /* segfault */
	for(;;);
}
