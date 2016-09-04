
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

int readline(int fd, void *pStr, ssize_t maxLen, const char* ss)
{
	ssize_t n, rc;
	char c, *ptr;

    if (ss) {
        printf("%s", ss);
        fflush(NULL);
    }
	ptr = (char*) pStr;
	for (n = 1; n < maxLen; n++)
	{
    again:
		if ((rc = read(fd, &c, 1)) == 1) {
			if (c == '\n')
				break;
			*ptr++ = c;
		} else if (rc == 0) {
			*ptr = 0;
			return(n - 1);
		} else {
			if (errno == EINTR) {
				goto again;
            }
            return(-1);
		}
	}

	*ptr = '\0';
	return n;
}

int main(int argc, char** argv)
{
    char buf[100];
    while(1){
        int size = readline(0, buf, sizeof(buf), ">>");
        printf("%s", buf);
    }
}
