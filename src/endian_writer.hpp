#ifndef __ENDIAN_WRITER_HPP__
#define __ENDIAN_WRITER_HPP__

#include "endian_lib.hpp"

class EndianWriter
{
        std::ofstream _fout;
        int _position;
        int _endianness;

public:
        EndianWriter(const char* filename, int endianness) : _position(0), _endianness(endianness)
        {
                _fout.open(filename, std::ios::out | std::ios::binary);
        }
        ~EndianWriter()
        {
                Close();
        }

        int GetPosition() { return _fout.tellp(); }
        void SetPosition(int position)
        {
                _position = position;
                _fout.seekp(position, std::ios::beg);
        }

        int GetEndianness() { return _endianness; }
        void Close() { _fout.close(); }

private:

        //--- Reverses subset of given buffer

        void ReverseBufferSegment(char* buffer, int start, int size)
        {
                int end = start + size - 1;
                while(start < end)
                {
                        int temp = buffer[start];
                        buffer[start] = buffer[end];
                        buffer[end] = temp;
                        start++;
                        end--;
                }
        }

        //--- Writes a given buffer to disk via the stream

        void WriteBuffer(char* buffer, const int count, int stride)
        {
                _position += count;
                if(_endianness == ENDIAN_BIG)
                {
                        for(int i = 0; i < count; i += stride)
                                ReverseBufferSegment(buffer, i, stride);
                }
                _fout.write(buffer, count);
        }

public:

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Write Byte              ////////////////
        ////////////////////////////////////////////////////////////////////////

        void WriteByte(uint8_t data)
        {
                char buffer[1];
                buffer[0] = (char)data;
                WriteBuffer(buffer, 1, 1);
        }

        void WriteBytes(std::vector<uint8_t> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteByte(data[i]);
        }

        void WriteSByte(int8_t data)
        {
                char buffer[1];
                buffer[0] = (char)data;
                WriteBuffer(buffer, 1, 1);
        }

        void WriteSBytes(std::vector<int8_t> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteSByte(data[i]);
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Write Int16             ////////////////
        ////////////////////////////////////////////////////////////////////////

        void WriteUInt16(uint16_t data)
        {
                char buffer[2];
                memcpy(buffer, &data, 2);
                WriteBuffer(buffer, 2, 2);
        }

        void WriteUInt16s(std::vector<uint16_t> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteUInt16(data[i]);
        }

        void WriteInt16(int16_t data)
        {
                char buffer[2];
                memcpy(buffer, &data, 2);
                WriteBuffer(buffer, 2, 2);
        }

        void WriteInt16s(std::vector<int16_t> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteInt16(data[i]);
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Write Int24             ////////////////
        ////////////////////////////////////////////////////////////////////////

        void WriteUInt24(uint32_t data)
        {
                char buffer[3];
                buffer[2] = (char)((data >> 16) & 0xFFu);
                buffer[1] = (char)((data >> 8) & 0xFFu);
                buffer[0] = (char)(data & 0xFFu);
                WriteBuffer(buffer, 3, 3);
        }

        void WriteUInt24(std::vector<uint32_t> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteUInt24(data[i]);
        }

        void WriteInt24(int32_t data)
        {
                char buffer[3];
                buffer[2] = (char)((int32_t)(data >> 16) & 0xFFu);
                buffer[1] = (char)((int32_t)(data >> 8) & 0xFFu);
                buffer[0] = (char)((int32_t)data & 0xFFu);
                WriteBuffer(buffer, 3, 3);
        }

        void WriteInt24s(std::vector<int32_t> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteInt24(data[i]);
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Write Int32             ////////////////
        ////////////////////////////////////////////////////////////////////////

        void WriteUInt32(uint32_t data)
        {
                char buffer[4];
                memcpy(buffer, &data, 4);
                WriteBuffer(buffer, 4, 4);
        }

        void WriteUInt32s(std::vector<uint32_t> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteUInt32(data[i]);
        }

        void WriteInt32(int32_t data)
        {
                char buffer[4];
                memcpy(buffer, &data, 4);
                WriteBuffer(buffer, 4, 4);
        }

        void WriteInt32s(std::vector<int32_t> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteInt32(data[i]);
        }

        ///////////////////////////////////////////////////////////////////////
        ////////////////                Write Float            ////////////////
        ///////////////////////////////////////////////////////////////////////

        void WriteFloat(float data)
        {
                char buffer[4];
                memcpy(buffer, &data, 4);
                WriteBuffer(buffer, 4, 4);
        }

        void WriteFloats(std::vector<float> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteFloat(data[i]);
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Write Double            ////////////////
        ////////////////////////////////////////////////////////////////////////

        void WriteDouble(double data)
        {
                char buffer[8];
                memcpy(buffer, &data, 8);
                WriteBuffer(buffer, 8, 8);
        }

        void WriteDoubles(std::vector<double> data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteDouble(data[i]);
        }

        ////////////////////////////////////////////////////////////////////////
        ////////////////                Write Strings           ////////////////
        ////////////////////////////////////////////////////////////////////////

        void WriteStringNT(std::string data)
        {
                for(int i = 0; i < data.size(); i++)
                        WriteByte(data[i]);
                WriteByte(0);
        }
};

#endif
