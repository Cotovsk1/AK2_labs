// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Istartii A.O.");
MODULE_DESCRIPTION("Lab 5: hello1 module with exported print_hello and timing list");
MODULE_VERSION("1.0");

struct hello_event {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

static LIST_HEAD(hello_event_list);

int print_hello(void)
{
	struct hello_event *element;

	element = kmalloc(sizeof(*element), GFP_KERNEL);
	if (!element)
		return -ENOMEM;

	element->start_time = ktime_get();

	pr_info("Hello, world!\n");

	element->end_time = ktime_get();

	list_add_tail(&element->list, &hello_event_list);

	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1: module loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *element, *tmp;

	pr_info("hello1: module unloading, printing print durations:\n");

	list_for_each_entry_safe(element, tmp, &hello_event_list, list) {
		u64 duration_ns;

		duration_ns = ktime_to_ns(element->end_time - element->start_time);

		pr_info("hello1: print duration: %llu ns\n", duration_ns);

		list_del(&element->list);
		kfree(element);
	}

	pr_info("hello1: module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
