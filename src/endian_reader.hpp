#ifndef __ENDIAN_READER_HPP__
#define __ENDIAN_READER_HPP__

#define ENDIAN_LITTLE 0
#define ENDIAN_BIG 1

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
        ~EndianReader()
        {
                _fin.close();
        }

private:
        // Reverses a subset of the buffer
        //
        // int start: the index at which to start reversing
        // int size: the amount of elements in the subset to reverse
        void ReverseBufferSegment(int start, int size)
        {
                for(int i = start; i < size / 2; i++)
                {
                        int tmp = _buffer[i];
                        _buffer[i] = _buffer[(start + size) - i];
                        _buffer[(start + size) - i] = tmp;
                }
        }

        // Reads a given amount of bytes into the buffer
        //
        // const int count: the amount of bytes to read
        // int stride: the size of each datatype subdivision
        void FillBuffer(const int count, int stride)
        {
                char buffer[count];
                _fin.read(buffer, count);
                _position += count;
                if(_endianness == ENDIAN_LITTLE)
                {
                        for(int i = 0; i < count; i += stride)
                        {
                                ReverseBufferSegment(i, stride);
                        }
                }
        }
};

#endif
