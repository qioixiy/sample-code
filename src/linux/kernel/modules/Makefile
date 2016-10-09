BASEDIR := /lib/modules/$(shell uname -r)
KERNEL_SRC_TREE ?= $(BASEDIR)/build
PWD :=$(shell pwd)
INSTALL_DIR ?= kernel/drivers/misc

.PHONY: all
all: clean modules

obj-m := killd.o forcermmod2.o forcermmod_test.o \
	processlist.o #processinfo.o

.PHONY:modules
modules:
	$(MAKE) -C $(KERNEL_SRC_TREE) SUBDIRS=$(PWD) modules

.PHONY:clean
clean:
	$(MAKE) -C $(KERNEL_SRC_TREE) SUBDIRS=$(PWD) clean

.PHONY:install
install:
	$(MAKE) -C $(KERNEL_SRC_TREE) SUBDIRS=$(PWD) INSTALL_MOD_DIR=$(INSTALL_DIR) modules_install
