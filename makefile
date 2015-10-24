CC=gcc
CFLAGS=-Wall
all: $(patsubst src/%.c, bin/%.out, $(wildcard src/*.c))
bin/%.out: src/%.c
	mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -r bin/*.out
