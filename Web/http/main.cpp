#include "HttpRequest.h"

int main()
{
    HttpRequest* Http = new HttpRequest;

    char* str = (char*)malloc(BUFSIZE);

    memset(str, 0, BUFSIZE);
    if(Http->HttpGet("http://www.baidu.com", str)) {
        printf("%s\n", str);
    } else {
        printf("http://www.baidu.com HttpGet请求失败!\n");
    }

    memset(str, 0, BUFSIZE);
    //安装Tomcat
    if(Http->HttpGet("127.0.0.1", str)) {
        printf("%s\n", str);
    } else {
        printf("127.0.0.1 HttpGet请求失败!\n");
    }

    free(str);
    return 0;
}
