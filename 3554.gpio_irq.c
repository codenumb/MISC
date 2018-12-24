/*
 * Sample driver for making GPIO to interrupt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.
 *
 * AUTHOR : Titusrathinaraj Stalin
 * EMAIL  : x0213399@ti.com
 *	
 */



/* Include linux kernel header files */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <asm/gpio.h>
#include <linux/interrupt.h>
#include <asm/irq.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Titus S");
MODULE_DESCRIPTION("GPIO interrupt sample driver");

#define GPIO_INT 55	/* GPIO No 55 */

/* local functions */
static int gpio_irq_open (struct inode *inode, struct file *filp);
static int gpio_irq_release (struct inode *inode, struct file *filp);
static int gpio_irq_fasync(int fd, struct file *filp, int on);

static struct fasync_struct *gpio_irq_async_queue;

/* declare file operation structure */
static struct file_operations gpio_irq_fops = {
	.owner = THIS_MODULE,
	.open  = gpio_irq_open,
	.release = gpio_irq_release,
	.fasync	= gpio_irq_fasync,
};

/*Interrupt Handler */
static irqreturn_t gpio_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	printk("\n GPIO interrupt raised; IRQ No : %d\n",irq);
	kill_fasync(&gpio_irq_async_queue, SIGIO, POLL_IN);
	return IRQ_HANDLED;
}

/***************************************************************************
 * Function             - gpio_request_irq
 * Functionality        - Registers Handlers to the IRQ's of GPIO's by request_irq
 * Input Params - 
 * Return Value - None
 * Note                 - None
 ****************************************************************************/
void gpio_request_irq(int irq_num)
{
	int status = 0;

	status = request_irq(irq_num, gpio_interrupt,IRQF_SHARED,"gpio_int", 102); //we can use IRQF_DIABLED

	printk(KERN_WARNING "gpio_request_irq %d status %d\n",
			   irq_num, status);

	if (status == -EINVAL) {
		printk("<1> EINVAL \n");
		} 
	else if (status == -ENOMEM) {
		printk("<1> ENOMEM ");
		} 		
		
	if (status < 0) {
		printk("<1> gpio_request_irq : Failed to Register IRQ %d  \n",
		       irq_num);
		printk("<1> gpio_request_irq : return status is %d  \n",
		       status);
	}

}

/***************************************************************************
 * Function             - gpio_unrequest_irq
 * Functionality        - Free Handlers o the IRQ's of GPIO's
 * Input Params - 
 * Return Value - None
 * Note                 - None
 ****************************************************************************/
void gpio_unrequest_irq(int irq_num)
{
	free_irq(irq_num, 102);
	printk("<1> gpio_unrequest_irq :  Freeing IRQ %d  \n", irq_num);

}
/****************************************************************************/


static int gpio_irq_fasync(int fd, struct file *filp, int on)
{
	int temp;
	temp = fasync_helper(fd, filp, on, &gpio_irq_async_queue);
	if (fd != -1)
		kill_fasync(&gpio_irq_async_queue, SIGIO, POLL_IN);
	return(temp);
}

void hhtp_gpio_init(void)
{
//	unsigned int *PINMUX3 = ioremap(0x01c40010,4); 
//	unsigned int control,tmp;
//	control = (*PINMUX3) | 0x00010000; //for GPIO18 (16th bit)
//	*PINMUX3 = control;

// TODO : Need to pinmux for GPIO55 here

	gpio_direction_input(GPIO_INT);
	tmp = gpio_to_irq(GPIO_INT);
	printk(KERN_ALERT "IRQ is %d\n",tmp);
	gpio_request_irq(tmp);
}

/******************************************************************************
 * gpio_irq_open - do nothing 
 *****************************************************************************/
static int gpio_irq_open (struct inode *inode, struct file *filp)
{
    return 0;
}    

/******************************************************************************
 * gpio_irq_release - do nothing 
 *****************************************************************************/
static int gpio_irq_release (struct inode *inode, struct file *filp)
{
	if (filp->f_flags & FASYNC) {
		gpio_irq_fasync (-1, filp, 0);
	}
	return 0;
} 

/*****************************************************************************
 * initialise user gpio module
 ****************************************************************************/
static int gpio_irq_init(void)
{
	unsigned int status,status1;

	status = register_chrdev(102, "gpio_int", &gpio_irq_fops);
	printk(KERN_ALERT "GPIO IRQ device is inserted sucessfully");
		  if (status < 0) {
		  printk(KERN_ALERT "Registering char device failed with %d\n", status);
		  return status;
}    
	status1 = gpio_request(GPIO_INT, "gpio_int");
	printk(KERN_ALERT "gpio request o/p is %d\n",status1);

	hhtp_gpio_init();
	return 0;
}

/*****************************************************************************
 * cleanup user gpio module
 ****************************************************************************/
static void gpio_irq_exit(void)
{
	unregister_chrdev(102, "gpio_int");
	gpio_unrequest_irq(gpio_to_irq(GPIO_INT));
	printk(KERN_ALERT "GPIO IRQ device is ejected sucessfully");
}

module_init(gpio_irq_init);
module_exit(gpio_irq_exit);
