#include <linux/kernel.h>
#include <linux/module.h>

static int __init initModule(void)
{
	printk(KERN_INFO "Hello world - test module spanning on multiple files\n");
	return 0;
}

module_init(initModule);
