CC = g++
CFLAGS = -g -Wall

test: test_read test_write

test_read:
	$(CC) $(CFLAGS) ./tests/test_read.cpp  ./src/endian_reader.hpp -o ./out/read

test_write:
	$(CC) $(CFLAGS) ./tests/test_write.cpp ./src/endian_writer.hpp -o ./out/write

clean:
	rm -f ./out/*
