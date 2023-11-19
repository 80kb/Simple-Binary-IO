CC = g++
CFLAGS = -g -Wall

test: ./tests/main.cpp ./src/endian_writer.hpp ./src/endian_reader.hpp
	$(CC) $(CFLAGS) $^ -o ./out/$@

clean:
	rm -f ./out/*
