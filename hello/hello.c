#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");

static __init int hello_init(void)
{
	printk(KERN_INFO "hello_init() called\n");
	return 0;
}

static __exit void hello_exit(void)
{
	printk(KERN_INFO "hello_exit() called\n");
}

module_init(hello_init);
module_exit(hello_exit);

