CC = g++
CFLAGS = -g -Wall
SOURCES = ./src/endian_reader.hpp
TESTS = ./tests/test1.cpp

testcompile:
	$(CC) $(CFLAGS) $(TESTS) $(SOURCES) -o ./out/test1

runtests:
	./out/test1

clean:
	rm -f ./out/*
