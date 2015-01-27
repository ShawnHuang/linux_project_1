#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/fs.h>
#include <linux/mm.h>
//#include <asm-i386/page.h>
//#include <asm-i386/pgtable.h>

asmlinkage long sys_project(long pid) {
        struct vm_area_struct *vm;  /* loop counter to loop through all vm section */
        struct page *page;
        unsigned long vm_address;   /* the virtual address */
        unsigned long pfn;

        //printk(KERN_EMERG "By it.livekn.com");
        struct task_struct *task;
        task = pid_task(find_vpid(pid), PIDTYPE_PID);
        ;
        //task = find_task_by_pid(pid);
        printk(KERN_INFO "process name: %s\n",task->comm);
        printk(KERN_INFO "vm_start: %08lx\n",task->mm->mmap->vm_start);
        printk(KERN_INFO "vm_end: %08lx\n",task->mm->mmap->vm_end);
        printk(KERN_INFO "file name: %s\n",task->mm->mmap->vm_file->f_path.dentry->d_name.name);
// physical frame address
        for ( vm = task->mm->mmap; vm != NULL; vm = vm->vm_next){

            printk("from 0x%08lx~0x%08lx\n",vm->vm_start,vm->vm_end);
            printk("page frame of the interval : \n");
            for (vm_address = vm->vm_start;
                vm_address < vm->vm_end;
                vm_address += 0x1000)
            {
                page = follow_page(vm, vm_address, 0);
                if ( page == NULL) continue;
                pfn = page_to_pfn(page);
                printk("0x%lx ",pfn);
            }
            printk("\n");
        }
        return 1;
}
