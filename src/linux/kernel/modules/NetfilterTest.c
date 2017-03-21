#include <linux/module.h>
#include <linux/netfilter.h>

/**
 * refs url: http://blog.chinaunix.net/uid-7396260-id-2056629.html
 * test cmd
 * $ insmod Netfiltertest
 * $ ping -s 72 127.0.0.1
 */

static int drop_cnt = 0;
static struct nf_hook_ops hook_test;

static unsigned int drop_pkt100(void *priv,
                                struct sk_buff *skb,
                                const struct nf_hook_state *state)
{
    if (skb->len == 100) {
        drop_cnt++;
        printk("drop the %d packet!\n", drop_cnt);
        return NF_DROP;
    }
    return NF_ACCEPT;
}

static int netfilter_test_init(void)
{
    printk(KERN_ALERT "netfilter test init\n");

    hook_test.pf = PF_INET;
    hook_test.hooknum = NF_INET_LOCAL_IN;
    hook_test.hook = drop_pkt100;

    nf_register_hook(&hook_test);
    return 0;
}

static void netfilter_test_exit(void)
{
    nf_unregister_hook(&hook_test);
    printk(KERN_ALERT "netfilter test exit\n");
}

module_init(netfilter_test_init);
module_exit(netfilter_test_exit);

MODULE_LICENSE("GPL");
