#include "endian_lib.h"
#include <string.h>
#include <assert.h>

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
void EndianReader::Try(int length) { assert(GetPosition() + length <= _stream_length); }

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

void EndianReader::ReadBytes(uint8_t *buffer, int length)
{
        Try(length);
        for(int i = 0; i < length; i++)
                buffer[i] = ReadByte();
}

int8_t EndianReader::ReadSByte()
{
        Try(1);
        char buffer[1];
        FillBuffer(buffer, 1, 1);
        return (int8_t)buffer[0];
}

void EndianReader::ReadSBytes(int8_t *buffer, int length)
{
        Try(length);
        for(int i = 0; i < length; i++)
                buffer[i] = ReadSByte();
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

void EndianReader::ReadUInt16s(uint16_t *buffer, int length)
{
        Try(length * sizeof(uint16_t));
        for(int i = 0; i < length; i++)
                buffer[i] = ReadUInt16();
}

int16_t EndianReader::ReadInt16()
{
        Try(2);
        char buffer[2];
        FillBuffer(buffer, 2, 2);
        return (uint16_t)((unsigned char)buffer[1] << 8) |
                (unsigned char)buffer[0];
}

void EndianReader::ReadInt16s(int16_t *buffer, int length)
{
        Try(length * sizeof(int16_t));
        for(int i = 0; i < length; i++)
                buffer[i] = ReadInt16();
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

void EndianReader::ReadUInt24s(uint32_t *buffer, int length)
{
        Try(length * 3);
        for(int i = 0; i < length; i++)
                buffer[i] = ReadUInt24();
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

void EndianReader::ReadInt24s(int32_t *buffer, int length)
{
        Try(length * 3);
        for(int i = 0; i < length; i++)
                buffer[i] = ReadInt24();
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

void EndianReader::ReadUInt32s(uint32_t *buffer, int length)
{
        Try(length * sizeof(uint32_t));
        for(int i = 0; i < length; i++)
                buffer[i] = ReadUInt32();
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

void EndianReader::ReadInt32s(int32_t *buffer, int length)
{
        Try(length * sizeof(int32_t));
        for(int i = 0; i < length; i++)
                buffer[i] = ReadInt32();
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

void EndianReader::ReadFloats(float *buffer, int length)
{
        Try(length * sizeof(float));
        for(int i = 0; i < length; i++)
                buffer[i] = ReadFloat();
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

void EndianReader::ReadDoubles(double *buffer, int length)
{
        Try(length * sizeof(double));
        for(int i = 0; i < length; i++)
                buffer[i] = ReadDouble();
}

//////////////////////////////////////////////////////////////////////////
////////////////                Read Strings              ////////////////
//////////////////////////////////////////////////////////////////////////

void EndianReader::ReadStringNT(char *buffer)
{
        char letter = ReadByte();
        int i = 0;
        while(letter != 0)
        {
                buffer[i++] = letter;
                letter = ReadByte();
        }
}
