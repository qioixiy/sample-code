# module.mk

MODULE_PATH:=$(call current_path)
#TODO
MODULE_NAME:=gui

#TODO
PRODUCT_SPECS:=
PLATFORM_SPECS:=
TARGET_SPECS:=

# don't use CXX CPPFLAGS... value, because will be covered by $(BUILD_CONFIGURE)
include $(BUILD_CONFIGURE)
CPPFLAGS+=-Isrc
CPPFLAGS+=$(shell pkg-config --cflags wayland-client)

SRC_FILES:=$(MODULE_PATH)/Compositor.cpp  $(MODULE_PATH)/Frame.cpp  $(MODULE_PATH)/NativeWindow.cpp  $(MODULE_PATH)/Painter.cpp  $(MODULE_PATH)/Widget.cpp  $(MODULE_PATH)/WidgetGL.cpp  $(MODULE_PATH)/WidgetImage.cpp

$(call build_target,$(BUILD_STATIC_LIBRARY),$(MODULE_PATH)/gui.a)
