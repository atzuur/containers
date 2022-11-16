CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c99
CFLAGS_DEBUG ?= -g3 -Og
CFLAGS_RELEASE ?= -O2 -march=native

SRC_FILES = dict.c dict.h test.c
BIN_FILES = testdict* queue.o

all: $(SRC_FILES)
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -c dict.c -o dict.o
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) test.c dict.o -o testdict
	./testdict
	$(rm) testdict*

debug: $(SRC_FILES)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -c dict.c -o dict.o
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) test.c dict.o -o testdict
	./testdict debug # filling up argc to 2

clean:
	$(rm) $(BIN_FILES)
