#include<linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/wait.h>

int __init rm_init(void)
{
    /* sudo cat /proc/kallsyms | grep test_completion */
    complete((struct completion *)0xffffffffc0bcd000);
    return 0;
}
void __exit rm_exit(void)
{
}
module_init(rm_init);
module_exit(rm_exit);
MODULE_LICENSE("GPL");
