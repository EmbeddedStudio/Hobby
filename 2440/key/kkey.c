#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

static struct class *keys_class;
//static struct class_device	*keys_class_devs;
static struct class_device	*keys_class_devs[4];

static int s3c24xx_keys_open(struct inode *inode, struct file *file)
{
	return 0;
}
static int s3c24xx_keys_read(struct file *filp, char __user *buff, 
                                         size_t count, loff_t *offp)
{
	return 0;
}


/* ����ṹ���ַ��豸��������ĺ���
 * ��Ӧ�ó�������豸�ļ�ʱ�����õ�open��read��write�Ⱥ�����
 * ���ջ��������ṹ��ָ���Ķ�Ӧ����
 */
static struct file_operations s3c24xx_keys_fops = {
    .owner  =   THIS_MODULE,    /* ����һ���꣬�������ģ��ʱ�Զ�������__this_module���� */
    .open   =   s3c24xx_keys_open,     
	.read	=	s3c24xx_keys_read,		   
};

int major;
static int  s3c24xx_keys_init(void)
{
   int i=0;  //ѭ������
	
	major=register_chrdev(0,"keys_drv",&s3c24xx_keys_fops);
	
	keys_class = class_create(THIS_MODULE, "keys");

	for (i = 1; i < 4; i++)
	{
		keys_class_devs[i] = class_device_create(keys_class, NULL, MKDEV(major, i), NULL, "key%d", i);
		if (unlikely(IS_ERR(keys_class_devs[i])))
			return PTR_ERR(keys_class_devs[i]);
	}

//	keys_class_devs = class_device_create(keys_class, NULL, MKDEV(major, 0), NULL, "keys");

//	printk(DEVICE_NAME " initialized\n");

	return 0;
}

static int  s3c24xx_keys_exit(void)
{
	int i;//ѭ������

	unregister_chrdev(major,"keys_drv" );
	
 	for (i = 0; i < 4; i++)
 	{
 		class_device_unregister(keys_class_devs[i]);
 	} 
	class_device_unregister(keys_class_devs);

	class_destroy(keys_class);


	return 0;
}

module_init(s3c24xx_keys_init);
module_exit(s3c24xx_keys_exit);

MODULE_LICENSE("GPL");







































