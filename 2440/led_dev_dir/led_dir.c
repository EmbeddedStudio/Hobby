#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/serial_core.h>
#include <linux/sysdev.h>
#include <linux/clk.h>
#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>



/* ����/����/ע��һ�� platform_dirve */

static struct platform_driver led_dir={
	.probe  = led_probe;
	.remove = led_remove;
	.driver = {
	.name   = "myled",
		}

};


static int led_probe (&led_dir)
{
	/*����  ��Դ*/
	printk("led_probe,found");
    /*ע���ַ��豸����*/
}

static int led_remove (&led_dir)
{
	/*����  ��Դ*/
	printk("led_probe,remove");

    /*ж���ַ��豸����*/
}

static int led_dir_init(void)
{
	platform_driver_register(&led_dev);
	return 0;
}
static void led_dir_exit(void)
{
	platform_driver_unregister(&led_dev);
}

module_init(led_dir_init);
module_exit(led_dir_exit);
MODULE_LICENSE("GPL");


























