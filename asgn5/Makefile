EXEC = encode decode
SOURCES = $(wildcard *.c)
OBJECTS = code.o huffman.o io.o node.o pq.o stack.o

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror
LDFLAGS = -lm

all: $(EXEC)

encode: encode.o node.o stack.o code.o pq.o io.o huffman.o
	$(CC) -o encode encode.c node.c stack.c code.c pq.c io.c huffman.c

decode: decode.o node.o stack.o code.o pq.o io.o huffman.o
	$(CC) -o decode decode.c node.c stack.c code.c pq.c io.c huffman.c


%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(EXEC) *.o
format:
	clang-format -i -style=file *.[ch]
