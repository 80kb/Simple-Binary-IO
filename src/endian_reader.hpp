#ifndef __ENDIAN_READER_HPP__
#define __ENDIAN_READER_HPP__

#define ENDIAN_LITTLE 0
#define ENDIAN_BIG 1

#include <iostream>
#include <fstream>
#include <stdexcept>

class EndianReader
{
        std::ifstream& _fin;
        int _stream_length;
        char* _buffer;
        int _position;
        int _endianness;

public:
        EndianReader(std::ifstream& fin, int stream_length, int endianness) 
                : _fin(fin), _stream_length(stream_length), _position(0), _endianness(endianness) {}
        ~EndianReader()
        {
                _fin.close();
        }

private:
        // Throws an exception if the attempted operation is invalid
        //
        // int length: the length of bytes to attempt to read
        void Try(int length)
        {
                if(_position + length > _stream_length)
                        throw std::invalid_argument("length extends past stream");
        }

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
                _buffer = buffer;
                _position += count;
                if(_endianness == ENDIAN_LITTLE)
                {
                        for(int i = 0; i < count; i += stride)
                        {
                                ReverseBufferSegment(i, stride);
                        }
                }
        }

public:
        char ReadByte()
        {
                Try(1);
                FillBuffer(1, 1);
                return _buffer[0];
        }
};

#endif
