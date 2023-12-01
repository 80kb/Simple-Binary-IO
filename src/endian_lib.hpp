#ifndef __ENDIAN_LIB_HPP__
#define __ENDIAN_LIB_HPP__

#include <fstream>
#include <vector>
#include <string>

#ifndef ENDIAN_LITTLE
#define ENDIAN_LITTLE 0
#endif // ENDIAN_LITTLE

#ifndef ENDIAN_BIG
#define ENDIAN_BIG 1
#endif // ENDIAN_LITTLE

#ifndef ENDIAN_ASSERT
#include <assert.h>
#define ENDIAN_ASSERT assert
#endif // ENDIAN_ASSERT

/////////////////////////////////////////////////////////////////////////
////////////////                EndianLib                ////////////////
/////////////////////////////////////////////////////////////////////////

class EndianAbstract
{
public:
        virtual int GetPosition() = 0;
        virtual void SetPosition(int position) = 0;
        virtual void Close() = 0;

protected:
        void ReverseBufferSegment(char* buffer, int start, int size)
        {
                int end = start + size - 1;
                while(start < end) {
                        int tmp = buffer[start];
                        buffer[start] = buffer[end];
                        buffer[end] = tmp;
                        start++; end--;
                }
        }
};

////////////////////////////////////////////////////////////////////////////
////////////////                EndianReader                ////////////////
////////////////////////////////////////////////////////////////////////////

class EndianReader : public EndianAbstract
{
        std::ifstream _fin;
        int _stream_length;
        int _endianness;

public:
        EndianReader(const char* filename, int endianness);
        ~EndianReader();

        int GetPosition();
        void SetPosition(int position);
        void Close();

        uint8_t ReadByte();
        int8_t ReadSByte();
        std::vector<uint8_t> ReadBytes(int length);
        std::vector<int8_t> ReadSBytes(int length);

        uint16_t ReadUInt16();
        int16_t ReadInt16();
        std::vector<uint16_t> ReadUInt16s(int length);
        std::vector<int16_t> ReadInt16s(int length);

        uint32_t ReadUInt24();
        int32_t ReadInt24();
        std::vector<uint32_t> ReadUInt24s(int length);
        std::vector<int32_t> ReadInt24s(int length);

        uint32_t ReadUInt32();
        int32_t ReadInt32();
        std::vector<uint32_t> ReadUInt32s(int length);
        std::vector<int32_t> ReadInt32s(int length);

        float ReadFloat();
        std::vector<float> ReadFloats(int length);

        double ReadDouble();
        std::vector<double> ReadDoubles(int length);

        std::string ReadStringNT();

private:
        void Try(int length);
        void FillBuffer(char* buffer, const int count, int stride);
};

////////////////////////////////////////////////////////////////////////////
////////////////                EndianWriter                ////////////////
////////////////////////////////////////////////////////////////////////////

class EndianWriter : public EndianAbstract
{
        std::ofstream _fout;
        int _endianness;

public:
        EndianWriter(const char* filename, int endianness);
        ~EndianWriter();

        int GetPosition();
        void SetPosition(int position);
        void Close();

        void WriteByte(uint8_t data);
        void WriteSByte(int8_t data);
        void WriteBytes(std::vector<uint8_t> data);
        void WriteSBytes(std::vector<int8_t> data);

        void WriteUInt16(uint16_t data);
        void WriteInt16(int16_t data);
        void WriteUInt16s(std::vector<uint16_t> data);
        void WriteInt16s(std::vector<int16_t> data);

        void WriteUInt24(uint32_t data);
        void WriteInt24(int32_t data);
        void WriteUInt24(std::vector<uint32_t> data);
        void WriteInt24s(std::vector<int32_t> data);

        void WriteUInt32(uint32_t data);
        void WriteInt32(int32_t data);
        void WriteUInt32s(std::vector<uint32_t> data);
        void WriteInt32s(std::vector<int32_t> data);

        void WriteFloat(float data);
        void WriteFloats(std::vector<float> data);

        void WriteDouble(double data);
        void WriteDoubles(std::vector<double> data);

        void WriteStringNT(std::string data);

private:
        void WriteBuffer(char* buffer, const int count, int stride);
};

#endif // __ENDIAN_LIB_HPP__
