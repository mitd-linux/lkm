# Loadable kernel module

ARCH ?= $(shell uname -r)
KDIR := /lib/modules/$(ARCH)/build

# module object files
obj-m := lkm.o
lkm-y := lkm_main.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
