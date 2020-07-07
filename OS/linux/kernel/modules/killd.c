/*
 * insmod ./killd.ko pid=1234
 * url: http://blog.chinaunix.net/uid-20301055-id-2741526.html
 */

#include<linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/wait.h>

static int pid = -1;
module_param(pid, int, S_IRUGO);

static int killd_init(void)
{
    struct task_struct * p;
    printk(KERN_ALERT "killd: force D status process to death\n");
    printk(KERN_ALERT "killd: pid=%d\n", pid);

    //read_lock(&tasklist_lock);
    for_each_process(p){
        if(p->pid == pid){
            printk("killd: found\n");
            set_task_state(p, TASK_STOPPED);
            printk(KERN_ALERT "killd: aha, dead already\n");
            return 0;
        }
    }
    printk("not found");
    //read_unlock(&tasklist_lock);
    return 0;
}

static void killd_exit(void)
{
    printk(KERN_ALERT "killd: bye\n");
}

module_init(killd_init);
module_exit(killd_exit);

MODULE_LICENSE("GPL");
