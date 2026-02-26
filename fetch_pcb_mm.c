#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/fs.h>
#include <linux/mm_types.h>

static int __init fetch_pcb_mm_init(void) {
        struct task_struct *task;
        struct mm_struct *mm;
        struct file *file;
        loff_t pos = 0;
        char buf[128];
        int len;


        file = filp_open("/tmp/fetch_pcb_mm.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (IS_ERR(file)) {
            printk(KERN_ALERT "Cannot open file\n");
                return PTR_ERR(file);
        }

        for_each_process(task) {
                mm = task->mm;
                if (mm) {
                        len = snprintf(buf, sizeof(buf),
                            "Process: %s, PID: %d PGD: %p\n",
                            task->comm, task->pid, mm->pgd);
                } else {
                        len = snprintf(buf, sizeof(buf),
                            "Process: %s, PID: %d\n", task->comm, task->pid);
                }

                kernel_write(file, buf, len, &pos); 

        } 
        filp_close(file, NULL); 
        
        printk(KERN_INFO "Process list written to /tmp/fetch_pcb_mm.txt\n"); 
        return 0; 
} 

static void __exit fetch_pcb_mm_exit(void) { 
        printk(KERN_INFO "fetch_pcb_mm: Module unloaded\n"); 
} 

module_init(fetch_pcb_mm_init); 
module_exit(fetch_pcb_mm_exit);

MODULE_LICENSE("GPL");
