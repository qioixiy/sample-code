#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include<linux/sched.h>

static ssize_t ps_read(struct file *file, char __user *buf,
                       size_t count, loff_t *ppos)
{
    int len=0;
    struct task_struct *task_list;

    for_each_process(task_list) {
        len  += sprintf(buf+len, "\n %s %d \n",task_list->comm,task_list->pid);
    }

    return len;
}

static const struct file_operations ps_proc = {
    .read = ps_read,
};

int functn_init (void) {
    proc_create("ps_list", 0, NULL, &ps_proc);
    return 0;
}

void functn_cleanup(void) {
    remove_proc_entry("proc_entry",NULL);
}

MODULE_LICENSE("GPL");
module_init(functn_init);
module_exit(functn_cleanup);
