/* SPDX-License-Identifier: LGPL-2.1 WITH Linux-syscall-note */
#ifndef _LINUX_TASKINTROSPECTION_H
#define _LINUX_TASKINTROSPECTION_H

#include <linux/types.h>
/* Commands sent from userspace */
enum { TASKINTROSPECTION_C_INTROSPECT,
       __TASKINTROSPECTION_C_MAX,
};
#define TASKINTROSPECTION_C_MAX (__TASKINTROSPECTION_C_MAX - 1)

/* Return attributes for the introspect command */
enum { TASKINTROSPECTION_C_INTROSPECT_A_UNSPEC = 0,
       TASKINTROSPECTION_C_INTROSPECT_A_PID,
       __TASKINTROSPECTION_C_INTROSPECT_A_MAX,
};
#define TASKINTROSPECTION_C_INTROSPECT_A_MAX                                   \
	(__TASKINTROSPECTION_C_INTROSPECT_A_MAX - 1)

/* Potential return attributes */
enum { TASKINTROSPECTION_A_UNSPEC = 0,
       TASKINTROSPECTION_A_TGID,
       TASKINTROSPECTION_A_PID,
       TASKINTROSPECTION_A_COMM,
       __TASKINTROSPECTION_A_MAX,
};
#define TASKINTROSPECTION_A_MAX (__TASKINTROSPECTION_A_MAX - 1)

#define TASKINTROSPECTION_GENL_NAME "tasks"
#define TASKINTROSPECTION_GENL_VERSION 1

#endif
