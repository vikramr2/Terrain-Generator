#pragma once

#include <vector>
#include "../Perlin_Noise/PerlinNoise.h"
#include "../Perlin_Noise/ppm.h"
#include "ofMain.h"

class Terrain {
   private:
    ppm GenerateNoise(int seed);
    int roughness_coeff = 5;
    int roughness;

   public:
    int terrain_seed;
    int hill_index = (rand() % 10) + 5;
    const static int kterrain_width = 100;
    const static int kterrain_length = 100;
    unsigned int terrain[kterrain_width][kterrain_length];
    Terrain(int seed);

    void GenerateTexture(ppm noise);
};