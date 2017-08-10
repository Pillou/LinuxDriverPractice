/**
 * Creates a read only char device that says how many times 
 * you have read from the dev file.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

//static int __init chardev_init(void);
//static void __exit chardev_cleanup(void);

static int device_open(struct inode * ind, struct file * fl);
static int device_release(struct inode * ind, struct file * fl);
static ssize_t device_read(struct file * fl, char * chr, size_t sz, loff_t * off);
static ssize_t device_write(struct file * fl, const char * chr, size_t sz, loff_t * off);

#define SUCCESS 	(0)
#define DEVICE_NAME 	"chardev"	/* device name as it appears in /proc/devices */
#define BUF_LEN		(80)		/* Max length of the message from the device */

#define DEVICE_OPEN	(1)
#define DEVICE_FREE	(0)

static int Major;			/* Major number assigned to our device driver */
static int Device_Open = DEVICE_FREE;	/* Is device open? Used to prvend multiple access */
static char msg[BUF_LEN];		/* The msg the device will give when asked */
static char *msg_Ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/* this function is called when the module is loaded */
static int __init chardev_init(void){
	Major = register_chrdev(0, DEVICE_NAME, &fops);

	if(Major < 0) {
		printk(KERN_ALERT "Registering %s failed with %d\n", DEVICE_NAME, Major);
	}

	printk(KERN_INFO "Major number %d.\n", Major);
	printk(KERN_INFO "To talk to the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Test other minor number. Try to cat and echo to the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done\n");

	return SUCCESS; 
}

/* This function is called when the module is removed */
static void __exit chardev_cleanup(void){
	/* unregister the device */
	unregister_chrdev(Major, DEVICE_NAME);
}


/*** Methods ***/

/* Called when a process tries to open the device file, like cat */
static int device_open(struct inode *inode, struct file *file){
	static int counter = 0;

	if(Device_Open == DEVICE_OPEN){
		return -EBUSY;
	}

	Device_Open = DEVICE_OPEN;
	sprintf(msg, "I already told you %d times Hello World!\n", counter++);
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

/* called when a process closes the device file */
static int device_release(struct inode * inode, struct file *file) {
	Device_Open = DEVICE_FREE;

	/* Decrement the usage count, or else once you opened the file,
	 * you will never get rid of the module
 	 */
	module_put(THIS_MODULE);

	return SUCCESS;
}

/* called when a process which already opened the dev file, attemps to
 * read from it.
 */
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset){
	/* number of bytes actually written to the buffer */
	int bytes_read = 0;

	while((length != 0) && (*msg_Ptr != '\0')){
		/* The buffer is in the user data segment, not he kernel segment
		 * so "*" assignment will not work. We have to use put_user which
		 * copies data from the kernel data segment to the user data segment.
		 */
		put_user(*(msg_Ptr++), buffer++);

		length--;
		bytes_read++;
	}
	/* most read reutrn the number of bytes put into the buffer */
	return bytes_read;
}


/* called when a process writes to the dev file: echo "hi" > /dev/hello */
static ssize_t device_write(struct file *flip, const char *buff, size_t len, loff_t * off){
	printk(KERN_ALERT "Sorry this operation is not supported.\n");
	return -EINVAL;
}


module_init(chardev_init);
module_exit(chardev_cleanup);
