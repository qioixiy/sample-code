# module.mk

MODULE_PATH:=$(call current_path)
#TODO
MODULE_NAME:=wayland

#TODO
PRODUCT_SPECS:=
PLATFORM_SPECS:=
TARGET_SPECS:=

# don't use CXX CPPFLAGS... value, because will be covered by $(BUILD_CONFIGURE)
include $(BUILD_CONFIGURE)
CPPFLAGS+=-Isrc
CPPFLAGS+=$(shell pkg-config --cflags wayland-client)
SRC_FILES:=$(MODULE_PATH)/WaylandClient.cpp

$(call build_target,$(BUILD_STATIC_LIBRARY),$(MODULE_PATH)/wayland.a)
