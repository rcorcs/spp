CC=g++
CFLAGS=-std=c++11 -lpthread #-lsupc++

all: main

main.o: main.cpp spp.h fork.h map.h reduce.h
	$(CC) -o main.o main.cpp -c $(CFLAGS)

main: main.o
	$(CC) -o main main.o $(CFLAGS)

clean:
	rm *.o main
