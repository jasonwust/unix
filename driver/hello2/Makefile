ifeq ($(KERNELRELEASE),)
	KERNELDIR ?= /usr/src/kernels/3.10.0-327.4.5.el7.x86_64
	PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.order *.symvers
.PHONY : clean
else
	obj-m :=hello.o
endif
