//SOURCE: https://stackoverflow.com/questions/45992320/how-to-create-an-image-in-c-with-an-2d-rgb-array

#pragma once

#include <cstdint>

#pragma pack(push, 2)
struct BitmapInfoHeader {
    uint32_t headerSize{40};
    uint32_t width{0};
    uint32_t height{0};
    uint16_t planes{1};
    uint16_t bitsPerPixel{24};
    uint32_t compression{0};
    uint32_t dataSize{0};
    uint32_t horizontalResolution{2400};
    uint32_t verticalResolution{2400};
    uint32_t colors{0};
    uint32_t importantColors{0};
};
#pragma pack(pop)