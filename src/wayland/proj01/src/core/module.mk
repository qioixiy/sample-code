# module.mk

MODULE_PATH:=$(call current_path)
#TODO
MODULE_NAME:= core

#TODO
PRODUCT_SPECS:=
PLATFORM_SPECS:=
TARGET_SPECS:=

# don't use CXX CPPFLAGS... value, because will be covered by $(BUILD_CONFIGURE)
include $(BUILD_CONFIGURE)
CPPFLAGS+=-Isrc
SRC_FILES:=$(MODULE_PATH)/App.cpp

$(call build_target,$(BUILD_STATIC_LIBRARY),$(MODULE_PATH)/core.a)