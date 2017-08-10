#include <linux/kernel.h>
#include <linux/module.h>

static void __exit cleanup(void){
	printk(KERN_INFO "Good bye world\n");
}

module_exit(cleanup);
