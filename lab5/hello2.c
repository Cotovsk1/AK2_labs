// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Istartii A.O.");
MODULE_DESCRIPTION("Lab 5: hello2 module calling exported print_hello from hello1");
MODULE_VERSION("1.0");

static uint count = 1;
module_param(count, uint, 0644);
MODULE_PARM_DESC(count, "Number of times print_hello() should be called (uint)");

static int __init hello2_init(void)
{
	int ret;
	int i;

	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("hello2: warning, count parameter is %u\n", count);
	} else if (count > 10) {
		pr_err("hello2: error, count parameter is %u, maximum is 10\n", count);
		return -EINVAL;
	}

	for (i = 0; i < (int)count; i++) {
		ret = print_hello();
		if (ret) {
			pr_err("hello2: failed to call print_hello(), ret=%d\n", ret);
			return ret;
		}
	}

	pr_info("hello2: module loaded successfully, called print_hello %u times\n", count);

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2: module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
