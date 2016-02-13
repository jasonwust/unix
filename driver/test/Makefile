	obj-m := test.o
	KERNELDIR ?= /usr/src/kernels/3.10.0-327.4.5.el7.x86_64
	PWD := $(shell pwd)
	SYMBOL_INC := $(obj)/../module_ipc
	EXTRA_CFLAGS += -I $(SYMBOL_INC)
	KBUILD_EXTRA_SYMBOLS := $(SYMBOL_INC)/Module.symvers
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.order *.symvers
.PHONY : clean modules modules_install
