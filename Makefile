ROOTFS=/home/cndul/work/zxq/IVI/ZXQ/external/VisionSDK/vision_sdk/linux/targetfs

CROSS_COMPILE:=arm-linux-gnueabihf-
CC=$(CROSS_COMPILE)gcc

INC=-I$(ROOTFS)/usr/include
LIB=-L$(ROOTFS)/usr/lib -L$(ROOTFS)/lib -L.
LIBS=-lffi -ldrm -lpvr_wlegl -lEGL -lIMGegl -lsrv_um -lpvr2d -ldrm_omap\
	-lGLESv2 -lm -lwayland-client -lwayland-server -lgbm -ludev\
	-lglib-2.0 -ldw -lelf -lz -lbz2 -lcap -lpthread
SRCS:=main.c egl/egl.c wayland/wayland.c gles/shader.c

all:
	$(CC) $(INC) -c $(SRCS)
	$(CC) $(LIB) *.o $(LIBS) -o test
	gcc $(SRCS) -o test-x86 -lwayland-egl -lwayland-client -lGLESv2 -lpthread -lEGL -lglapi

clean:
	-rm *.o test test-*
