#include <unistd.h>
#include <stdio.h>

int main() {
	printf("0x%X\n", sbrk(0));

	return 0;
}
