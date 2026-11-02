// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Istartii A.O.");
MODULE_DESCRIPTION("Lab 4: Linux Kernel Module with Parameters and Lists");
MODULE_VERSION("1.0");

static uint count = 1;
module_param(count, uint, 0644);
MODULE_PARM_DESC(count, "Number of times to print 'Hello, world!' (uint)");

struct my_event {
	struct list_head list;
	ktime_t event_time;
};

static LIST_HEAD(event_list_head);

static int __init hello_init(void)
{
	struct my_event *element;
	int i;

	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("Hello_module: Warning! Parameter count is %u\n", count);
	} else if (count > 10) {
		pr_err("Hello_module: Error! Parameter count (%u) > 10 is invalid!\n",
		       count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		element = kmalloc(sizeof(*element), GFP_KERNEL);
		if (!element)
			return -ENOMEM;

		element->event_time = ktime_get();
		list_add_tail(&element->list, &event_list_head);

		pr_info("Hello, world!\n");
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct my_event *element, *tmp;

	list_for_each_entry_safe(element, tmp, &event_list_head, list) {
		pr_info("Event timestamp: %lld ns\n",
			ktime_to_ns(element->event_time));
		list_del(&element->list);
		kfree(element);
	}

	pr_info("Hello_module: Unloaded successfully\n");
}

module_init(hello_init);
module_exit(hello_exit);
