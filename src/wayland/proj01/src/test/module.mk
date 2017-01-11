# module.mk

MODULE_PATH:=$(call current_path)

#TODO
PRODUCT_SPECS:=
PLATFORM_SPECS:=
TARGET_SPECS:=

# don't use CXX CPPFLAGS... value, because will be covered by $(BUILD_CONFIGURE)
include $(BUILD_CONFIGURE)
CPPFLAGS+=-Isrc
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

MODULE_NAME:=gui_test
SRC_FILES:=$(MODULE_PATH)/gui_test.cpp
$(call build_target,$(BUILD_EXECUTABLE))

MODULE_NAME:=GlProgram_test
SRC_FILES:=$(MODULE_PATH)/GlProgram_test.cpp
$(call build_target,$(BUILD_EXECUTABLE))
