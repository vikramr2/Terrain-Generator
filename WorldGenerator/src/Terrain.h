#pragma once

#include <vector>
#include "../Perlin_Noise/PerlinNoise.h"
#include "../Perlin_Noise/ppm.h"
#include "ofMain.h"

class Terrain {
   private:
    ppm GenerateNoise(int seed);

   public:
    const static int kterrain_width = 20;
    const static int kterrain_length = 20;
    unsigned int terrain[kterrain_width][kterrain_length];
    Terrain(int seed);
    std::vector<ofBoxPrimitive> InitializeTerrain();
};