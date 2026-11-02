obj-m += hello.o

KDIR ?= $(HOME)/repos/linux-stable

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
