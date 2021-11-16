#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>

// Some more stuff
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/serio.h>

#define DRIVER_DESC	"Half-Qwerty Keyboard Driver"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Josh Cole");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("0.0.2");

static irqreturn_t interrupt(struct serio *serio, unsigned char data, unsigned int flags) {
	printk(KERN_ALERT "Hi\n");
	return IRQ_HANDLED;
};

static int connect(struct serio *serio, struct serio_driver *drv) {
	printk(KERN_ALERT "Hi\n");
	return 0;
}

static void disconnect(struct serio *serio) {
	printk(KERN_ALERT "Hi\n");

}

static const struct serio_device_id serio_ids[] = {
	{
		.type = SERIO_XT,
		.proto = SERIO_ANY,
		.id = SERIO_ANY,
		.extra = SERIO_ANY,
	},
	{ 0 }
};

MODULE_DEVICE_TABLE(serio, serio_ids);

static struct serio_driver xtkbd_drv = {
	.driver = {
		.name = 	"halfqwerty-serio",
	},
	.description = DRIVER_DESC,
	.id_table = serio_ids,
	.interrupt = interrupt,
	.connect = connect,
	.disconnect = disconnect
};

module_serio_driver(xtkbd_drv);
