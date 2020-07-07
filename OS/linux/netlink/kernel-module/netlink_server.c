#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/time.h>
#include <linux/types.h>
#include <net/sock.h>
#include <net/netlink.h>

#define NETLINK_TEST 25
#define MAX_MSGSIZE 1024

static struct sock *netlink_sock = NULL;

static
void send_usermsg(char *message, int pid)
{
    struct sk_buff *skb;
    struct nlmsghdr *nlh;
    int len = strlen(message);
    int len_msg = NLMSG_SPACE(MAX_MSGSIZE);

    if(!message || !netlink_sock) {
        return ;
    }

    skb = alloc_skb(len_msg, GFP_KERNEL);
    if(!skb) {
        printk(KERN_ERR "netlink-server:alloc_skb error\n");
        return;
    }

    nlh = nlmsg_put(skb, 0, 0, 0, MAX_MSGSIZE, 0);
    NETLINK_CB(skb).portid = 0;
    NETLINK_CB(skb).dst_group = 0;
    memcpy(NLMSG_DATA(nlh), message, len+1);

    netlink_unicast(netlink_sock, skb, pid, MSG_DONTWAIT);
}

static void netlink_data_ready(struct sk_buff *__skb)
{
    struct sk_buff *skb;
    skb = skb_get (__skb);

    if(skb->len >= NLMSG_SPACE(0)) {
        struct nlmsghdr *nlh;
        struct completion cmpl;
        char str[100];
        int pid;

        init_completion(&cmpl);
        //wait_for_completion_timeout(&cmpl, 1 * HZ);

        nlh = nlmsg_hdr(skb);
        memcpy(str, NLMSG_DATA(nlh), sizeof(str));
        printk("msg: %s\n", str) ;
        pid = nlh->nlmsg_pid;
        send_usermsg(str, pid);

        kfree_skb(skb);
    }
}

// Initialize netlink
int netlink_init(void)
{
    struct netlink_kernel_cfg cfg = {
                                     .input  = netlink_data_ready,
    };

    netlink_sock = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);
    if(!netlink_sock){
        printk(KERN_ERR "netlink-server: create netlink socket error.\n");
        return 1;
    }
    printk("netlink-server: create netlink socket ok.\n");

    return 0;
}

static void netlink_exit(void)
{
    if(netlink_sock != NULL){
        netlink_kernel_release(netlink_sock);
    }
    printk("netlink-server: module exited\n");
}

module_init(netlink_init);
module_exit(netlink_exit);

MODULE_AUTHOR("");
MODULE_LICENSE("GPL");
