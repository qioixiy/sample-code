# Top Makefile
# Copyright (C) 2016

ifeq ($(V),)
Q = @
endif
export Q

# export OUT dir
export OUT ?= build
export ARCH ?= x86
export PLATFORM ?= linux
export DEBUG ?= TRUE
ifeq ($(DEBUG), TRUE)
export BUILD_TYPE = debug
else
export BUILD_TYPE = release
endif

export BUILDDIR = $(ARCH)-$(PLATFORM)-$(BUILD_TYPE)
export OUTDIR=$(OUT)/$(BUILDDIR)

CC = gcc
export CC

MODULES_DIR = src
MODULES = $(shell ls $(MODULES_DIR))

all : $(OUTDIR) $(MODULES)
$(OUTDIR):
	@echo "Create directory $@"
	$(Q)mkdir -p $@

$(MODULES):
	@echo build module[$(MODULES_DIR)/$@]
	$(Q)$(MAKE) -f scripts/Makefile.build MODULE=$(MODULES_DIR)/$@ --no-print-directory

main: ipc tools

clean :
	$(Q)for subdir in $(MODULES); \
	do $(MAKE) -C $(MODULES_DIR)/$$subdir $@ MODULE=$$subdir --no-print-directory;\
	done

distclean: clean

cleanbuild:
	@echo clean $(OUT)
	$(Q)$(RM) -r $(OUT)

tags:
	ctags -R

cscope:
	cscope-indexer -r .

help:
	@echo "-----------------A common Makefile-----------------------"
	@echo "The following targets aresupport:"
	@echo " all              - (==make) compile and link"
	@echo " clean            - clean target"
	@echo " cleanbuild       - clean build dir"
	@echo " distclean        - clean target and otherinformation"
	@echo " tags             - create ctags for vimeditor"
	@echo " help             - print help information"
	@echo "To make a target, do 'make [target]'"

.PHONY : all clean distclean tags help

# make KEYS="USERNAME SHELL ARCH" debug
debug:
	$(foreach k,$(KEYS),$(warning $k=$($k)))
