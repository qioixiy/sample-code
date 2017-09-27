#include<linux/module.h>
#include<linux/list.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kthread.h>
#include<linux/proc_fs.h>
#include<linux/sched.h>

static struct proc_dir_entry *tempdir, *processinfo_file;
static int proc_read_processinfo(char *page, char **start, off_t offset, int count, int*eof, void *data)
{
    //struct tast_struct *pos,*task;
    struct task_struct *pos;

    static char buf[1024*8]={0};
    char tmp[128]={0};

    /*static int num=0;
      printk("num = %d, offset = %d, count = %d/n",num,offset,count);
      num++;
    */
    //task=&init_task;

    if(offset>0)
    {
        return 0;
    }
    memset(buf,0,sizeof(buf));
    /*list_for_each_entry(pos,&task->tasks,tasks)
      {
      sprintf(tmp,"%d/t/t%s/n",pos->pid,pos->comm);
      strcat(buf,tmp);
      memset(tmp,0,sizeof(tmp));
      }*/
    for_each_process(pos)
    {
        sprintf(tmp,"%d/t/t%s/n",pos->pid,pos->comm);
        strcat(buf,tmp);
        memset(tmp,0,sizeof(tmp));
    }
    *start=buf;

    return strlen(buf);
}
static int init_processinfo_module(void)
{
    int rv=0;
    printk("processinfo module: hello kernel!/n");

    tempdir=proc_mkdir("mydir",NULL);
    if(tempdir==NULL)
    {
        rv=-ENOMEM;
        return rv;
    }
    processinfo_file=create_proc_read_entry("processinfo",0444,tempdir,proc_read_processinfo,NULL);
    if(processinfo_file==NULL)
    {
        rv=-ENOMEM;
        remove_proc_entry("mydir",NULL);
        return rv;
    }
    printk("processinfo module: init successfully!/n");
    return 0;
}
static void exit_processinfo_module(void)
{
    remove_proc_entry("processinfo",tempdir);
    remove_proc_entry("mydir",NULL);
    printk("processinfo module: by kernel!/n");
}
module_init(init_processinfo_module);
module_exit(exit_processinfo_module);
