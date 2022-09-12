EXEC = banhammer
SOURCES = $(wildcard *.c)
OBJECTS = bv.o bf.o parser.o ht.o node.o bst.o speck.o

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror
LDFLAGS = -lm

all: $(EXEC)

banhammer: banhammer.o bv.o bf.o parser.o ht.o node.o bst.o speck.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o banhammer banhammer.c bv.c bf.c parser.c ht.c node.c bst.c speck.c

%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(EXEC) *.o
format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build make
