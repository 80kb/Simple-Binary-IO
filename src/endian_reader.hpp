#ifndef __ENDIAN_READER_HPP__
#define __ENDIAN_READER_HPP__

#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1

class EndianReader
{
        char* _filename;
        byte _buffer[];
        int _position;
        int _endianness;

public:
        EndianReader(char* filename, int endianness) : _filename(filename), _endianness(endianness), _position(0) {}
        ~EndianReader();

private:
        FillBuffer(int count, int stride);
};

#endif
