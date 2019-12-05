//SOURCE: https://stackoverflow.com/questions/45992320/how-to-create-an-image-in-c-with-an-2d-rgb-array

#pragma once
#include <cstdint>

#pragma pack(push, 2)
struct BitmapFileHeader {
    char header[2]{'B', 'M'};
    uint32_t fileSize;
    uint32_t reserved{};
    uint32_t dataOffset;
};
#pragma pack(pop)