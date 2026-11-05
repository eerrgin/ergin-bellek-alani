CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O2 -Iinclude
.PHONY: all test clean
all: build/logbatch build/test_arena
build:
	mkdir -p build
build/logbatch: src/logbatch.c src/arena.c include/arena.h | build
	$(CC) $(CFLAGS) -o $@ src/logbatch.c src/arena.c
build/test_arena: tests/test_arena.c src/arena.c include/arena.h | build
	$(CC) $(CFLAGS) -o $@ tests/test_arena.c src/arena.c
test: build/test_arena build/logbatch
	./build/test_arena
	./build/logbatch
clean:
	rm -rf build
