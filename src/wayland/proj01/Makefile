# top makefile

## TARGET_PRODUCT TARGET_PLATFORM should be come from cmdline
## it's here, just for convenience
TARGET_PRODUCT :=
TARGET_PLATFORM :=

## strip writespace
TARGET_PRODUCT := $(strip $(TARGET_PRODUCT))
TARGET_PLATFORM:= $(strip $(TARGET_PLATFORM))
TARGET_BUILD_TYPE:= $(strip $(TARGET_BUILD_TYPE))

BUILD_SYSTEM_PATH := build
include $(BUILD_SYSTEM_PATH)/core/main.mk
