//SOURCE: https://stackoverflow.com/questions/45992320/how-to-create-an-image-in-c-with-an-2d-rgb-array

#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

using namespace std;

class Bitmap {
   private:
    int m_width{0};
    int m_height{0};
    unique_ptr<uint8_t[]> m_pixels{nullptr};

   public:
    struct RBG {
        uint8_t r;
        uint8_t b;
        uint8_t g;
    };

    Bitmap(int width, int height)
        : m_width(width),
          m_height(height),
          m_pixels(new uint8_t[width * height * sizeof(RBG)]{}){};

    void setPixel(int x, int y, RBG color) {
        uint8_t *pixel = m_pixels.get();

        pixel = pixel + ((y * sizeof(RBG)) * m_width) + (x * sizeof(RBG));

        // little endian
        pixel[0] = color.b;
        pixel[1] = color.g;
        pixel[2] = color.r;
    }
    void setDimensions(int, int);
    int getSize();
    bool write(string);

    ~Bitmap();
};