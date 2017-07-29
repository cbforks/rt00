#include "../rt00.h"

long syscall0( long n ) {
	long ret;
	__asm__ volatile( "int $0x80"
		: "=a" ( ret )
		: "a" ( n )
		: "memory" );
	return( ret );
}

long syscall1( long n, long a0 ) {
	long ret;
	__asm__ volatile( "int $0x80"
		: "=a" ( ret )
		: "a" ( n ), "b" ( a0 )
		: "memory" );
	return( ret );
}

long syscall2( long n, long a0, long a1 ) {
	long ret;
	__asm__ volatile( "int $0x80"
		: "=a" ( ret )
		: "a" ( n ), "b" ( a0 ), "c" ( a1 )
		: "memory" );
	return( ret );
}

long syscall3( long n, long a0, long a1, long a2 ) {
	long ret;
	__asm__ volatile( "int $0x80"
		: "=a" ( ret )
		: "a" ( n ), "b" ( a0 ), "c" ( a1 ), "d" ( a2 )
		: "memory" );
	return( ret );
}

long syscall4( long n, long a0, long a1, long a2, long a3 ) {
	long ret;
	__asm__ volatile( "int $0x80"
		: "=a" ( ret )
		: "a" ( n ), "b" ( a0 ), "c" ( a1 ), "d" ( a2 ), "S" ( a3 )
		: "memory" );
	return( ret );
}

long syscall5( long n, long a0, long a1, long a2, long a3, long a4 ) {
	long ret;
	__asm__ volatile( "int $0x80"
		: "=a" ( ret )
		: "a" ( n ), "b" ( a0 ), "c" ( a1 ), "d" ( a2 ), "S" ( a3 ), "D" ( a4 )
		: "memory" );
	return( ret );
}

long syscall6( long n, long a0, long a1, long a2, long a3, long a4, long a5 ) {
	long ret;
	register long ebp __asm__( "ebp" ) = a5;
	__asm__ volatile( "int $0x80"
		: "=a" ( ret )
		: "a" ( n ), "b" ( a0 ), "c" ( a1 ), "d" ( a2 ), "S" ( a3 ), "D" ( a4 ), "r" ( ebp )
		: "memory" );
	return( ret );
}

void _start( void ) __attribute__((noreturn));
void _start( void ) {
	register long eax __asm__( "eax" ) = 0;

	__asm__ volatile(
		/* Setup the base */
		"mov  %esp, %ebp\n\t"

		/* align the stack */
		"add  $0x1c,   %ebp\n\t"

		"mov  (0)(%ebp),  %ecx\n\t"
		"lea  (4)(%ebp),  %edx\n\t"
		"lea  (4)(%edx,%ecx,4), %eax\n\t"

		/* Fix GCC's 'helpful" 16-byte alignment */
		"and  $-16, %esp\n\t"

		/* push args onto re-aligned stack */
		"push %eax\n\t" /* envp = EAX = [ argv+8*argc+8 ] */
		"push %edx\n\t" /* argv = EDX = [ ESP+8 ] */
		"push %ecx\n\t" /* argc = ECX = [ ESP ] */

		"call main"
	);

	_exit( eax );
}
