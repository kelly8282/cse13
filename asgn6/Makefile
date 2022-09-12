EXEC = keygen decrypt encrypt

CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -O2 $(shell pkg-config --cflags gmp)
LDFLAGS = $(shell pkg-config --libs gmp)

all: $(EXEC)

keygen: keygen.o numtheory.o randstate.o rsa.o
	$(CC) $(LDFLAGS) -o keygen keygen.c numtheory.c randstate.c rsa.c
encrypt: encrypt.o numtheory.o randstate.o rsa.o
	$(CC) $(LDFLAGS) -o encrypt encrypt.c numtheory.c randstate.c rsa.c

decrypt: decrypt.o numtheory.o randstate.o rsa.o
	$(CC) $(LDFLAGS) -o decrypt decrypt.c numtheory.c randstate.c rsa.c


%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(EXEC) *.o
format:
	clang-format -i -style=file *.[ch]
