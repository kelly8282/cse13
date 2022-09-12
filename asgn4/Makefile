SOURCES = tsp.c graph.c path.c stack.c
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
PROGRAM = tsp
FILES = tsp.o graph.o path.o stack.o

all: tsp

tsp: $(OBJECTS)
	$(CC) -o $@ $^ -g 
graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c
path.o: path.c
	$(CC) $(CFLAGS) -c path.c
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
vertices.o: vertices.c
	$(CC) $(CFLAGS) -c vertices.c

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build make

