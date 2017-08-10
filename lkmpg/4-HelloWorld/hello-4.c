// hello-4.c - Demonstrate module documentation

#include <linux/module.h>	// needed by all modules
#include <linux/kernel.h>	// needed for KERN_INFO
#include <linux/init.h>		// needed of the macro

#define DRIVER_AUTHOR 	"Guillaume Le Cam <lecam.guillaume@gmail.com>"
#define DRIVER_DESC	"A sample driver 4."


static int __init hello_4_init(void)
{
	printk(KERN_INFO "Hello World 4.\n");
	return 0;
}

static void __exit hello_4_exit(void)
{
	printk(KERN_INFO "Goodbye World 4.\n");
}

module_init(hello_4_init);
module_exit(hello_4_exit);

MODULE_LICENSE("GPL");	// get rid of the the taint message
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");






