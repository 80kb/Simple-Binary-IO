CC = g++
CFLAGS = -g -Wall

HDR_FILES = ./src/endian_lib.h
SRC_FILES = ./src/endian_reader.cpp ./src/endian_writer.cpp

test: ./tests/main.cpp $(HDR_FILES) $(SRC_FILES)
	$(CC) $(CFLAGS) ./tests/main.cpp $(HDR_FILES) $(SRC_FILES) -o ./out/$@

clean:
	rm -f ./out/*
