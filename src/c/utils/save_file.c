#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void save_file(const char *file, const void *buf, size_t size)
{
    int fd = open(file, O_RDWR|O_CREAT|O_APPEND, 0666);
    if (fd) {
        int ret = write(fd, buf, size);
        if (ret != size) {
            printf("write size:%d\n", ret);
        }
        close(fd);
    }
}

#ifdef __TEST_MAIN
int main(int argc, char *argv[])
{
    int buf = ~0x0;
    save_file("file.txt", &buf, sizeof(buf));
    buf = 0x0;
    save_file("file.txt", &buf, sizeof(buf));

    return 0;
}
#endif
