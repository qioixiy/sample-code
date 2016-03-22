
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int get_file_size(const char* filename)
{
    struct stat buf;
    stat(filename, &buf);
    return buf.st_size;
}

const char* get_file_data(const char* filename, int size)
{
    int fd = open(filename, O_RDONLY|O_NONBLOCK);
    char* data = malloc(size);

    int index = 0;
    for(;index < size;) {
        int ret = read(fd, data+index, size-index);

        if (ret < 0) {
            if (errno == EAGAIN) {
                continue;
            }
            printf("read error\n");
            return NULL;
        } else {
            index += ret;
        }
    }

    return data;
}
