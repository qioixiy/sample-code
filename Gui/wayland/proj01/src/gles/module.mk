# module.mk

MODULE_PATH:=$(call current_path)
#TODO
MODULE_NAME:=gles

#TODO
PRODUCT_SPECS:=
PLATFORM_SPECS:=
TARGET_SPECS:=

# don't use CXX CPPFLAGS... value, because will be covered by $(BUILD_CONFIGURE)
include $(BUILD_CONFIGURE)
CPPFLAGS+=-Isrc
SRC_FILES:=$(MODULE_PATH)/GlEnv.cpp \
	$(MODULE_PATH)/GlProgramDescDefault.cpp \
	$(MODULE_PATH)/GlProgramDescDrawRect.cpp \
	$(MODULE_PATH)/GlProgramDescRgbaShow.cpp \
	$(MODULE_PATH)/GlProgramDescNV12Show.cpp \
	$(MODULE_PATH)/GlProgramDescObj.cpp \
	$(MODULE_PATH)/GlProgramDescObjLight.cpp \
	$(MODULE_PATH)/GlProgramObject.cpp \
	$(MODULE_PATH)/Shader.cpp \
	$(MODULE_PATH)/Texture.cpp \
	$(MODULE_PATH)/FBO.cpp \
        $(MODULE_PATH)/ObjLoader.cpp \

$(call build_target,$(BUILD_STATIC_LIBRARY),$(MODULE_PATH)/gles.a)