# module.mk

MODULE_PATH:=$(call current_path)
#TODO
MODULE_NAME:=utils

#TODO
PRODUCT_SPECS:=
PLATFORM_SPECS:=
TARGET_SPECS:=

# don't use CXX CPPFLAGS... value, because will be covered by $(BUILD_CONFIGURE)
include $(BUILD_CONFIGURE)
CPPFLAGS+=-Isrc
SRC_FILES:=$(MODULE_PATH)/File.cpp $(MODULE_PATH)/Node.cpp \
	$(MODULE_PATH)/pngObj.cpp $(MODULE_PATH)/util.cpp \
	$(MODULE_PATH)/log/Log.cpp \
	$(MODULE_PATH)/file.c $(MODULE_PATH)/Matrix.c \

$(call build_target,$(BUILD_STATIC_LIBRARY),$(MODULE_PATH)/utils.a)
