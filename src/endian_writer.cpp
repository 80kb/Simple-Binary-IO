#include "endian_lib.h"
#include <string.h>

EndianWriter::EndianWriter(const char* filename, int endianness) : _endianness(endianness)
{
        _fout.open(filename, std::ios::out | std::ios::binary);
}

EndianWriter::~EndianWriter() { Close(); }

//--- Position
int EndianWriter::GetPosition() { return _fout.tellp(); }
void EndianWriter::SetPosition(int position) { _fout.seekp(position, std::ios::beg); }

//--- Cleanup
void EndianWriter::Close() { _fout.close(); }

//--- Underlying write call
void EndianWriter::WriteBuffer(char* buffer, const int count, int stride)
{
        if(_endianness == ENDIAN_BIG) {
                for(int i = 0; i < count; i += stride)
                        ReverseBufferSegment(buffer, i, stride);
        }
        _fout.write(buffer, count);
}

////////////////////////////////////////////////////////////////////////
////////////////                Write Byte              ////////////////
////////////////////////////////////////////////////////////////////////

void EndianWriter::WriteByte(uint8_t data)
{
        char buffer[1];
        buffer[0] = (char)data;
        WriteBuffer(buffer, 1, 1);
}

void EndianWriter::WriteBytes(uint8_t *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteByte(data[i]);
}

void EndianWriter::WriteSByte(int8_t data)
{
        char buffer[1];
        buffer[0] = (char)data;
        WriteBuffer(buffer, 1, 1);
}

void EndianWriter::WriteSBytes(int8_t *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteSByte(data[i]);
}

////////////////////////////////////////////////////////////////////////
////////////////                Write Int16             ////////////////
////////////////////////////////////////////////////////////////////////

void EndianWriter::WriteUInt16(uint16_t data)
{
        char buffer[2];
        memcpy(buffer, &data, 2);
        WriteBuffer(buffer, 2, 2);
}

void EndianWriter::WriteUInt16s(uint16_t *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteUInt16(data[i]);
}

void EndianWriter::WriteInt16(int16_t data)
{
        char buffer[2];
        memcpy(buffer, &data, 2);
        WriteBuffer(buffer, 2, 2);
}

void EndianWriter::WriteInt16s(int16_t *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteInt16(data[i]);
}

////////////////////////////////////////////////////////////////////////
////////////////                Write Int24             ////////////////
////////////////////////////////////////////////////////////////////////

void EndianWriter::WriteUInt24(uint32_t data)
{
        char buffer[3];
        buffer[2] = (char)((data >> 16) & 0xFFu);
        buffer[1] = (char)((data >> 8) & 0xFFu);
        buffer[0] = (char)(data & 0xFFu);
        WriteBuffer(buffer, 3, 3);
}

void EndianWriter::WriteUInt24(uint32_t *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteUInt24(data[i]);
}

void EndianWriter::WriteInt24(int32_t data)
{
        char buffer[3];
        buffer[2] = (char)((int32_t)(data >> 16) & 0xFFu);
        buffer[1] = (char)((int32_t)(data >> 8) & 0xFFu);
        buffer[0] = (char)((int32_t)data & 0xFFu);
        WriteBuffer(buffer, 3, 3);
}

void EndianWriter::WriteInt24s(int32_t *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteInt24(data[i]);
}

////////////////////////////////////////////////////////////////////////
////////////////                Write Int32             ////////////////
////////////////////////////////////////////////////////////////////////

void EndianWriter::WriteUInt32(uint32_t data)
{
        char buffer[4];
        memcpy(buffer, &data, 4);
        WriteBuffer(buffer, 4, 4);
}

void EndianWriter::WriteUInt32s(uint32_t *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteUInt32(data[i]);
}

void EndianWriter::WriteInt32(int32_t data)
{
        char buffer[4];
        memcpy(buffer, &data, 4);
        WriteBuffer(buffer, 4, 4);
}

void EndianWriter::WriteInt32s(int32_t *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteInt32(data[i]);
}

///////////////////////////////////////////////////////////////////////
////////////////                Write Float            ////////////////
///////////////////////////////////////////////////////////////////////

void EndianWriter::WriteFloat(float data)
{
        char buffer[4];
        memcpy(buffer, &data, 4);
        WriteBuffer(buffer, 4, 4);
}

void EndianWriter::WriteFloats(float *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteFloat(data[i]);
}

////////////////////////////////////////////////////////////////////////
////////////////                Write Double            ////////////////
////////////////////////////////////////////////////////////////////////

void EndianWriter::WriteDouble(double data)
{
        char buffer[8];
        memcpy(buffer, &data, 8);
        WriteBuffer(buffer, 8, 8);
}

void EndianWriter::WriteDoubles(double *data, int length)
{
        for(int i = 0; i < length; i++)
                WriteDouble(data[i]);
}

////////////////////////////////////////////////////////////////////////
////////////////                Write Strings           ////////////////
////////////////////////////////////////////////////////////////////////

void EndianWriter::WriteStringNT(char *data)
{
        int i = 0;
        while(data[i] != 0)
                WriteByte(data[i++]);
        WriteByte(0);
}

