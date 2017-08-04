# module.mk

MODULE_PATH:=$(call current_path)

#TODO
PRODUCT_SPECS:=
PLATFORM_SPECS:=
TARGET_SPECS:=

# don't use CXX CPPFLAGS... value, because will be covered by $(BUILD_CONFIGURE)
include $(BUILD_CONFIGURE)
CPPFLAGS+=-Isrc
CPPFLAGS+=$(shell pkg-config --cflags wayland-client)

LDLIBS += \
	src/gui/gui.a \
	src/gui2/gui2.a \
	src/wayland/wayland.a \
	src/gles/gles.a \
	src/egl/egl.a \
	src/core/core.a \
	src/utils/utils.a \
	-lcairo \
	-lpng \
	-lpthread \
	-lz \

ifeq "$(TARGET_PLATFORM)" "arm-linux"
LIBS += \
	-ldrm \
	-lpvr_wlegl \
	-lpvr2d \
	-lffi \
	-lEGL \
	-lIMGegl \
	-lwayland-server \
	-lwayland-client \
	-lwayland-cursor\
	-ldrm_omap \
	-lsrv_um \
	-lGLESv2 \
	-ludev \
	-lcairo \
	-lexpat \
	-lfreetype \
	-lfontconfig \
	-lpixman-1 \
	-lrt \
	-lm

MODULE_NAME:=GLESKHR_test
SRC_FILES:=$(MODULE_PATH)/GLESKHR_test.cpp
$(call build_target,$(BUILD_EXECUTABLE))

else
LIBS += \
	-lGLESv2 \
	-lEGL \
	-lwayland-client \
	-lwayland-egl \

endif

MODULE_NAME:=gui_test
SRC_FILES:=$(MODULE_PATH)/gui_test.cpp
$(call build_target,$(BUILD_EXECUTABLE))

MODULE_NAME:=gui2_test
SRC_FILES:=$(wildcard $(MODULE_PATH)/gui2_test.cpp)
$(call build_target,$(BUILD_EXECUTABLE))

MODULE_NAME:=GlProgram_test
SRC_FILES:=$(MODULE_PATH)/GlProgram_test.cpp
$(call build_target,$(BUILD_EXECUTABLE))

MODULE_NAME:=WidgetGL_test
SRC_FILES:=$(MODULE_PATH)/WidgetGL_test.cpp
$(call build_target,$(BUILD_EXECUTABLE))
