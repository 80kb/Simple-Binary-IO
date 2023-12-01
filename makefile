CC = g++
CFLAGS = -g -Wall

test: ./tests/main.cpp ./src/endian_lib.hpp
	$(CC) $(CFLAGS) $^ -o ./out/$@

clean:
	rm -f ./out/*
