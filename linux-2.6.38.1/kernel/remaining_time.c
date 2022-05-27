#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/t_params.h>
#include <linux/vmalloc.h>

asmlinkage long get_remaining_time(int pid, struct t_params *t_arguments){
        struct list_head *children_tasks;
        struct task_struct *i;


        int found=0;
        int cop;

        struct t_params *tp_temp=vmalloc(sizeof(struct t_params));

        printk("Panagiotis Paraschidis, 3164, get_remaining_time\n");
        if(t_arguments==NULL){
                printk("the arguments you gave are null\n");
                return EINVAL;
        }

        if(pid<-1){
                printk("invalid pid in get_remaining_time\n");
                return EINVAL;
        }
        else if(pid==current->pid){
                printk("i am in process with pid=%d\n", pid);
                tp_temp->remaining_time=current->remaining_time;
                printk("(get)time is %lld \n", tp_temp->remaining_time);
                access_ok(VERIFY_READ,t_arguments,sizeof(t_arguments));
                cop=copy_to_user(t_arguments,tp_temp,sizeof(tp_temp));
        }
        else{

                list_for_each(children_tasks, &current->children){
                        i=list_entry(children_tasks, struct task_struct, sibling);
                        if(i->pid==pid){
                                found=1;
                                printk("I am in child process with pid=%d\n",pid);
                                tp_temp->remaining_time=current->remaining_time;
                                printk("(get)time is %lld \n", tp_temp->remaining_time);
                                access_ok(VERIFY_READ,t_arguments,sizeof(t_arguments));
                                cop=copy_to_user(t_arguments,tp_temp,sizeof(tp_temp));
                        }
                }
                if(found==0){
                        printk("child process wasn't found\n");
                        return EINVAL;
                }
        }
         return ((long)0);
}
