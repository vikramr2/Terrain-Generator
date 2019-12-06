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

	void setDimensions(int w, int h) {
        m_width = w;
        m_height = h;
	}
    
	int getSize() { return m_width * m_height * sizeof(RBG); }

    bool write(string filename) {
		BitmapFileHeader fileHeader;
        BitmapInfoHeader infoHeader;

        fileHeader.fileSize =
            sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + getSize();
        fileHeader.dataOffset =
            sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

        infoHeader.width = m_width;
        infoHeader.height = m_height;

        ofstream file;
        file.open(filename, ios::out | ios::binary);

        if (!file) {
            return false;
        }

        file.write(reinterpret_cast<char *>(&fileHeader),
                    sizeof(fileHeader));
        file.write(reinterpret_cast<char *>(&infoHeader),
                    sizeof(infoHeader));
        file.write(reinterpret_cast<char *>(m_pixels.get()), getSize());

        file.close();

        return true;
    }

    Bitmap::~Bitmap() { cout << "bitmap destroyed" << endl; }
};