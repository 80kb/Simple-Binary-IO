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
                Close();
        }

        int GetPosition() { return _fin.tellg(); }
        void SetPosition(int position)
        {
                _position = position;
                _fin.seekg(position, std::ios::beg);
        }

        int GetLength() { return _stream_length; }
        int GetEndianness() { return _endianness; }
        void Close() { _fin.close(); }

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

        uint8_t ReadByte()
        {
                Try(1);
                char buffer[1];
                FillBuffer(buffer, 1, 1);
                return (uint8_t)buffer[0];
        }

        std::vector<uint8_t> ReadBytes(int length)
        {
                Try(length);
                std::vector<uint8_t> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadByte());
                return buffer;
        }

        int8_t ReadSByte()
        {
                Try(1);
                char buffer[1];
                FillBuffer(buffer, 1, 1);
                return (int8_t)buffer[0];
        }

        std::vector<int8_t> ReadSBytes(int length)
        {
                Try(length);
                std::vector<int8_t> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadSByte());
                return buffer;
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

        std::vector<uint16_t> ReadUInt16s(int length)
        {
                Try(length * sizeof(uint16_t));
                std::vector<uint16_t> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadUInt16());
                return buffer;
        }

        int16_t ReadInt16()
        {
                Try(2);
                char buffer[2];
                FillBuffer(buffer, 2, 2);
                return (uint16_t)((unsigned char)buffer[1] << 8) |
                        (unsigned char)buffer[0];
        }

        std::vector<int16_t> ReadInt16s(int length)
        {
                Try(length * sizeof(int16_t));
                std::vector<int16_t> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadInt16());
                return buffer;
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

        std::vector<uint32_t> ReadUInt24s(int length)
        {
                Try(length * 3);
                std::vector<uint32_t> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadUInt24());
                return buffer;
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

        std::vector<int32_t> ReadInt24s(int length)
        {
                Try(length * 3);
                std::vector<int32_t> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadInt24());
                return buffer;
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

        std::vector<uint32_t> ReadUInt32s(int length)
        {
                Try(length * sizeof(uint32_t));
                std::vector<uint32_t> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadUInt32());
                return buffer;
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

        std::vector<int32_t> ReadInt32s(int length)
        {
                Try(length * sizeof(int32_t));
                std::vector<int32_t> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadInt32());
                return buffer;
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Read Float              ////////////////
        ////////////////////////////////////////////////////////////////////////

        float ReadFloat()
        {
                Try(4);
                char buffer[4];
                FillBuffer(buffer, 4, 4);

                float out;
                memcpy(&out, buffer, sizeof out);
                return out;
        }

        std::vector<float> ReadFloats(int length)
        {
                Try(length * sizeof(float));
                std::vector<float> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadFloat());
                return buffer;
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

        std::vector<double> ReadDoubles(int length)
        {
                Try(length * sizeof(double));
                std::vector<double> buffer;
                for(int i = 0; i < length; i++)
                        buffer.push_back(ReadDouble());
                return buffer;
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
