ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m += hello1.o
obj-m += hello2.o
ccflags-y += -I$(src)/inc -g	# add debugging info
else
# normal makefile
KDIR ?= $(HOME)/repos/linux-stable
ROOTFS ?= $(HOME)/repos/busybox
 
all:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello1.ko hello1.ko.unstripped
	cp hello2.ko hello2.ko.unstripped
	$(CROSS_COMPILE)strip -g hello1.ko hello2.ko	# strip only debugging info
 
install: all
	cp hello1.ko hello2.ko $(ROOTFS)/_install/lib/modules/
	cd $(ROOTFS)/_install && find . | cpio -o -H newc | gzip > ../rootfs.cpio.gz
 
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
	rm -f *.ko.unstripped
 
%.s %.i: %.c
	$(MAKE) -C $(KDIR) M=$$PWD $@
endif
 
