MODULES_DIR ?= src
MODULES ?= $(shell ls $(MODULES_DIR))
CFLAGS += -Isrc
CXXFLAGS += -std=c++11

all: pre _all

pre:

test: utils core egl gles gui cairo-priv wayland

include scripts/Makefile

.PHONY: pre
