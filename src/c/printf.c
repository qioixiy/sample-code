// url: http://blog.csdn.net/liujia2100/article/details/8578640

typedef int * va_list;
#define va_start(ap, A)		(ap = (int *)&(A) + 1)
#define va_arg(ap, T)		(*(T *)ap++)
#define va_end(ap)		((void)0)

char itoa(unsigned long a, char * buf)
{
    unsigned long num = a;
    int i = 0;
    int len = 0;

    do
    {
        buf[i++] = num % 10 + '0';
        num /= 10;
    } while (num);
    buf[i] = '\0';

    len = i;
    for (i = 0; i < len/2; i++)
    {
        char tmp;
        tmp = buf[i];
        buf[i] = buf[len-i-1];
        buf[len-i-1] = tmp;
    }

    return len;
}

char itoa16(unsigned long a, char * buf)
{
    char index[]="0123456789ABCDEF";
    unsigned long num = a;
    int i = 0;
    int len = 0;
    for(i = 0; i < 8; i++)
    {
        buf[7-i] = index[num % 16];

        num /= 16;
    }
    buf[8] = '\0';
    len = 8;
    return len;
}

int sprintf(char *str, char * format, va_list ap)
{
    int i;
    char c;
    char *ptr = str;

    char ch;
    char * p;
    unsigned long a;

    while ((c = *format++) != '\0')
    {
        switch (c)
        {
            ch = 0;
            a  = 0;
        case '%':
            c = *format++;

            switch (c)
            {

                char buf[20]={'\0'};
            case 'c':
                ch = va_arg(ap, int);
                *ptr++ = ch;
                break;
            case 's':
                p = va_arg(ap, char *);
                for(; *p != '\0'; p++)
                    *ptr++ = *p;
                break;
            case 'x':
                a = va_arg(ap, int);
                itoa16(a,buf);
                p = buf;
                for(; *p != '\0'; p++)
                    *ptr++ = *p;
                break;
            case 'd':
                a = va_arg(ap, int);
                i = itoa(a,buf);
                p = buf;
                for(; *p != '\0'; p++)
                    *ptr++ = *p;
                break;

            default:
                break;
            }
            break;

        default:
            *ptr++ = c;
            break;
        }
    }
    *ptr = '\0';
    return 0;
}

void printf(const char *fmt,...)
{
    va_list ap;
    char string[100];
    va_start(ap, fmt);
    sprintf(string, fmt, ap);
    puts(string);
    va_end(ap);
}
