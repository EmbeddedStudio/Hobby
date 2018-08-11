
/*
 * drives\mtd\nand\s3c2410.c
 * drives\mtd\nand\at91_nand.c
 */
#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/clk.h>
    
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/partitions.h>
    
#include <asm/io.h>
    
#include <asm/arch/regs-nand.h>
#include <asm/arch/nand.h>

static struct nand_chip nand;
static struct mtd_info * mtd;

static void s3c2440_select_chip()
{

}


static int  nand_init()
{
    /*1.分配一个nand_chip结构体*/
    nand = kzalloc(sizeof(struct nand_chip), GFP_KERNEL);
    
    /*2.设置*/
    nand ->select_chip = s3c2440_select_chip;
    
    /*3.硬件相关的操作*/
    /*4.使用： nand_scan*/
    mtd = kzalloc(sizeof(struct mtd), GFP_KERNEL);
    mtd->priv = nand;
    mtd->owner = THIS_MODULE;

    
    nand_scan(mtd,1);
    /*5.add_mtd_partitions*/
    
}

static void nand_exit()
{

}



module_init(nand_init);
module_exit(nand_exit);

MODULE_LICENSE("GPL");





























