#pragma once
#include <cstdint>

#ifndef ENDIAN_LITTLE
#define ENDIAN_LITTLE 0
#endif // ENDIAN_LITTLE
#ifndef ENDIAN_BIG
#define ENDIAN_BIG 1
#endif // ENDIAN_LITTLE

/////////////////////////////////////////////////////////////////////////
////////////////                EndianLib                ////////////////
/////////////////////////////////////////////////////////////////////////

class EndianAbstract {
public:
	virtual int Position() = 0;
	virtual void SetPosition(int position) = 0;

protected:
	void ReverseBufferSegment(char *buffer, int start, int size) {
		int end = start + size - 1;
		while (start < end) {
			int tmp = buffer[start];
			buffer[start] = buffer[end];
			buffer[end] = tmp;
			start++;
			end--;
		}
	}
};

////////////////////////////////////////////////////////////////////////////
////////////////                EndianReader                ////////////////
////////////////////////////////////////////////////////////////////////////

class EndianReader : public EndianAbstract {
	char *_buffer;
	int _position;
	int _stream_length;
	int _endianness;

public:
	EndianReader(char *buffer, int length, int endianness);

	int GetPosition();
	void SetPosition(int position);

	uint8_t ReadByte();
	int8_t ReadSByte();
	void ReadBytes(uint8_t *buffer, int length);
	void ReadSBytes(int8_t *buffer, int length);

	uint16_t ReadUInt16();
	int16_t ReadInt16();
	void ReadUInt16s(uint16_t *buffer, int length);
	void ReadInt16s(int16_t *buffer, int length);

	uint32_t ReadUInt24();
	int32_t ReadInt24();
	void ReadUInt24s(uint32_t *buffer, int length);
	void ReadInt24s(int32_t *buffer, int length);

	uint32_t ReadUInt32();
	int32_t ReadInt32();
	void ReadUInt32s(uint32_t *buffer, int length);
	void ReadInt32s(int32_t *buffer, int length);

	float ReadFloat();
	void ReadFloats(float *buffer, int length);

	double ReadDouble();
	void ReadDoubles(double *buffer, int length);

	void ReadStringNT(char *buffer);

	private:
	void Try(int length);
	void FillBuffer(char *buffer, const int count, int stride);
};

////////////////////////////////////////////////////////////////////////////
////////////////                BufferWriter                ////////////////
////////////////////////////////////////////////////////////////////////////

class EndianWriter : public EndianAbstract {
	char *_buffer;
	int _position;
	int _endianness;

public:
	EndianWriter(char *buffer, int endianness);

	int GetPosition();
	void SetPosition(int position);

	void WriteByte(uint8_t data);
	void WriteSByte(int8_t data);
	void WriteBytes(uint8_t *data, int length);
	void WriteSBytes(int8_t *data, int length);

	void WriteUInt16(uint16_t data);
	void WriteInt16(int16_t data);
	void WriteUInt16s(uint16_t *data, int length);
	void WriteInt16s(int16_t *data, int length);

	void WriteUInt24(uint32_t data);
	void WriteInt24(int32_t data);
	void WriteUInt24(uint32_t *data, int length);
	void WriteInt24s(int32_t *data, int length);

	void WriteUInt32(uint32_t data);
	void WriteInt32(int32_t data);
	void WriteUInt32s(uint32_t *data, int length);
	void WriteInt32s(int32_t *data, int length);

	void WriteFloat(float data);
	void WriteFloats(float *data, int length);

	void WriteDouble(double data);
	void WriteDoubles(double *data, int length);

	void WriteStringNT(char *data);

	private:
	void WriteBuffer(char *buffer, const int count, int stride);
};
