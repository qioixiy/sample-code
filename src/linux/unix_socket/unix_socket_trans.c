
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <pthread.h>
#include <errno.h>

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

unsigned char char_to_hexnumber(char c)
{
    unsigned char ret = 0xff;
    if (c >= '0' && c <= '9') {
        ret = c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        ret = c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        ret = c - 'A' + 10;
    }
    return ret;
}

char* find_first_vaild_hexchar(char* s)
{
    char* ret = 0;

    while(*s != '\0') {
        if (*s == ' ') {
            s++;
            continue;
        }
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
            s+=2;
            continue;
        }
        break;
    }
    if (*s == '\0') {
        ret = 0;
    } else {
        ret = s;
    }
    return ret;
}

/* 55-> 5+5*16, aa-> 10+10*16 */
int hex_to_byte(char *s)
{
    int ret;
    unsigned char s0 = char_to_hexnumber(s[0]);
    unsigned char s1 = char_to_hexnumber(s[1]);

    int i = s0 * 16 + s1;
    if (i > 0xff) {
        printf("invalid hex number\n");
        ret = -1;
    } else {
        ret = i;
    }
    
    return ret;
}

int hexstr_tobyte(char *buf, unsigned char *bytes)
{
    int index = 0;

    while(1) {
        buf = find_first_vaild_hexchar(buf);
        
        if (!buf) {
            break;
        }
        int i = hex_to_byte(buf);
        if (i == -1) {
            break;
        }
        bytes[index] = i;
        buf+=2;

        index++;
    }
    
    return index;
}

void print_hexstr(unsigned char* hexstr, int size)
{
    int first_flag = 1;
    while(size--) {
        if (first_flag == 1) {
            first_flag = 0;
        } else {
            printf(" ");
        }
        printf("0x%x", *hexstr++);
    }
}

void* write_pthread(void* p)
{
    int fd = *(int*)&p;
    printf("write pthread start %d\n", fd);

    char buf[100];
    unsigned char bytes[50];
    while(1) {
        readline(0, buf, sizeof buf, ">>");

        unsigned char ret = hexstr_tobyte(buf, bytes);
        printf("buf:%s[%d]", buf, ret);
        print_hexstr(bytes, ret);
        printf("\n");
        write(fd, bytes, ret);
        fflush(NULL);
    }

    printf("write pthread end\n");
}

int main(int argc, char **argv)
{  
    /* create a socket */  
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);  
        
    struct sockaddr_un address;  
    address.sun_family = AF_UNIX;  
    strcpy(address.sun_path, "serial");  
        
    /* connect to the server */  
    int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));  
    if(result == -1)  
    {  
        perror("connect failed: ");  
        exit(1);  
    }  
    pthread_t pit;
    pthread_create(&pit, 0, write_pthread, sockfd);
    unsigned char ch;
    while(1) {
        read(sockfd, &ch, 1);
        printf("0x%x ", ch);
        fflush(NULL);
    }
        
    /* close the socket */  
    close(sockfd);  
        
    return 0;  
}  
