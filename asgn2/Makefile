
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra 
LDFLAGS = -lm
FILES= mathlib-test.o , e.o , madhava.o, euler.o, bbp.o, viete.o , newton.o

all: mathlib-test

mathlib-test: mathlib-test.o e.o madhava.o euler.o bbp.o viete.o newton.o
	$(CC) $(LDFLAGS) -o mathlib-test mathlib-test.o e.o madhava.o euler.o bbp.o viete.o newton.o

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c

euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c

bbp.o: bbp.c
	$(CC) $(CFLAGS) -c bbp.c

viete.o: viete.c
	$(CC) $(CFLAGS) -c viete.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

clean: 
	rm -f mathlib-test *.o

format: 
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build make
