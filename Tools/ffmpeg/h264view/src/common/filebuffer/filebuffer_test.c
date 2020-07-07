#include <stdio.h>
#include <stdlib.h>
#include "get_file_size.h"
#include "filebuffer.h"

int main() {
	printf("%s\n", open_file_and_get_buffer(__FILE__) != NULL ? get_buffer() : (unsigned char *)"error\n");
	
	unsigned char *buffer = "123456789";
	unsigned char *chars = "3456";
	
	if (find_bytestream_from_buffer(buffer, 10, chars, 3)){
		printf("find bytestream\n");
	} else {
		printf("can't find bytestream\n");
	}
	
	unsigned char buffer_bytes[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
	unsigned char bytes[] = {0x07, 0x08, 0x09};
	
	if (find_bytestream_from_buffer(buffer_bytes+6, sizeof(buffer_bytes), bytes, 2)){
		printf("find bytestream\n");
	} else {
		printf("can't find bytestream\n");
	}
	
	free_buffer();
	
	return 0;
}