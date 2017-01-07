# module.mk

MODULE_PATH:=$(call current_path)
#TODO
MODULE_NAME:=main

#TODO
PRODUCT_SPECS:=
PLATFORM_SPECS:=
TARGET_SPECS:=

# don't use CXX CPPFLAGS... value, because will be covered by $(BUILD_CONFIGURE)
include $(BUILD_CONFIGURE)
CPPFLAGS+=-Isrc
SRC_FILES:=$(MODULE_PATH)/test_project1.cpp
LDLIBS += \
	src/gui/gui.a \
	src/wayland/wayland.a \
	src/gles/gles.a \
	src/egl/egl.a \
	src/core/core.a \
	src/utils/utils.a \
	-lGLESv2 \
	-lEGL \
	-lpthread \
	-lwayland-client \
	-lwayland-egl \
	-lglapi \
	-lpng \
	-lpthread

$(call build_target,$(BUILD_EXECUTABLE))
