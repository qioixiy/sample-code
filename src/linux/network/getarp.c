#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <string.h>
#include <stdlib.h>
#include <linux/sockios.h>
/**
 * url: http://www.tuicool.com/articles/ZJjiuy
 * ./a.out eth0 192.168.1.1
   ARP高速缓存操作，包含IP地址和硬件地址的映射表
   操作ARP高速缓存的命令字 SIOCDARP,SIOCGARP,SIOCSARP分别是删除ARP高速缓存的一条记录，获得ARP高速缓存的一条记录和修改ARP高速缓存的一条记录

   struct arpreq
   {
   struct sockaddr arp_pa; //协议地址
   struct sockaddr arp_ha;//硬件地址
   int arp_flags;//标记
   struct sockaddr arp_netmask;//协议地址的子网掩码
   char arp_dev[16];//查询网络接口的名称
   }

**/
//根据IP地址查找硬件地址
int main(int argc,char*argv[])
{
    int s;
    int err;
    struct arpreq arpreq;
    struct sockaddr_in *addr=(struct sockaddr_in*)&arpreq.arp_pa; //IP地址
    s=socket(AF_INET,SOCK_DGRAM,0);
    if(s<0)
    {
        perror("socket error");
    }

    const char *s_arp_dev = argv[1]; /* "eth0" */
    addr->sin_family=AF_INET;
    addr->sin_addr.s_addr=inet_addr(argv[2]); //转换成二进制IP
    if(addr->sin_addr.s_addr==INADDR_NONE)
    {
        printf("IP地址格式错误\n");
    }
    strcpy(arpreq.arp_dev, s_arp_dev);
    err=ioctl(s,SIOCGARP,&arpreq);
    if(err==-1)
    {
        perror("arp");
        return -1;
    }

    unsigned char* hw=(unsigned char*)&arpreq.arp_ha.sa_data; //硬件地址
    printf("%s\n",argv[1]);
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n",hw[0],hw[1],hw[2],hw[3],hw[4],hw[5]);
    close(s);
    return 0;

}
