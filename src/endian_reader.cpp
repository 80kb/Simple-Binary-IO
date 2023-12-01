#include "endian_lib.hpp"
#include <string.h>

EndianReader::EndianReader(const char* filename, int endianness) : _endianness(endianness)
{
        // Get file length
        std::ifstream file(filename, std::ios::binary | std::ios::in | std::ios::ate);
        int size = -1;
        if(file) {
                file.seekg(0, std::ios::end);
                size = file.tellg();
        }
        else
                perror(filename);
        _stream_length = size;
        file.close();

        // Open internal stream
        _fin.open(filename, std::ios::in | std::ios::binary);
}

EndianReader::~EndianReader() { Close(); }

//--- Position
int EndianReader::GetPosition() { return _fin.tellg(); }
void EndianReader::SetPosition(int position) { _fin.seekg(position, std::ios::beg); }

//--- Cleanup
void EndianReader::Close() { _fin.close(); }

//--- Asserts that read attempt does not exceed stream length
void EndianReader::Try(int length) { ENDIAN_ASSERT(GetPosition() + length <= _stream_length); }

//--- Reads a given amount of raw bytes into buffer
void EndianReader::FillBuffer(char* buffer, const int count, int stride)
{
        _fin.read(buffer, count);
        if(_endianness == ENDIAN_BIG) {
                for(int i = 0; i < count; i += stride)
                        ReverseBufferSegment(buffer, i, stride);
        }
}

//////////////////////////////////////////////////////////////////////////
////////////////                Read Bytes                ////////////////
//////////////////////////////////////////////////////////////////////////

uint8_t EndianReader::ReadByte()
{
        Try(1);
        char buffer[1];
        FillBuffer(buffer, 1, 1);
        return (uint8_t)buffer[0];
}

std::vector<uint8_t> EndianReader::ReadBytes(int length)
{
        Try(length);
        std::vector<uint8_t> buffer;
        for(int i = 0; i < length; i++)
                buffer.push_back(ReadByte());
        return buffer;
}

int8_t EndianReader::ReadSByte()
{
        Try(1);
        char buffer[1];
        FillBuffer(buffer, 1, 1);
        return (int8_t)buffer[0];
}

std::vector<int8_t> EndianReader::ReadSBytes(int length)
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

uint16_t EndianReader::ReadUInt16()
{
        Try(2);
        char buffer[2];
        FillBuffer(buffer, 2, 2);
        return (uint16_t)((unsigned char)buffer[1] << 8) |
                (unsigned char)buffer[0];
}

std::vector<uint16_t> EndianReader::ReadUInt16s(int length)
{
        Try(length * sizeof(uint16_t));
        std::vector<uint16_t> buffer;
        for(int i = 0; i < length; i++)
                buffer.push_back(ReadUInt16());
        return buffer;
}

int16_t EndianReader::ReadInt16()
{
        Try(2);
        char buffer[2];
        FillBuffer(buffer, 2, 2);
        return (uint16_t)((unsigned char)buffer[1] << 8) |
                (unsigned char)buffer[0];
}

std::vector<int16_t> EndianReader::ReadInt16s(int length)
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

uint32_t EndianReader::ReadUInt24()
{
        Try(3);
        char buffer[3];
        FillBuffer(buffer, 3, 3);
        return (uint32_t)((unsigned char)buffer[2] << 16) |
                ((unsigned char)buffer[1] << 8) |
                (unsigned char)buffer[0];
}

std::vector<uint32_t> EndianReader::ReadUInt24s(int length)
{
        Try(length * 3);
        std::vector<uint32_t> buffer;
        for(int i = 0; i < length; i++)
                buffer.push_back(ReadUInt24());
        return buffer;
}

int32_t EndianReader::ReadInt24()
{
        Try(3);
        char buffer[3];
        FillBuffer(buffer, 3, 3);
        return (int32_t)((unsigned char)buffer[2] << 16) |
                ((unsigned char)buffer[1] << 8) |
                (unsigned char)buffer[0];
}

std::vector<int32_t> EndianReader::ReadInt24s(int length)
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

uint32_t EndianReader::ReadUInt32()
{
        Try(4);
        char buffer[4];
        FillBuffer(buffer, 4, 4);

        return (uint32_t)((unsigned char)buffer[3] << 24) |
                ((unsigned char)buffer[2] << 16) |
                ((unsigned char)buffer[1] << 8) |
                (unsigned char)buffer[0];
}

std::vector<uint32_t> EndianReader::ReadUInt32s(int length)
{
        Try(length * sizeof(uint32_t));
        std::vector<uint32_t> buffer;
        for(int i = 0; i < length; i++)
                buffer.push_back(ReadUInt32());
        return buffer;
}

int32_t EndianReader::ReadInt32()
{
        Try(4);
        char buffer[4];
        FillBuffer(buffer, 4, 4);
        return (int32_t)((unsigned char)buffer[3] << 24) |
                ((unsigned char)buffer[2] << 16) |
                ((unsigned char)buffer[1] << 8) |
                (unsigned char)buffer[0];
}

std::vector<int32_t> EndianReader::ReadInt32s(int length)
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

float EndianReader::ReadFloat()
{
        Try(4);
        char buffer[4];
        FillBuffer(buffer, 4, 4);

        float out;
        memcpy(&out, buffer, sizeof out);
        return out;
}

std::vector<float> EndianReader::ReadFloats(int length)
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

double EndianReader::ReadDouble()
{
        Try(8);
        char buffer[8];
        FillBuffer(buffer, 8, 8);

        double out;
        memcpy(&out, buffer, sizeof out);
        return out;
}

std::vector<double> EndianReader::ReadDoubles(int length)
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

std::string EndianReader::ReadStringNT()
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
