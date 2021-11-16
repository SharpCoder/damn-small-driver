#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xf7e1912f, "module_layout" },
	{ 0xda34d5b3, "usb_deregister" },
	{ 0x5213071b, "usb_register_driver" },
	{ 0xab56e416, "input_register_device" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x340b2e78, "input_allocate_device" },
	{ 0xc84ed42, "kmem_cache_alloc_trace" },
	{ 0xc35ee9f4, "kmalloc_caches" },
	{ 0xcdc2303a, "usb_submit_urb" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "usbcore");

MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic03isc01ip01in*");

MODULE_INFO(srcversion, "14D42EF5A137F47AB8D175C");
