// hello-4.c - Demonstrate module documentation

#include <linux/module.h>	// needed by all modules
#include <linux/kernel.h>	// needed for KERN_INFO
#include <linux/init.h>		// needed of the macro

#define DRIVER_AUTHOR 	"Guillaume Le Cam <lecam.guillaume@gmail.com>"
#define DRIVER_DESC	"A sample driver 5. Test Passing command line argument.;"

const static int hello_id = 5;

// parameters that can be passed
static short int my_short = 1;
static int my_int = 2;
static long int my_long = 3;
static char *my_string = "Pirouette";
static int my_int_array[2] = {-1,1};
static int arr_argc = 0;

/* module_param (param_name, type, permission_bits) */

module_param(my_short, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(my_short, "A short integer");
module_param(my_int, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(my_int, "An integer");
module_param(my_long, long, S_IRUSR);
MODULE_PARM_DESC(my_long, "A long integer");
module_param(my_string, charp, 0000);
MODULE_PARM_DESC(my_string, "A character string");

/* module_param_array(param_name, type, num, permission_bits)
 * num : pointer to the variable that will store the number of elements
 * of the array initialized by the user at module loading time
 */

module_param_array(my_int_array, int, &arr_argc, 0000);
MODULE_PARM_DESC(my_int_array, "An array of integer");


static int __init hello_5_init(void)
{
	int i=0;
	printk(KERN_INFO "Hello World %d.\n", hello_id);

	printk(KERN_INFO "my_short : %hd\n", my_short);
	printk(KERN_INFO "my_int : %d\n", my_int);
	printk(KERN_INFO "my_long : %ld\n", my_long);
	printk(KERN_INFO "my_string : %s\n", my_string);

	for(i=0; i<sizeof(my_int_array)/sizeof(my_int_array[0]); i++) {
		printk(KERN_INFO "my_int_array[%d] : %d\n",i ,my_int_array[i]);
	}
	return 0;
}

static void __exit hello_5_exit(void)
{
	printk(KERN_INFO "Goodbye World %d.\n", hello_id);
}

module_init(hello_5_init);
module_exit(hello_5_exit);

MODULE_LICENSE("GPL");	// get rid of the the taint message
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");






