#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/t_params.h>
#include <linux/vmalloc.h>

asmlinkage long set_total_computation_time(int pid, unsigned int total_time1){
        struct task_struct *i;
        int found=0;
        struct list_head *children_tasks;
        s64 x=1000000000;
        s64 total_time=total_time1*x;
        printk("Panagiotis Paraschidis, 3164, set_total_computation_time\n");
        if(pid<-1){
                printk("invalid pid in set total computation time\n");
                return EINVAL;
        }
        if(pid==current->pid){
                printk("(set) total comp time is: %lld in pid=%d \n",total_time,pid );
                current->total_computation_time=total_time;
                current->remaining_time=total_time;
                current->infinite=0;
        }
        else{
                printk("i am looking for child with pid:%d\n",pid);
                printk("while my pid is: %d\n", current->pid);

                list_for_each(children_tasks, &current->children){
                        i=list_entry(children_tasks, struct task_struct, sibling);
                        if (i->pid==pid){
                                printk("I am in child process with pid=%d\n", pid);
                                printk("(set) total comp time is: %lld in pid=%d \n",total_time,pid );
                                i->total_computation_time=total_time;
                                i->remaining_time=total_time;
                                i->infinite=0;
                                found=1;
                        }
                }

                if(found==0){
                        printk("child process wasn't found\n");
                        return EINVAL;
                }
        }

        return ((long)0);

}
