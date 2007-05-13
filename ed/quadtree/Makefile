CC = gcc -g

LIBS = `pkg-config gtk+-2.0 --libs`
CFLAGS = `pkg-config gtk+-2.0 --cflags` -c

interface: main.o quadtree.o
	$(CC) main.o quadtree.o -o interface $(LIBS) 

main.o: main.c
	$(CC) main.c -o main.o $(CFLAGS)

quadtree.o: quadtree.h quadtree.c
	$(CC) quadtree.c -o quadtree.o $(CFLAGS)
		
clean:
	rm -rf *.o interface