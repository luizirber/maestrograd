CC = g++

CFLAGS = -Wall -O2 `pkg-config xfcui-4.3 --cflags` `pkg-config sigc++-2.0 --cflags` `pkg-config xfccore-4.3 --cflags`

LIBS = `pkg-config xfcui-4.3 --libs` `pkg-config sigc++-2.0 --libs` `pkg-config xfccore-4.3 --libs` 

vetorial: vetorial.o main.o imagem.o poligono.o
	$(CC) vetorial.o main.o imagem.o ponto.o poligono.o -o vetorial $(LIBS)
	
vetorial.o: janela.hh janela.cc menu.ui
	$(CC) -c janela.cc -o vetorial.o $(CFLAGS)

main.o: main.cpp main.hh
	$(CC) -c main.cpp -o main.o $(CFLAGS)

imagem.o: imagem.cpp imagem.h
	$(CC) -c imagem.cpp -o imagem.o $(CFLAGS)

poligono.o: poligono.cpp
	$(CC) -c poligono.cpp -o poligono.o $(CFLAGS)

clean:
	rm -f *.o vetorial
