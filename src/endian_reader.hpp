#ifndef __ENDIAN_READER_HPP__
#define __ENDIAN_READER_HPP__

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

class EndianReader
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
        void ReverseBufferSegment(char* buffer, int start, int size);
        void FillBuffer(char* buffer, const int count, int stride);
};

#endif // __ENDIAN_READER_HPP__
