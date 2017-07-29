#include "../rt00.h"

long syscall0( long n ) {
	long ret;
	__asm__ volatile("syscall"
		: "=a" ( ret )
		: "a" ( n )
		: "rcx", "r11", "memory" );
	return( ret );
}

long syscall1( long n, long a0 ) {
	long ret;
	__asm__ volatile( "syscall"
		: "=a" ( ret )
		: "a" ( n ), "D" ( a0 )
		: "rcx", "r11", "memory" );
	return( ret );
}

long syscall2( long n, long a0, long a1 ) {
	long ret;
	__asm__ volatile( "syscall"
		: "=a" ( ret )
		: "a" ( n ), "D" ( a0 ), "S" ( a1 )
		: "rcx", "r11", "memory" );
	return( ret );
}

long syscall3( long n, long a0, long a1, long a2 ) {
	long ret;
	__asm__ volatile( "syscall"
		: "=a" ( ret )
		: "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 )
		: "rcx", "r11", "memory" );
	return( ret );
}

long syscall4( long n, long a0, long a1, long a2, long a3 ) {
	long ret;
	register long r10 __asm__( "r10" ) = a3;
	__asm__ volatile( "syscall"
		: "=a" ( ret )
		: "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 ), "r" ( r10 )
		: "rcx", "r11", "memory" );
	return( ret );
}

long syscall5( long n, long a0, long a1, long a2, long a3, long a4 ) {
	long ret;
	register long r10 __asm__( "r10" ) = a3, r08 __asm__( "r8" ) = a4;
	__asm__ volatile( "syscall"
		: "=a" ( ret )
		: "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 ), "r" ( r08 ), "r" ( r10 )
		: "rcx", "r11", "memory" );
	return( ret );
}

long syscall6( long n, long a0, long a1, long a2, long a3, long a4, long a5 ) {
	long ret;
	register long r10 __asm__( "r10" ) = a3, r08 __asm__( "r8" ) = a4, r09 __asm__( "r9" ) = a5;
	__asm__ volatile( "syscall"
		: "=a" ( ret )
		: "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 ), "r" ( r08 ), "r" ( r09 ), "r" ( r10 )
		: "rcx", "r11", "memory" );
	return( ret );
}

void start( void ) __attribute__((noreturn));
void start( void ) {
	register long rax __asm__( "rax" ) = 0;

	__asm__ volatile( 
		/* Setup the base */
		"pop  %rbp\n\t"
		"mov  %rsp, %rbp\n\t"

		"mov  (0)(%rbp),  %rdi\n\t" /* argc = RDI = [ RSP ] */
		"lea  (8)(%rbp),  %rsi\n\t" /* argv = RSI = [ RSP+8 ] */
		"lea  (8)(%rsi,%rdi,8), %rdx\n\t" /* envp = RDX = [ argv+8*argc+8 ] */

		/* align the stack */
		"and  $-16, %rsp\n\t"

		"call main"
	);

	_exit( rax );
}
