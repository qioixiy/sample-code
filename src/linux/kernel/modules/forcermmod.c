#include<linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/wait.h>

void force(void)
{
}
int __init rm_init(void)
{
    struct module *mod = (struct module*)0xf88de380;
    int i;
    int o=0;
    mod->state = MODULE_STATE_LIVE;
    mod->exit = force;
    for (i = 0; i < NR_CPUS; i++) {
        mod->ref[i].count = *(local_t *)&o;
    }
    return 0;
}
void __exit rm_exit(void)
{
}
module_init(rm_init);
module_exit(rm_exit);
MODULE_LICENSE("GPL");
