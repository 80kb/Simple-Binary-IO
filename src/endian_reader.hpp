#ifndef __ENDIAN_READER_HPP__
#define __ENDIAN_READER_HPP__

#include <iostream>
#include <fstream>

class EndianReader
{
        std::ifstream& _fin;
        char* _buffer;
        int _position;
        int _endianness;

public:
        EndianReader(std::ifstream &fin, int endianness) : _fin(fin), _position(0), _endianness(endianness) {}
        ~EndianReader() {}

private:
        void FillBuffer(const int count, int stride)
        {
                char buffer[count];
                _fin.read(buffer, count);
                _position += count;

        }
};

#endif
