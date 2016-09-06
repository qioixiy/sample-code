SRC_BASE = ../..

CFLAGS += -g -Wall -Werror -O2
CPPFLAGS += -I. -I./inc -I../../include
LDFLAGS += -lpthread -L../../libs -lipc

LOCAL_SRC_FILES = $(wildcard src/*.c)
SRC_BIN = main

include $(SRC_BASE)/$(mk_rule)
