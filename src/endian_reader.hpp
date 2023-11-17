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
                int end = start + size - 1;
                while (start < end)
                {
                        int temp = _buffer[start];
                        _buffer[start] = _buffer[end];
                        _buffer[end] = temp;
                        start++;
                        end--;
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
                if(_endianness == ENDIAN_BIG)
                {
                        for(int i = 0; i < count; i += stride)
                                ReverseBufferSegment(i, stride);
                }
        }

public:
        //////////////////////
        ///// Read Bytes /////
        //////////////////////
        
        char ReadByte()
        {
                Try(1);
                FillBuffer(1, 1);
                return _buffer[0];
        }

        void ReadBytes(char* bytes, int length)
        {
                Try(length);
                for(int i = 0; i < length; i++)
                        bytes[i] = ReadByte();
        }

        signed char ReadSByte()
        {
                Try(1);
                FillBuffer(1, 1);
                return (signed char)_buffer[0];
        }

        void ReadSBytes(char* sbytes, int length)
        {
                Try(length);
                for(int i = 0; i < length; i++)
                        sbytes[i] = ReadSByte();
        }
        
        //////////////////////
        ///// Read Int16 /////
        //////////////////////

        unsigned short ReadUInt16()
        {
                Try(2);
                FillBuffer(2, 2);
                return ((unsigned short)_buffer[0] << 8) | _buffer[1];
        }

        void ReadUInt16s(unsigned short* arr, int length)
        {
                Try(length * 2);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadUInt16();
        }

        short ReadInt16()
        {
                Try(2);
                FillBuffer(2, 2);
                return ((short)_buffer[0] << 8) | _buffer[1];
        }

        void ReadInt16s(short* arr, int length)
        {
                Try(length * 2);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadInt16();
        }

        //////////////////////
        ///// Read Int32 /////
        //////////////////////

        unsigned int ReadUInt32()
        {
                Try(4);
                FillBuffer(4, 4);


                return ((unsigned int)_buffer[0] << 24) |
                        (_buffer[1] << 16) |
                        (_buffer[2] << 8) |
                        _buffer[3];
        }

        void ReadUInt32s(unsigned int* arr, int length)
        {
                Try(length * 4);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadUInt32();
        }
};

#endif
