// hello-3.c - Illustrating the __init, __initdata and __exit macros

#include <linux/module.h>	// needed by all modules
#include <linux/kernel.h>	// needed for KERN_INFO
#include <linux/init.h>		// needed of the macro

static int hello_3_data __initdata = 3;

static int __init hello_3_init(void)
{
	printk(KERN_INFO "Hello World %d.\n", hello_3_data);
	return 0;
}

static void __exit hello_3_exit(void)
{
	printk(KERN_INFO "Goodbye World 3.\n");
}

module_init(hello_3_init);
module_exit(hello_3_exit);





