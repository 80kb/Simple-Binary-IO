CC = g++
CFLAGS = -g -Wall
SOURCES = ./src/endian_reader.hpp

tests:
	$(CC) $(CFLAGS) ./test/main.cpp $(SOURCES) -o ./out/$@

run:
	./out/tests

clean:
	rm -f ./out/*
