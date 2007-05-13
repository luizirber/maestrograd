CC = gcc -g

LIBS =
CFLAGS =

program: list.o main.o
	$(CC) main.o list.o -o program $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS) 

list.o: list.c list.h
	$(CC) -c list.c -o list.o $(CFLAGS)
		
clean:
	rm -rf *.o program
