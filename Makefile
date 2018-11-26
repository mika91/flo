CC=g++
CFLAGS=-Wall -O -I/usr/local/include/ -I/public/ig/glm/
LDFLAGS=-lglfw -lGLEW -lGL
DEPS=

all: project2018

project2018: projet2018.o 
	$(CC) -o $@ $^ $(LDFLAGS)

projet2018.o: projet2018.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o core

clean-all: clean
	rm -f project2018
