# Makefile
CURPWD = $(PWD)

OUT_DIR ?= out
SRC_DIR = $(CURPWD)
BUILD_DIR = $(CURPWD)/$(OUT_DIR)/$(TARGET)
#BUILD_DIR=.
export

TARGET ?= x86
V =
Q = @
ifeq ($(V), 1)
	Q =
endif

ROOTFS =
ifeq ($(TARGET), ARM)
	ROOTFS=/home/cndul/work/zxq/targetfs
	INC = -Dyunos
	CROSS_COMPILE=arm-linux-gnueabihf-
endif

# compiler
CC = $(CROSS_COMPILE)gcc -g
CXX = $(CROSS_COMPILE)g++ -g

# include
INC += -I$(ROOTFS)/usr/include -I$(CURPWD)
INC-cairo=$(ROOTFS)/usr/include/cairo
INC += -I$(INC-cairo)

CFLAGS = $(INC)
CXXFLAGS = -std=c++11

# lib
LIB = -L$(ROOTFS)/usr/lib -L$(ROOTFS)/lib -L.
LIBS = -lpthread -lm -lstdc++ -lGLESv2 -lEGL -lwayland-client
LIBS-ARM = -lffi -ldrm -lpvr_wlegl -lIMGegl -lsrv_um -lpvr2d\
	-ldrm_omap -lm -lwayland-server -lgbm -ludev -lglib-2.0\
	-ldw -lelf -lz -lbz2 -lcap
LIBS-x86 = -lwayland-egl -lglapi
LIBS-cairo = -lcairo -lpng -lpixman-1 -lfreetype -lfontconfig -lexpat
LIBS += $(LIBS-cairo) $(LIBS-$(TARGET))

# src
APP_C_SRCS := \
	test/render.c \
	test/show_image.c \
	test/cube.c \
	test/cube2.c \

APP_CXX_SRCS := \
	test/ui_test.cpp \
	test/cube3.cpp \
	test/layout_test.cpp \
	test/test_project1.cpp \

C_SRCS := \
	egl/egl.c \
	wayland/wayland.c \
	gles/gles.c \
	gles/shader.c \
	gles/texture.c \
	gles/draw.c \
	utils/file.c \
	cairo/cairo.c \
	utils/util.c \
	utils/Matrix.c \
	utils/png_load.c \
	utils/blender2opengles/cube.c \

CXX_SRCS := \
	utils/obj/loader.cpp \
	gui/Common.cpp \
	gui/Node.cpp \
	gui/Frame.cpp \
	gui/NativeWindow.cpp \
	gui/wayland/WaylandClient.cpp \
	gui/Widget.cpp \
	gui/WidgetImage.cpp \
	gui/Painter.cpp \
	gui/egl/egl.cpp \
	app/app.cpp \
	gles/glslProgramObject.cpp \

# objs
OBJS_C := $(subst .c,.o,$(C_SRCS))
OBJS_CXX := $(subst .cpp,.o,$(CXX_SRCS))
OBJS := $(OBJS_C) $(OBJS_CXX)
APP_C_OBJS := $(subst .c,.o,$(APP_C_SRCS))
APP_CXX_OBJS := $(subst .cpp,.o,$(APP_CXX_SRCS))
APPS := $(APP_C_OBJS) $(APP_CXX_OBJS)

all: apps
	@echo all ok

pre:
	@echo BUILD_DIR=$(BUILD_DIR)
	@[ -d $(BUILD_DIR) ] || mkdir $(BUILD_DIR) -p
	@[ -d $(BUILD_DIR)/bin ] || mkdir $(BUILD_DIR)/bin -p

objs: $(OBJS_C) $(OBJS_CXX)
	@echo objs ready

$(APP_C_OBJS) $(OBJS_C): %.o: %.c
	@echo CC $^
	@[ -d $(BUILD_DIR)/$(<D) ] || mkdir $(BUILD_DIR)/$(<D) -p
	$(Q)$(CC) -c $(CFLAGS) $< -o $(BUILD_DIR)/$@

$(APP_CXX_OBJS) $(OBJS_CXX): %.o: %.cpp
	@echo CXX $^
	@[ -d $(BUILD_DIR)/$(<D) ] || mkdir $(BUILD_DIR)/$(<D) -p
	$(Q)$(CXX) -c $(INC) $(CXXFLAGS) $< -o $(BUILD_DIR)/$@

apps: pre objs app_c app_cxx
	@echo build apps ok

app_c: $(APP_C_OBJS)
	$(Q)for a in $^; do \
		echo CLD `basename $$a .o` \
			&& cd $(BUILD_DIR) \
			&& $(CC) $$a $(OBJS) $(LIB) $(LIBS) -o $(BUILD_DIR)/bin/`basename $$a .o`; \
	done
app_cxx: $(APP_CXX_OBJS)
	$(Q)for a in $^; do \
		echo CXXLD `basename $$a .o` \
			&& cd $(BUILD_DIR) \
			&& $(CXX) $$a $(OBJS) $(LIB) $(LIBS) -o $(BUILD_DIR)/bin/`basename $$a .o`; \
done

.PHONY: clean all
clean:
	-@rm $(addprefix $(BUILD_DIR)/,$(OBJS) $(APPS)) -rf
