#include <iostream>
#include "../src/endian_reader.hpp"

int main()
{
        ////////////////////////////////////////////////////////
        ////////////////        Read File       ////////////////
        ////////////////////////////////////////////////////////

        EndianReader reader("sample.bin", ENDIAN_BIG);

        char r_byte0      = reader.ReadByte();
        uint16_t r_num0   = reader.ReadUInt16();
        int16_t r_num1    = reader.ReadInt16();
        uint32_t r_num2   = reader.ReadUInt24();
        uint32_t r_num3   = reader.ReadUInt32();
        std::string r_str = reader.ReadStringNT();
        float r_num4      = reader.ReadFloat();

        std::cout << "reading from sample.bin\n\n";
        std::cout << "ReadByte():\t\t" << (int)r_byte0 << std::endl;
        std::cout << "ReadUInt16():\t\t" << r_num0 << std::endl;
        std::cout << "ReadInt16():\t\t" << r_num1 << std::endl;
        std::cout << "ReadUInt24():\t\t" << r_num2 << std::endl;
        std::cout << "ReadUInt32():\t\t" << r_num3 << std::endl;
        std::cout << "ReadStringNT():\t\t" << r_str << std::endl;
        std::cout << "ReadFloat():\t\t" << r_num4 << std::endl;

        return 0;
}

