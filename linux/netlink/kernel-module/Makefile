ifneq ($(KERNELRELEASE),)
	obj-m :=netlink_server.o
else
	KERNELDIR ?=/lib/modules/$(shell uname -r)/build
	PWD :=$(shell pwd)

default: client
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean: clean_client
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
endif

client:
	gcc client.c -o client

clean_client:
	-@rm client -f
