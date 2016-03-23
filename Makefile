
# Makefile
CURPWD = $(PWD)

OUT_DIR ?= out
BUILD_DIR = $(CURPWD)/$(OUT_DIR)/$(TARGET)

ROOTFS =
ifeq ($(TARGET), ARM)
	ROOTFS=/home/cndul/work/zxq/IVI/ZXQ/external/VisionSDK/vision_sdk/linux/targetfs
	CROSS_COMPILE=arm-linux-gnueabihf-
endif

# compiler
CC = $(CROSS_COMPILE)gcc

# include
INC = -I$(ROOTFS)/usr/include -I$(CURPWD)
INC-cairo=$(ROOTFS)/usr/include/cairo
INC += -I$(INC-cairo)

# lib
LIB = -L$(ROOTFS)/usr/lib -L$(ROOTFS)/lib -L.
LIBS = -lpthread -lGLESv2 -lEGL -lwayland-client
LIBS-ARM = -lffi -ldrm -lpvr_wlegl -lIMGegl -lsrv_um -lpvr2d\
	-ldrm_omap -lm -lwayland-server -lgbm -ludev -lglib-2.0\
	-ldw -lelf -lz -lbz2 -lcap
LIBS-x86 = -lwayland-egl -lglapi
LIBS-cairo = -lcairo -lpng -lpixman-1 -lfreetype -lfontconfig -lexpat
LIBS += $(LIBS-cairo) $(LIBS-$(TARGET))

# src
SRCS := main.c \
	egl/egl.c \
	wayland/wayland.c \
	gles/shader.c \
	gles/texture.c \
	utils/file.c \
	cairo/cairo.c

# objs
OBJS := $(subst .c,.o,$(SRCS))

all:
	TARGET=ARM make target
	TARGET=x86 make target

pre:
	@echo BUILD_DIR=$(BUILD_DIR)
	@[ -d $(BUILD_DIR) ] || mkdir $(BUILD_DIR) -p

# egl/%.o: egl/%.c
# 	$(CC) -c $(INC) $< -o $(BUILD_DIR)/$@

%.o: %.c
	@echo "%.o: %.c" $^
	@[ -d $(BUILD_DIR)/$(<D) ] || mkdir $(BUILD_DIR)/$(<D) -p
	$(CC) -c $(INC) $< -o $(BUILD_DIR)/$@

target: pre $(OBJS)
	@echo OBJS=$(OBJS)
	cd $(BUILD_DIR) && $(CC) $(OBJS) $(LIB) $(LIBS) -o $(BUILD_DIR)/test

.PHONY: clean
clean:
	-@rm $(BUILD_DIR) -rf
