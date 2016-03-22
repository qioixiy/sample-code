
# Makefile

CURPWD = $(PWD)

ROOTFS =
ifeq ($(TARGET), ARM)
	ROOTFS=/home/cndul/work/zxq/IVI/ZXQ/external/VisionSDK/vision_sdk/linux/targetfs
	CROSS_COMPILE=arm-linux-gnueabihf-
endif

# compiler
CC = $(CROSS_COMPILE)gcc

# include
INC += -I$(ROOTFS)/usr/include -I$(CURPWD)

# lib
LIB = -L$(ROOTFS)/usr/lib -L$(ROOTFS)/lib -L.
LIBS = -lpthread -lGLESv2 -lEGL -lwayland-client
LIBS-ARM = -lffi -ldrm -lpvr_wlegl -lIMGegl -lsrv_um -lpvr2d\
	-ldrm_omap -lm -lwayland-server -lgbm -ludev -lglib-2.0\
	-ldw -lelf -lz -lbz2 -lcap
LIBS-x86 = -lwayland-egl -lglapi

LIBS += $(LIBS-$(TARGET))

# src
SRCS := main.c egl/egl.c wayland/wayland.c gles/shader.c utils/file.c

all:
	TARGET=ARM make target
	TARGET=x86 make target

target:
	$(CC) $(INC) $(SRCS) $(LIB) $(LIBS) -o test-$(TARGET)

clean:
	-rm test-*
