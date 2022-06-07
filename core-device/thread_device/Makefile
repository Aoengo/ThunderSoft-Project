TARGET		:= ThunderSoft_Project
ifneq ($(KERNELRELEASE),)
	obj-m:= $(TARGET).o
	$(TARGET)-objs += ./src/core_thread.o ./src/core_timer.o ./src/core_main.o 
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	@rm -rf *~ *.o *.ko *.mod.c *.mod .*.cmd modules.order Module.makers Module.symvers .tmp_versions

endif


