MODULES_DIR ?= src
MODULES ?= $(shell ls $(MODULES_DIR))

all: pre _all
	@echo done

pre:
	@echo start

main: tools

include scripts/Makefile

.PHONY: pre
