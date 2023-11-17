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
        EndianReader(std::ifstream& fin, const char* filename, int endianness) : _fin(fin), _position(0), _endianness(endianness)
        {
                // Get file length
                std::ifstream file(filename, std::ios::binary | std::ios::in | std::ios::ate);
                int size = -1;
                if(file)
                {
                        file.seekg(0, std::ios::end);
                        size = file.tellg();
                }
                else
                {
                        perror(filename);
                }
                _stream_length = size;
                file.close();
        }
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
        // Returns single byte from stream
        char ReadByte()
        {
                Try(1);
                FillBuffer(1, 1);
                return _buffer[0];
        }

        // Returns array of bytes from stream
        //
        // char* bytes: the return array in which to store the bytes
        // int length: the amount of bytes to read
        void ReadBytes(char* bytes, int length)
        {
                Try(length);
                for(int i = 0; i < length; i++)
                        bytes[i] = ReadByte();
        }
};

#endif
