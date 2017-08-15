/*
 *  procfs1.c -  create a "file" in /proc
 *
 * This file has been updated since some function have been deleted since 3.10
 */

#include <linux/module.h>	/* Specifically, a module */
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/proc_fs.h>	/* Necessary because we use the proc fs */
#include <asm/uaccess.h>	/* copy_to_user */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GLC");
MODULE_DESCRIPTION("Simple module to test proc read");

#define ENTRY_NAME	"HelloWorld"
#define PERMS		(0644)
#define PARENT		(NULL)
#define BUFFER_SIZE	(100)

static const char buffer[] = "Hello World!\n";

static struct file_operations fops;


static int proc_open(struct inode * inode, struct file * file) {
	printk( KERN_INFO "Proc called open");

	return 0;
}

static ssize_t proc_read(struct file * file, char __user *buf, size_t size, loff_t *offset) {
	/* copy_to_user( void* to, const void __user* from, unsigned long size)
	 * needed because user uses virtual memory
 	 * prevents crashing to inaccessible regions
	 * can handle architecture specific issues */
	int length = sizeof(buffer) / sizeof(buffer[0]);
	static int read = 1;

	if( read == 0 ){
		read = 1;
		return 0;
	}else{
		read = 0;
	}

	if(copy_to_user(buf, buffer, length) != 0){
		printk(KERN_INFO "ERROR! copy_to_user");
		return -ENOMEM;
	}
	printk( KERN_INFO "Proc called read");
	return length;
}

static int proc_release(struct inode * inode, struct file *file){
	printk( KERN_INFO "Proc called release");
	return 0;
}


static int __init proc_init_module(void)
{
	/* Create the file /proc/procfs_name */
	/* create_proc_entry has been remove in 3.10 */
	//Our_Proc_File = create_proc_entry(procfs_name, 0644, NULL);

	printk( KERN_INFO "/proc/%s create \n", ENTRY_NAME);
	fops.owner = THIS_MODULE;
	fops.open = proc_open;
	fops.read = proc_read;
	fops.release = proc_release;

	if(proc_create(ENTRY_NAME, PERMS, NULL, &fops) == NULL){
		printk(KERN_INFO "ERROR! proc_create\n");
		remove_proc_entry(ENTRY_NAME, NULL);
		return -ENOMEM;
	}
	return 0;	/* everything is ok */
}

static void __exit proc_cleanup_module(void)
{
	remove_proc_entry(ENTRY_NAME, NULL);
	printk(KERN_INFO "/proc/%s removed\n", ENTRY_NAME);
}

module_init(proc_init_module);
module_exit(proc_cleanup_module);


