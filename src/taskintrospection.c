// SPDX-License-Identifier: (GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause-No-Nuclear-Warranty
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <net/netlink.h>
#include <net/genetlink.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include "include/uapi/taskintrospection.h"

MODULE_DESCRIPTION("Task Introspection API");
MODULE_AUTHOR("Sargun Dhillon <sargun@sargun.me>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS_NET_PF_PROTO_NAME(PF_NETLINK, NETLINK_GENERIC,
			       TASKINTROSPECTION_GENL_NAME);

static struct genl_family genl_family;

static struct nla_policy taskintrospection_instrospect_policy[TASKINTROSPECTION_C_INTROSPECT_A_MAX + 1] = {
	[TASKINTROSPECTION_C_INTROSPECT_A_PID] = { .type = NLA_U32, },
};

static struct task_struct *get_task_by_pid(pid_t nr)
{
	struct task_struct *tsk = NULL;
	struct pid *pid;

	pid = find_get_pid(nr);
	if (!pid)
		return NULL;

	tsk = get_pid_task(pid, PIDTYPE_PID);
	put_pid(pid);

	return tsk;
}

static int taskintrospection_instrospect_fillinfo(struct task_struct *task,
						  struct genl_info *info,
						  struct sk_buff *skb)
{
	void *head;
	int err = -EMSGSIZE;

	head = genlmsg_put(skb, info->snd_portid, info->snd_seq, &genl_family,
			   0, TASKINTROSPECTION_C_INTROSPECT);
	if (!head)
		goto err;

	if (nla_put_u32(skb, TASKINTROSPECTION_A_PID, task->pid))
		goto err;
	if (nla_put_u32(skb, TASKINTROSPECTION_A_TGID, task->tgid))
		goto err;
	if (nla_put_string(skb, TASKINTROSPECTION_A_COMM, task->comm))
		goto err;

	genlmsg_end(skb, head);

	return 0;
err:
	genlmsg_cancel(skb, head);
	return err;
}

static int taskintrospection_instrospect_reply(struct task_struct *task,
					       struct genl_info *info)
{
	struct sk_buff *skb;
	int err;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	err = taskintrospection_instrospect_fillinfo(task, info, skb);
	if (err < 0) {
		nlmsg_free(skb);
		return err;
	}

	return genlmsg_reply(skb, info);
}

static int taskintrospection_instrospect(struct sk_buff *skb,
					 struct genl_info *info)
{
	/* message handling code goes here; return 0 on success, negative
	* values on failure */
	struct task_struct *task;
	struct nlattr *na;
	u64 pid;
	int err;

	na = info->attrs[TASKINTROSPECTION_C_INTROSPECT_A_PID];
	if (!na) {
		NL_SET_ERR_MSG_MOD(info->extack,
				   "Missing search criteria for task");
		return -EINVAL;
	}

	pid = nla_get_u32(info->attrs[TASKINTROSPECTION_C_INTROSPECT_A_PID]);
	task = get_task_by_pid(pid);
	if (!task) {
		NL_SET_ERR_MSG_MOD(info->extack, "Could not find task by PID");
		return -ESRCH;
	}

	err = taskintrospection_instrospect_reply(task, info);
	put_task_struct(task);

	return err;
}

static const struct genl_ops genl_ops[] = {
	{
		.cmd = TASKINTROSPECTION_C_INTROSPECT,
		.doit = taskintrospection_instrospect,
		.policy = taskintrospection_instrospect_policy,
		.maxattr = TASKINTROSPECTION_C_INTROSPECT_A_MAX,
	},
};

static struct genl_family genl_family = {
	.ops = genl_ops,
	.n_ops = ARRAY_SIZE(genl_ops),
	.name = TASKINTROSPECTION_GENL_NAME,
	.version = TASKINTROSPECTION_GENL_VERSION,
	.module = THIS_MODULE,
	.netnsok = true,
};

static int taskintrospection_init(void)
{
	return genl_register_family(&genl_family);
}

static void taskintrospection_exit(void)
{
	genl_unregister_family(&genl_family);
}

module_init(taskintrospection_init);
module_exit(taskintrospection_exit);
