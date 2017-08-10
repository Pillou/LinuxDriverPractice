// hello-1.c - Simple kernel module

#include <linux/module.h>	// needed by all module
#include <linux/kernel.h>	// needed for KERN_INFO

int init_module(void)
{
	printk(KERN_INFO "Hello world 1.\n");

	return 1; // 0 mean success
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye work 1.\n");

}
