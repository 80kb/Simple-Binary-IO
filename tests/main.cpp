#include <iostream>
#include "../src/endian_lib.h"

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

        char word[32] = "money";
        writer.WriteStringNT(word);

        float num4 = 0.456;
        writer.WriteFloat(num4);

        uint8_t bytes[4] = {0xA, 0xB, 0xC, 0xD};
        writer.WriteBytes(bytes, 4);

        writer.Close();

        ////////////////////////////////////////////////////////
        ////////////////        Read File       ////////////////
        ////////////////////////////////////////////////////////

        EndianReader reader("sample.bin", ENDIAN_BIG);

        char r_byte0 = reader.ReadByte();
        uint16_t r_num0 = reader.ReadUInt16();
        int16_t r_num1 = reader.ReadInt16();
        uint32_t r_num2 = reader.ReadUInt24();
        uint32_t r_num3 = reader.ReadUInt32();
        char r_str[32]; reader.ReadStringNT(r_str);
        float r_num4 = reader.ReadFloat();
        uint8_t buffer[4]; reader.ReadBytes(buffer, 4);

        std::cout << "reading from sample.bin"  << std::endl << std::endl;
        std::cout << "ReadByte():\t\t"          << (int)r_byte0 << std::endl;
        std::cout << "ReadUInt16():\t\t"        << r_num0 << std::endl;
        std::cout << "ReadInt16():\t\t"         << r_num1 << std::endl;
        std::cout << "ReadUInt24():\t\t"        << r_num2 << std::endl;
        std::cout << "ReadUInt32():\t\t"        << r_num3 << std::endl;
        std::cout << "ReadStringNT():\t\t"      << r_str << std::endl;
        std::cout << "ReadFloat():\t\t"         << r_num4 << std::endl;
        std::cout << "ReadBytes():\t\t{ ";
        for(int i = 0; i < 4; i++) std::cout << (int)buffer[i] << " ";
        std::cout << "}" << std::endl;

        reader.Close();

        return 0;
}
