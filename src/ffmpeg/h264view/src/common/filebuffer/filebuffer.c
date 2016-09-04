#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_file_size.h"
#include "filebuffer.h"

static unsigned char *buffer;

/*need free buffer*/
unsigned char *open_file_and_get_buffer(char *filename)
{
	FILE *fp = fopen(filename, "rb");
	
	if (fp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", filename);
	}
	
	unsigned long filesize = get_file_size(filename);
	buffer = malloc(filesize + sizeof(void*) + 1);//padding sizeof pointer+1 bytes
	*((unsigned long *)buffer) = filesize;//save buffersize
	buffer[filesize + sizeof(void*)] = 0;
	
	if (!buffer) {
		fprintf(stderr, "no memory space\n");
		return NULL;
	}
	unsigned long readsize = fread(buffer+sizeof(void*), 1, filesize, fp);
	if (readsize != filesize) {
		fprintf(stderr, "read file warrning\n\tfilesize=%d\n\treadsize=%d\n", 
				filesize, readsize);
		free(buffer);
		return NULL;
	}
	
	return buffer;
}

unsigned char *get_buffer() {
	return buffer;
}

void free_buffer() {
	if (buffer) {
		free(buffer);
	}
}

unsigned char *find_bytestream_from_buffer(const unsigned char *buffer, int buffer_size, const unsigned char *bytes, int bytes_size)
{
	const unsigned char *local_pointer = buffer;
	int i = 0;
	
	for (i = 0; i + bytes_size <= buffer_size; i++) {
		if (0 == memcmp(bytes, buffer+i, bytes_size) ) {
			return (void *)buffer+i;
		}
	}
	return NULL;
}
