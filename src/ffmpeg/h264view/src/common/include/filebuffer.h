#ifndef _FILEBUFFER_
#define _FILEBUFFER_

unsigned char *open_file_and_get_buffer(char *filename);
unsigned char *get_buffer();
void free_buffer();
unsigned char *find_bytestream_from_buffer(const unsigned char *buffer, int buffer_size, const unsigned char *bytes, int bytes_size);

#endif