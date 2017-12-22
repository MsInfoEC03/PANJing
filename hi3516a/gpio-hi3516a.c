/*linux/arch/arm/mach-hi3516a/gpio.c
 *
 * Generic SA-1100 GPIO handling
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/gpio.h>

#include <mach/hardware.h>
#include <mach/irqs.h>
#include <linux/module.h>
//#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
//#include <linux/slab.h>
//#include <linux/uaccess.h>
//#include <linux/types.h>
#include <asm/io.h>


#define GPIO1_7 (0x200f0160)

#define GPIO00_BASE (0x20140000)
#define GPIO01_BASE (0x20150000)
#define GPIO02_BASE (0x20160000)
#define GPIO03_BASE (0x20170000)
#define GPIO04_BASE (0x20180000)
#define GPIO05_BASE (0x20190000)
#define GPIO06_BASE (0x201A0000)
#define GPIO07_BASE (0x201B0000)
#define GPIO08_BASE (0x201C0000)
#define GPIO09_BASE (0x201D0000)
#define GPIO10_BASE (0x201E0000)
#define GPIO11_BASE (0x201F0000)
#define GPIO12_BASE (0x20200000)
#define GPIO13_BASE (0x20210000)
#define GPIO14_BASE (0x20220000)
#define GPIO15_BASE (0x20260000)

/*unsigned int GPIO_REG[]=
{
    GPIO00_BASE,
    GPIO01_BASE,
    GPIO02_BASE,
    GPIO03_BASE,
    GPIO04_BASE,
    GPIO05_BASE,
    GPIO06_BASE,
    GPIO07_BASE,
    GPIO08_BASE,
    GPIO09_BASE,
    GPIO10_BASE,
    GPIO11_BASE,
    GPIO12_BASE,
    GPIO13_BASE,
    GPIO14_BASE,
    GPIO15_BASE,
};*/

/*unsigned int GPIO_DIR[]=
{
	GPIO00_BASE + 0x400,
	GPIO01_BASE + 0x400,
	GPIO02_BASE + 0x400,
	GPIO03_BASE + 0x400,
	GPIO04_BASE + 0x400,
	GPIO05_BASE + 0x400,
	GPIO06_BASE + 0x400,
	GPIO07_BASE + 0x400,
	GPIO08_BASE + 0x400,
	GPIO09_BASE + 0x400,
	GPIO10_BASE + 0x400,
	GPIO11_BASE + 0x400,
	GPIO12_BASE + 0x400,
	GPIO13_BASE + 0x400,
	GPIO14_BASE + 0x400,
	GPIO15_BASE + 0x400,
};*/
unsigned int GPIO_DIR[]=
{
	GPIO09_BASE + 0x400,
	GPIO09_BASE + 0x400,
	GPIO01_BASE + 0x400,
	
	
};

unsigned int GPIO_ADDR[]=
{
	//GPIO09_BASE + 0x4,	
	//GPIO09_BASE + 0x8,	
	GPIO09_BASE + 0x10,	// 0
	//GPIO09_BASE + 0x20,
	GPIO09_BASE + 0x40,	// 1
	GPIO01_BASE + 0x200,	// 2
	//GPIO09_BASE + 0x80,
	//GPIO09_BASE + 0x100,
	//GPIO09_BASE + 0x200,
	/*GPIO08_BASE + 0x400,
	GPIO09_BASE + 0x400,
	GPIO10_BASE + 0x400,
	GPIO11_BASE + 0x400,
	GPIO12_BASE + 0x400,
	GPIO13_BASE + 0x400,
	GPIO14_BASE + 0x400,
	GPIO15_BASE + 0x400,*/
};

unsigned char GPIO_BIT[]=
{
    (1 << 2),    /* 0 */
    (1 << 4),    /* 1 */
    (1 << 7),    /* 2 */
    //(1 << 3),    /* GPIO X_3 */
    //(1 << 4),    /* GPIO X_4 */
    //(1 << 5),    /* GPIO X_5 */
    //(1 << 6),    /* GPIO X_6 */
    //(1 << 7),    /* GPIO X_7 */
};

