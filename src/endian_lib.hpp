#ifndef __ENDIAN_LIB_HPP__
#define __ENDIAN_LIB_HPP__

#include <fstream>
#include <vector>
#include <string>
#include <string.h>

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

///////////////////////////////////////////////////////////////////////////////////////

EndianReader::EndianReader(const char* filename, int endianness) : _endianness(endianness)
{
    // Get file length
    std::ifstream file(filename, std::ios::binary | std::ios::in | std::ios::ate);
    int size = -1;
    if (file) {
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
    if (_endianness == ENDIAN_BIG) {
        for (int i = 0; i < count; i += stride)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < length; i++)
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
    while (letter != 0)
    {
        out += letter;
        letter = ReadByte();
    }
    return out;
}

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

///////////////////////////////////////////////////////////////////////////////////////

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
    if (_endianness == ENDIAN_BIG) {
        for (int i = 0; i < count; i += stride)
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

void EndianWriter::WriteBytes(std::vector<uint8_t> data)
{
    for (size_t i = 0; i < data.size(); i++)
        WriteByte(data[i]);
}

void EndianWriter::WriteSByte(int8_t data)
{
    char buffer[1];
    buffer[0] = (char)data;
    WriteBuffer(buffer, 1, 1);
}

void EndianWriter::WriteSBytes(std::vector<int8_t> data)
{
    for (size_t i = 0; i < data.size(); i++)
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

void EndianWriter::WriteUInt16s(std::vector<uint16_t> data)
{
    for (size_t i = 0; i < data.size(); i++)
        WriteUInt16(data[i]);
}

void EndianWriter::WriteInt16(int16_t data)
{
    char buffer[2];
    memcpy(buffer, &data, 2);
    WriteBuffer(buffer, 2, 2);
}

void EndianWriter::WriteInt16s(std::vector<int16_t> data)
{
    for (size_t i = 0; i < data.size(); i++)
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

void EndianWriter::WriteUInt24(std::vector<uint32_t> data)
{
    for (size_t i = 0; i < data.size(); i++)
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

void EndianWriter::WriteInt24s(std::vector<int32_t> data)
{
    for (size_t i = 0; i < data.size(); i++)
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

void EndianWriter::WriteUInt32s(std::vector<uint32_t> data)
{
    for (size_t i = 0; i < data.size(); i++)
        WriteUInt32(data[i]);
}

void EndianWriter::WriteInt32(int32_t data)
{
    char buffer[4];
    memcpy(buffer, &data, 4);
    WriteBuffer(buffer, 4, 4);
}

void EndianWriter::WriteInt32s(std::vector<int32_t> data)
{
    for (size_t i = 0; i < data.size(); i++)
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

void EndianWriter::WriteFloats(std::vector<float> data)
{
    for (size_t i = 0; i < data.size(); i++)
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

void EndianWriter::WriteDoubles(std::vector<double> data)
{
    for (size_t i = 0; i < data.size(); i++)
        WriteDouble(data[i]);
}

////////////////////////////////////////////////////////////////////////
////////////////                Write Strings           ////////////////
////////////////////////////////////////////////////////////////////////

void EndianWriter::WriteStringNT(std::string data)
{
    for (size_t i = 0; i < data.size(); i++)
        WriteByte(data[i]);
    WriteByte(0);
}

#endif // __ENDIAN_LIB_HPP__
