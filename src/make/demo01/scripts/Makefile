# Top Makefile
# Copyright (C) 2016

ifeq ($(V),)
Q = @
endif
export Q

# export OUT dir
OUT ?= build
ARCH ?= x86
PLATFORM ?= linux
DEBUG ?= TRUE
ifeq ($(DEBUG), TRUE)
BUILD_TYPE = debug
else
BUILD_TYPE = release
endif
BUILDDIR = $(ARCH)-$(PLATFORM)-$(BUILD_TYPE)
OUTDIR=$(OUT)/$(BUILDDIR)
export OUT ARCH PLATFORM DEBUG BUILD_TYPE BUILDDIR OUTDIR

CC = gcc
CXX = g++
export CC CXX CFLAGS CXXFLAGS

_all : $(OUTDIR) $(MODULES)
$(OUTDIR):
	@echo "Create directory $@"
	$(Q)mkdir -p $@

$(MODULES):
	@echo build module[$(MODULES_DIR)/$@]
	$(Q)$(MAKE) -f scripts/Makefile.build MODULE=$(MODULES_DIR)/$@ --no-print-directory

clean :
	-$(Q)for subdir in $(MODULES); \
	do $(MAKE) -C $(MODULES_DIR)/$$subdir $@ MODULE=$$subdir --no-print-directory;\
	done

cleanbuild:
	@echo clean $(OUT)
	$(Q)$(RM) -r $(OUT)

distclean: clean cleanbuild

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
	@echo " rebuild          - rebuild"
	@echo " distclean        - clean target and otherinformation"
	@echo " tags             - create ctags for vimeditor"
	@echo " help             - print help information"
	@echo "To make a target, do 'make [target]'"

.PHONY : all clean distclean tags help

# make KEYS="USERNAME SHELL ARCH" debug
debug:
	$(foreach k,$(KEYS),$(warning $k=$($k)))

rebuild:
	make cleanbuild
	make _all
