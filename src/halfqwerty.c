#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// Some more stuff
#include <linux/slab.h>
#include <linux/usb/input.h>
#include <linux/hid.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Josh Cole");
MODULE_DESCRIPTION("A damn small driver");
MODULE_VERSION("0.0.1");

struct usb_kbd {
	struct input_dev *dev;
	struct usb_device *usbdev;
	unsigned char old[8];
	struct urb *irq;
	char name[128];
	char phys[64];
	unsigned char *new;
	struct usb_ctrlrequest *cr;
	dma_addr_t new_dma;	
};


static void usb_kbd_irq(struct urb *urb) {
	printk(KERN_ALERT "Hi\n");
}

static int usb_kbd_event(struct input_dev *dev, unsigned int type, unsigned int code, int value) {
	printk(KERN_ALERT "Hi\n");
	return 0;
}

static int usb_kbd_open(struct input_dev *dev) {
	printk(KERN_ALERT "Hi\n");
	struct usb_kbd *kbd = input_get_drvdata(dev);
	kbd->irq->dev = kbd->usbdev;
	usb_submit_urb(kbd->irq, GFP_KERNEL);
	return 0;
}

static void usb_kbd_close(struct input_dev *dev) {
	printk(KERN_ALERT "Hi\n");
}


static int usb_kbd_probe(struct usb_interface *iface, const struct usb_device_id *id) {
	printk(KERN_ALERT "Probe initiated\n");
	
	struct usb_device *dev = interface_to_usbdev(iface);
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint;
	struct usb_kbd *kbd;
	struct input_dev *input_dev;
	int i, pipe, maxp;
	
	interface = iface->cur_altsetting;
	endpoint = &interface->endpoint[0].desc;
	pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress);
	maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe));
	kbd = kzalloc(sizeof(struct usb_kbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	
	kbd->usbdev = dev;
	kbd->dev = input_dev;
	
	usb_make_path(dev, kbd->phys, sizeof(kbd->phys));
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &iface->dev;
	input_set_drvdata(input_dev, kbd);
	
	// Some event handlers?
	input_dev->event = usb_kbd_event;
	input_dev->open = usb_kbd_open;
	input_dev->close = usb_kbd_close;
	
	usb_fill_int_urb(
		kbd->irq,
		dev,
		pipe,
		kbd->new,
		(maxp > 8 ? 8 : maxp),
		usb_kbd_irq,
		kbd,
		endpoint->bInterval	
	);
	
	// Some configuration?
	kbd->irq->transfer_dma = kbd->new_dma;
	kbd->irq->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
	kbd->cr->bRequestType = USB_TYPE_CLASS | USB_RECIP_INTERFACE;
	kbd->cr->bRequest = 0x09;
	kbd->cr->wValue = cpu_to_le16(0x200);
	kbd->cr->wIndex = cpu_to_le16(interface->desc.bInterfaceNumber);
	kbd->cr->wLength = cpu_to_le16(1);
	
	
	input_register_device(kbd->dev);
	usb_set_intfdata(iface, kbd);

	return 0;
}

static void usb_kbd_disconnect(struct usb_interface *intf) {
	printk(KERN_ALERT "We're freeeeee!\n");
}

static const struct usb_device_id usb_kbd_id_table[] = {
	{
		USB_INTERFACE_INFO(
			USB_INTERFACE_CLASS_HID,
			USB_INTERFACE_SUBCLASS_BOOT,
			USB_INTERFACE_PROTOCOL_KEYBOARD
		)
	},
	{ }
};

MODULE_DEVICE_TABLE(usb, usb_kbd_id_table);

static struct usb_driver usb_kbd_driver = {
	.name = 	"halfqwerty",
	.probe = 	usb_kbd_probe,
	.disconnect =	usb_kbd_disconnect,
	.id_table =	usb_kbd_id_table,
};

module_usb_driver(usb_kbd_driver);
