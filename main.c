#include "rt00.h"

int main() {
	syscall3( __NR_write, 1, ( long )( "Hello World!\n" ), 13 );
	return 0;
}
