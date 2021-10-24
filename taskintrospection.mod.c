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

__visible struct module __this_module __section(".gnu.linkonce.this_module") = {
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

static const struct modversion_info ____versions[] __used
	__section("__versions") = {
		{ 0x7eadc417, "module_layout" },
		{ 0x1bf6e44f, "genl_unregister_family" },
		{ 0xad3d448, "genl_register_family" },
		{ 0xcbd4898c, "fortify_panic" },
		{ 0xd0da656b, "__stack_chk_fail" },
		{ 0x296695f, "refcount_warn_saturate" },
		{ 0xe6d2458e, "do_trace_netlink_extack" },
		{ 0x5b3aeacb, "__put_task_struct" },
		{ 0xdb982a1b, "netlink_unicast" },
		{ 0xa916b694, "strnlen" },
		{ 0xc6240ce9, "kfree_skb" },
		{ 0xfec3e700, "skb_trim" },
		{ 0x31e1522e, "nla_put" },
		{ 0x9b5b0d30, "genlmsg_put" },
		{ 0xd8ad87d5, "__alloc_skb" },
		{ 0xe20aea51, "put_pid" },
		{ 0xf253285a, "get_pid_task" },
		{ 0xd5deac85, "find_get_pid" },
		{ 0xbdfb6dbb, "__fentry__" },
	};

MODULE_INFO(depends, "");

MODULE_INFO(srcversion, "5C51481FD6953CD2CD84057");
