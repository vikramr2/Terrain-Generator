#pragma once

#include <vector>
#include "../Bitmap/Bitmap.h"
#include "../Perlin_Noise/PerlinNoise.h"
#include "../Perlin_Noise/ppm.h"
#include "ofMain.h"

class Terrain {
   private:
    ppm GenerateNoise(int seed);
    int roughness_coeff = 3;
    int roughness;

   public:
    int terrain_seed;
    const static int hill_index = 10;
    const static int kterrain_width = 150;
    const static int kterrain_length = 150;
    unsigned int terrain[kterrain_width][kterrain_length];
    Terrain(int seed);

    void GenerateTexture(ppm noise);
};