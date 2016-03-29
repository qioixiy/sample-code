
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int file_is_exist(const char* filename)
{
    return 0 == access((filename), F_OK);
}

int get_file_size(const char* filename)
{
    if (!file_is_exist(filename)) {
        return -1;
    }
    struct stat buf;
    stat(filename, &buf);
    return buf.st_size;
}

char* get_file_data(const char* filename, int size)
{
    if (!file_is_exist(filename)) {
        printf("error: file %s is not exist\n", filename);
        return NULL;
    }
    int fd = open(filename, O_RDONLY|O_NONBLOCK);
    char* data = malloc(size);

    int index = 0;
    for(;index < size;) {
        int ret = read(fd, data+index, size-index);

        if (ret < 0) {
            if (errno == EAGAIN) {
                continue;
            }
            printf("error: read %s\n", filename);
            return NULL;
        } else {
            index += ret;
        }
    }

    return data;
}

char* get_string_from_file()
{
    ;
}
