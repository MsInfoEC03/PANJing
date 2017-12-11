#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xf6628fc9, "module_layout" },
	{ 0x3ec8886f, "param_ops_int" },
	{ 0x6395be94, "__init_waitqueue_head" },
	{ 0x1b9ecedf, "__mutex_init" },
	{ 0x2b140f5e, "cdev_add" },
	{ 0x88dc55cf, "cdev_init" },
	{ 0x4a21112a, "kmem_cache_alloc_trace" },
	{ 0x53822150, "kmalloc_caches" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x37a0cba, "kfree" },
	{ 0xd6a968fe, "cdev_del" },
	{ 0x236c8c64, "memcpy" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0xb5dcab5b, "remove_wait_queue" },
	{ 0xcf21d241, "__wake_up" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x1000e51, "schedule" },
	{ 0x5860aad4, "add_wait_queue" },
	{ 0xffd5a395, "default_wake_function" },
	{ 0xf5d0b8cb, "current_task" },
	{ 0x59f300eb, "mutex_unlock" },
	{ 0x868e2bb, "mutex_lock" },
	{ 0xbc22005, "remap_pfn_range" },
	{ 0xe52947e7, "__phys_addr" },
	{ 0x27e1a049, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "B677870E179AEB2F76763B3");
