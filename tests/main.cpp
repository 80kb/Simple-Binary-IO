#include <iostream>
#include <fstream>
#include "../src/endian_writer.hpp"

int main(int argc, char** argv)
{
        if(argc != 2)
        {
                std::cout << "missing file argument" << std::endl;
                return 1;
        }

        EndianWriter writer(argv[1], ENDIAN_BIG);

        // write byte
        char byte0 = 0x0A;
        writer.WriteByte(byte0);

        // write UInt16
        uint16_t num0 = 0x58;
        writer.WriteUInt16(num0);

        // write Int16
        int16_t num1 = -34;
        writer.WriteInt16(num1);

        // write UInt24
        uint32_t num2 = 0xDEAF00;
        writer.WriteUInt24(num2);

        // write Int32
        uint32_t num3 = 0xC0FFEE;
        writer.WriteInt32(num3);

        // write stringNT
        char word[6] = "money";
        writer.WriteStringNT(word, 6);

        // write float
        float num4 = 0.456;
        writer.WriteFloat(num4);

        return 0;
}
