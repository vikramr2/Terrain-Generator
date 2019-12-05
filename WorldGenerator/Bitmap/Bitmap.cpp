#include "Bitmap.h"
#include "stdafx.h"

using namespace std;


void Bitmap::setDimensions(int w, int h) {
    m_width = w;
    m_height = h;
}

int Bitmap::getSize() { return m_width * m_height * sizeof(RBG); }

bool Bitmap::write(string filename) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.fileSize =
        sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + getSize();
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    infoHeader.width = m_width;
    infoHeader.height = m_height;

    ofstream file;
    file.open(filename, ios::out | ios::binary);

    if (!file) {
        return false;
    }

    file.write(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<char *>(m_pixels.get()), getSize());

    file.close();

    return true;
}

Bitmap::~Bitmap() { cout << "bitmap destroyed" << endl; }