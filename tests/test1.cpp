#include <iostream>
#include <fstream>
#include <unistd.h>
#include "../src/endian_reader.hpp"

int main(int argc, char** argv)
{
        if(argc != 2)
        {
                std::cout << "missing file argument" << std::endl;
                return 1;
        }
        
        std::ifstream fin(argv[1], std::ios::in | std::ios::binary);
        EndianReader reader(fin, argv[1], ENDIAN_BIG);

        char magic[4];
        reader.ReadBytes(magic, 4);

        std::cout << magic[0]
                << magic[1]
                << magic[2]
                << magic[3]
                << std::endl;
}
