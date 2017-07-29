#ifndef __RT00__
#define __RT00__

/* x32 syscall flag bit */
#define __X32_SYSCALL_BIT	0x40000000

# ifdef __x86_64__
#  include "x86_64/unistd.h"
# elif defined(__i386__)
#  include "x86_32/unistd.h"
# elif defined(__ILP32__)
#  include "x86_32/unistd_x32.h"
# else
#  error Unsupported platform.
# endif

extern char _end, _edata, _etext, __executable_start;

long syscall6( long n, long a0, long a1, long a2, long a3, long a4, long a5 );
long syscall5( long n, long a0, long a1, long a2, long a3, long a4 );
long syscall4( long n, long a0, long a1, long a2, long a3 );
long syscall3( long n, long a0, long a1, long a2 );
long syscall2( long n, long a0, long a1 );
long syscall1( long n, long a0 );
long syscall0( long n );

void _exit( int r ) __attribute__((noreturn));

#endif/*__RT00__*/
