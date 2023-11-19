#ifndef __ENDIAN_READER_HPP__
#define __ENDIAN_READER_HPP__

#include "endian_lib.hpp"

class EndianReader
{
        std::ifstream _fin;
        int _stream_length;
        int _position;
        int _endianness;

public:
        EndianReader(const char* filename, int endianness) : _position(0), _endianness(endianness)
        {
                //--- Get file length

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

                //--- Open stream for reading

                _fin.open(filename, std::ios::in | std::ios::binary);
        }
        ~EndianReader()
        {
                _fin.close();
        }

        int Position() { return _position; }
        int Length() { return _stream_length; }
        int Endianness() { return _endianness; }

private:
        //--- Throws an exception if the attempted operation is invalid

        void Try(int length)
        {
                if(_position + length > _stream_length)
                        throw std::invalid_argument("length extends past stream");
        }

        //--- Reverses a subset of the buffer
        
        void ReverseBufferSegment(char* buffer, int start, int size)
        {
                int end = start + size - 1;
                while (start < end)
                {
                        int temp = buffer[start];
                        buffer[start] = buffer[end];
                        buffer[end] = temp;
                        start++;
                        end--;
                }
        }

        //--- Reads a given amount of bytes into the buffer

        void FillBuffer(char* buffer, const int count, int stride)
        {
                _fin.read(buffer, count);
                _position += count;
                if(_endianness == ENDIAN_BIG)
                {
                        for(int i = 0; i < count; i += stride)
                                ReverseBufferSegment(buffer, i, stride);
                }
        }

public:
        ////////////////////////////////////////////////////////////////////////
        ////////////////                Read Bytes              ////////////////
        ////////////////////////////////////////////////////////////////////////
        
        char ReadByte()
        {
                Try(1);
                char buffer[1];
                FillBuffer(buffer, 1, 1);
                return buffer[0];
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
                char buffer[1];
                FillBuffer(buffer, 1, 1);
                return (signed char)buffer[0];
        }

        void ReadSBytes(char* sbytes, int length)
        {
                Try(length);
                for(int i = 0; i < length; i++)
                        sbytes[i] = ReadSByte();
        }
        
        ////////////////////////////////////////////////////////////////////////
        ////////////////                Read Int16              ////////////////
        ////////////////////////////////////////////////////////////////////////

        uint16_t ReadUInt16()
        {
                Try(2);
                char buffer[2];
                FillBuffer(buffer, 2, 2);
                return (uint16_t)((unsigned char)buffer[1] << 8) | 
                        (unsigned char)buffer[0];
        }

        void ReadUInt16s(unsigned short* arr, int length)
        {
                Try(length * 2);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadUInt16();
        }

        uint16_t ReadInt16()
        {
                Try(2);
                char buffer[2];
                FillBuffer(buffer, 2, 2);
                return (uint16_t)((unsigned char)buffer[1] << 8) | 
                        (unsigned char)buffer[0];
        }

        void ReadInt16s(short* arr, int length)
        {
                Try(length * 2);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadInt16();
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Read Int24              ////////////////
        ////////////////////////////////////////////////////////////////////////

        uint32_t ReadUInt24()
        {
                Try(3);
                char buffer[3];
                FillBuffer(buffer, 3, 3);
                return (uint32_t)((unsigned char)buffer[2] << 16) |
                        ((unsigned char)buffer[1] << 8) |
                        (unsigned char)buffer[0];
        }

        void ReadUInt24s(unsigned int* arr, int length)
        {
                Try(length * 3);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadUInt24();
        }

        int32_t ReadInt24()
        {
                Try(3);
                char buffer[3];
                FillBuffer(buffer, 3, 3);
                return (int32_t)((unsigned char)buffer[2] << 16) |
                        ((unsigned char)buffer[1] << 8) |
                        (unsigned char)buffer[0];
        }

        void ReadInt24s(int* arr, int length)
        {
                Try(length * 3);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadInt24();
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Read Int32              ////////////////
        ////////////////////////////////////////////////////////////////////////

        uint32_t ReadUInt32()
        {
                Try(4);
                char buffer[4];
                FillBuffer(buffer, 4, 4);

                return (uint32_t)((unsigned char)buffer[3] << 24) |
                        ((unsigned char)buffer[2] << 16) |
                        ((unsigned char)buffer[1] << 8) |
                        (unsigned char)buffer[0];
        }

        void ReadUInt32s(unsigned int* arr, int length)
        {
                Try(length * 4);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadUInt32();
        }

        int32_t ReadInt32()
        {
                Try(4);
                char buffer[4];
                FillBuffer(buffer, 4, 4);
                return (int32_t)((unsigned char)buffer[3] << 24) |
                        ((unsigned char)buffer[2] << 16) |
                        ((unsigned char)buffer[1] << 8) |
                        (unsigned char)buffer[0];
        }

        void ReadInt32s(int* arr, int length)
        {
                Try(length * 4);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadInt32();
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Read Float              ////////////////
        ////////////////////////////////////////////////////////////////////////

        double ReadFloat()
        {
                Try(4);
                char buffer[4];
                FillBuffer(buffer, 4, 4);

                float out;
                memcpy(&out, buffer, sizeof out);
                return out;
        }

        void ReadFloats(float* arr, int length)
        {
                Try(length * 4);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadFloat();
        }

        /////////////////////////////////////////////////////////////////////////
        ////////////////                Read Double              ////////////////
        /////////////////////////////////////////////////////////////////////////

        double ReadDouble()
        {
                Try(8);
                char buffer[8];
                FillBuffer(buffer, 8, 8);

                double out;
                memcpy(&out, buffer, sizeof out);
                return out;
        }

        void ReadDoubles(double* arr, int length)
        {
                Try(length * 8);
                for(int i = 0; i < length; i++)
                        arr[i] = ReadDouble();
        }

        //////////////////////////////////////////////////////////////////////////
        ////////////////                Read Strings              ////////////////
        //////////////////////////////////////////////////////////////////////////
        
        std::string ReadStringNT()
        {
                std::string out = "";
                char letter = ReadByte();
                while(letter != 0)
                {
                        out += letter;
                        letter = ReadByte();
                }
                return out;
        }
};

#endif
