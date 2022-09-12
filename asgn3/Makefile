CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -lm
PROGRAM = sorting
FILES = sorting.o heap.o quick.o insert.o shell.o stats.o

all: sorting

sorting: sorting.o insert.o shell.o stats.o heap.o quick.o
	$(CC) -lm -o $(PROGRAM) $(FILES)
insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c
shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c
heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c
quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build make
