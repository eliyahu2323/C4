CC = gcc
FLAGS = -Wall -g

all: frequency

frequency: main.o frequency.o
	$(CC) $(FLAGS) -o frequency main.o frequency.o

main.o: main.c frequency.h
	$(CC) $(FLAGS) -c main.c 

frequency.o: frequency.c frequency.h
	$(CC) $(FLAGS) -c frequency.c 

.PHONY: clean all

clean:
	rm -f *.o frequency