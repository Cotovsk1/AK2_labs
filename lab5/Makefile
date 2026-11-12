obj-m += hello1.o
obj-m += hello2.o

KDIR ?= $(HOME)/repos/linux-stable

ccflags-y += -I$(src)/inc

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
