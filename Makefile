CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: tsp

tsp: tsp.o graph.o path.o stack.o
	$(CC) -o tsp $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.c *.h
