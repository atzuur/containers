CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c99
CFLAGS_DEBUG ?= -g3 -Og
CFLAGS_RELEASE ?= -O2 -march=native

SRC_FILES = queue.c queue.h test.c
BIN_FILES = testq* queue.o

all: $(SRC_FILES)
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -c queue.c -o queue.o
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) test.c queue.o -o testq
	./testq
	$(rm) testq*

debug: $(SRC_FILES)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -c queue.c -o queue.o
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) test.c queue.o -o testq
	./testq

clean:
	$(rm) $(BIN_FILES)
