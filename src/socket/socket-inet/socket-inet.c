#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

/* 从服务器套接字中读取主页内容。返回成功的标记。*/

void get_home_page (int socket_fd)
{
	char buffer[10000];
	ssize_t number_characters_read;
	/* 发送 HTTP GET 请求获取主页内容。*/
	sprintf (buffer, "GET /\n");
	write (socket_fd, buffer, strlen (buffer));
	/* 从套接字中读取信息。调用 read 一次可能不会返回全部信息，所以我们必须不
	   断尝试读取直到真正结束。*/

	while (1) {
		number_characters_read = read (socket_fd, buffer, 10000);

		if (number_characters_read == 0)
			return;
		/* 将数据输出到标准输出流。*/
		fwrite (buffer, sizeof (char), number_characters_read, stdout);
	}
}

int main (int argc, char* const argv[])
{
	int socket_fd;
	struct sockaddr_in name;
	struct hostent* hostinfo;

	/* 创建套接字。*/
	socket_fd = socket (PF_INET, SOCK_STREAM, 0);
	/* 将服务器地址保存在套接字地址中。*/
	name.sin_family = AF_INET;
	/* 将包含主机名的字符串转换为数字。*/
	hostinfo = gethostbyname (argv[1]);
	if (hostinfo == NULL)
		return 1;
	else
		name.sin_addr = *((struct in_addr *) hostinfo->h_addr);
	/* 网页服务器使用 80 端口。*/
	name.sin_port = htons (80);

	/* 连接到网页服务器。*/
	if (connect (socket_fd, (struct sockaddr *)&name, sizeof (struct sockaddr_in)) == -1)
    {
		perror ("connect");
		return 1;
    }
	/* 读取主页内容。*/
	get_home_page (socket_fd);

	return 0;
} 
