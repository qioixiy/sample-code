/*
 * sudo cat /proc/kallsyms | grep __this_module | grep [module name]
 * url: http://www.aiuxian.com/article/p-1216640.html
 */

#include<linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/wait.h>

static DECLARE_COMPLETION(test_completion);
int init_module()
{
    return 0;
}
void cleanup_module( )
{
    wait_for_completion(&test_completion);
}
MODULE_LICENSE("GPL");
