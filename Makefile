export CC = gcc
export CFLAGS = -Wall -Wextra -std=c99
export CFLAGS_DEBUG = -g3 -Og
export CFLAGS_RELEASE = -O2 -march=native

ifeq ($(OS), Windows_NT)
    detected_os := windows
else
    detected_os := $(shell uname)
endif

ifeq ($(detected_os), windows)
	rm = del
else
	rm = rm
endif

export rm

MODULES = queue
OBJ_FILES = queue/queue.o

all: build clean

debug: $(MODULES)
	$(foreach module, $(MODULES), +$(MAKE) -C $(module) debug)
	ar rcs libcontainers.a $(OBJ_FILES)

build: $(MODULES)
	$(foreach module, $(MODULES), +$(MAKE) -C $(module))
	ar rcs libcontainers.a $(OBJ_FILES)

clean: $(MODULES)
	$(foreach module, $(MODULES), +$(MAKE) -C $(module) clean)