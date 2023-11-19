CC = g++
CFLAGS = -g -Wall
SOURCES = ./src/endian_reader.hpp

testcompile:
	$(CC) $(CFLAGS) ./tests/main.cpp $(SOURCES) -o ./out/test

clean:
	rm -f ./out/*
