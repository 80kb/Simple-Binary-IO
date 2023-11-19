#include "../src/endian_writer.hpp"

int main()
{
        ////////////////////////////////////////////////////////
        ////////////////        Write File      ////////////////
        ////////////////////////////////////////////////////////

        EndianWriter writer("sample.bin", ENDIAN_BIG);

        char byte0 = 0x0A;
        writer.WriteByte(byte0);

        uint16_t num0 = 0x58;
        writer.WriteUInt16(num0);

        int16_t num1 = -34;
        writer.WriteInt16(num1);

        uint32_t num2 = 0xDEAF00;
        writer.WriteUInt24(num2);

        uint32_t num3 = 0xC0FFEE;
        writer.WriteInt32(num3);

        char word[6] = "money";
        writer.WriteStringNT(word, 6);

        float num4 = 0.456;
        writer.WriteFloat(num4);

        return 0;
}
