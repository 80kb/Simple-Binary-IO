#include <iostream>
#include "../src/endian_writer.hpp"
#include "../src/endian_reader.hpp"

int main(int argc, char** argv)
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

        ////////////////////////////////////////////////////////
        ////////////////        Read File       ////////////////
        ////////////////////////////////////////////////////////

        EndianReader reader("sample.bin", ENDIAN_BIG);

        char byte0      = reader.ReadByte();
        uint16_t num0   = reader.ReadUInt16();
        int16_t num1    = reader.ReadInt16();
        uint32_t num2   = reader.ReadUInt24();
        uint32_t num3   = reader.ReadUInt32();
        std::string str = reader.ReadStringNT();
        float num4      = reader.ReadFloat();

        std::cout << "reading from sample.bin\n\n";
        std::cout << "ReadByte():\t\t" << byte0 << std::endl;
        std::cout << "ReadUInt16():\t\t" << num0 << std::endl;
        std::cout << "ReadInt16():\t\t" << num1 << std::endl;
        std::cout << "ReadUInt24():\t\t" << num2 << std::endl;
        std::cout << "ReadUInt32():\t\t" << num3 << std::endl;
        std::cout << "ReadStringNT():\t\t" << str << std::endl;
        std::cout << "ReadFloat():\t\t" << num4 << std::endl;

        return 0;
}
