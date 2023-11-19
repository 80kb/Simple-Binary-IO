# Simple-Binary-IO
Simple C++ binary reader/writer made to mimic the syntax of C# binary streams. Supports both big and little endian.

## Example Usage
Full functionality showcased in [tests/main.cpp](tests/main.cpp)
```c++
#include "endian_writer.hpp"

//--- Creates a new writer and writes an big-endian unsigned integer
EndianWriter writer("sample.bin", ENDIAN_BIG);
uint32_t num = 0xC0FFEE;
writer.WriteUInt32(num);
```
```c++
#include "endian_reader.hpp"

//--- Creates a new reader and reads a big-endian unsigned integer
EndianReader reader("sample.bin", ENDIAN_BIG);
uint32_t num = reader.ReadUInt32();
```
