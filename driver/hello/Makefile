obj-m := hello.o

KERNEL_SRC  := /usr/src/kernels/3.10.0-327.4.5.el7.x86_64
default:
	$(MAKE) -C $(KERNEL_SRC) M=`pwd` modules
.PHONY: clean

clean:
	rm -f *.o *.ko [mM]odule* *.mod.c