#define GPIO_BIT_REG(X, Y) (GPIO_REG[X] + ((GPIO_BIT[Y])<<2))

unsigned int *con;
unsigned int *data;
unsigned int *mask;



static int hi3516a_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	unsigned int  memaddr = 0;
	//unsigned int regvalue = 0;
	
	if(offset == 2)
	{
		memaddr = GPIO1_7;
		mask = ioremap(memaddr, 4);
		writel(1, mask);
		printk(KERN_INFO "fuyong config ok.\n");
	}
	memaddr = GPIO_ADDR[offset];
        data = ioremap(memaddr, 4);
	//printk(KERN_INFO "data = %p", data);
	//printk(KERN_INFO "get value ok.\n");
	return readl(data);
        //return 0;
}
static void hi3516a_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	unsigned int  memaddr = 0;
	//unsigned int regvalue = 0;
	
	if(offset == 2)
	{
		memaddr = GPIO1_7;
		mask = ioremap(memaddr, 4);
		writel(1, mask);
		printk(KERN_INFO "fuyong config ok.\n");
	}
	memaddr = GPIO_ADDR[offset];
	data = ioremap(memaddr, 4);
	printk(KERN_INFO "data = %p", data);
	if(value)
	{
		//data = ioremap(memaddr, 4);
		//printk(KERN_INFO "data = %p", data);
		printk(KERN_INFO "set value 1 ok.\n");
		//regvalue |= GPIO_BIT[2];
		writel(0xff, data);
	}
	else
	{
		//data = ioremap(memaddr, 4);
		printk(KERN_INFO "set value 0 ok.\n");
		//regvalue &= ~GPIO_BIT[2];
		writel(0x00, data);
	}
}

static int hi3516a_direction_input(struct gpio_chip *chip, unsigned offset)
{
	unsigned int  memaddr = 0;
	unsigned int regvalue = 0;
	
	if(offset == 2)
	{
		memaddr = GPIO1_7;
		mask = ioremap(memaddr, 4);
		writel(1, mask);
		printk(KERN_INFO "fuyong config ok.\n");
	}
	memaddr = GPIO_DIR[offset];
        con = ioremap(memaddr, 4);
	regvalue &= ~GPIO_BIT[offset];
	writel(regvalue, con);
	//printk(KERN_INFO "con = %p", con);
	//printk(KERN_INFO "set direction_input ok.\n");
	return 0;
}
static int hi3516a_direction_output(struct gpio_chip *chip, unsigned offset, int value)
{
	unsigned int  memaddr = 0;
	unsigned int regvalue = 0;
	
	if(offset == 2)
	{
		memaddr = GPIO1_7;
		mask = ioremap(memaddr, 4);
		writel(1, mask);
		printk(KERN_INFO "fuyong config ok.\n");
	}
	memaddr = GPIO_DIR[offset];
        con = ioremap(memaddr, 4);
	//printk(KERN_INFO "memaddr = %d", memaddr);
	printk(KERN_INFO "con = %p", con);
	regvalue |= GPIO_BIT[offset];
	writel(regvalue, con);
	printk(KERN_INFO "set direction_output ok.\n");
        return 0;
}

static int hi3516a_to_irq(struct gpio_chip *chip, unsigned offset)
{
	printk(KERN_INFO "hi3516a_to_irq!!!\n");
        return 0;
}

static struct gpio_chip hi3516a_gpio_chip = {
        .label                  = "gpio",
        .direction_input        = hi3516a_direction_input,
        .direction_output       = hi3516a_direction_output,
        .set                    = hi3516a_gpio_set,
        .get                    = hi3516a_gpio_get,
        .to_irq                 = hi3516a_to_irq,
        .base                   = 0,
        .ngpio                  = 16 + 1,
};

void __init hi3516a_init_gpio(void)
{
	printk(KERN_INFO "**********hi3516a_init_gpio ok.***********\n");
        gpiochip_add(&hi3516a_gpio_chip);
	
}
arch_initcall(hi3516a_init_gpio);

