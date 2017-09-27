#include<linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/wait.h>

int (*try)(task_t * p, unsigned int state, int sync);
int __init rm_init(void){
    struct task_struct *tsk = find_task_by_pid(28792);
    try=0xc011a460;
    (*try)(tsk, TASK_INTERRUPTIBLE|TASK_UNINTERRUPTIBLE, 0);
    return 0;
}
void __exit rm_exit(void){
}
module_init(rm_init);
module_exit(rm_exit);
MODULE_LICENSE("GPL");
