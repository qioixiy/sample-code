#include <stdio.h>
#include "get_file_size.h"

int main() {

	char *filename = __FILE__;
	unsigned long filesize;
	
	filesize = get_file_size(filename);
	printf("%s size is %d\n", filename, filesize);
	
	return 0;
}