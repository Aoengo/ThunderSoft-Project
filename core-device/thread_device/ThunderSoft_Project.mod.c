#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

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
	{ 0xd9726f80, "module_layout" },
	{ 0x1bcee483, "cdev_del" },
	{ 0x4240b5cb, "cdev_init" },
	{ 0xf9a482f9, "msleep" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x40794748, "kthread_create_on_node" },
	{ 0x15ba50a6, "jiffies" },
	{ 0xc5850110, "printk" },
	{ 0x514011c4, "kthread_stop" },
	{ 0x6626afca, "down" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x24d273d1, "add_timer" },
	{ 0xd5f10699, "cdev_add" },
	{ 0x37874eb8, "wake_up_process" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xcf2a6966, "up" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "742BF7860D3891F6B3D024B");
