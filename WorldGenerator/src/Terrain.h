#pragma once

#include <vector>
#include "../Perlin_Noise/PerlinNoise.h"
#include "../Perlin_Noise/ppm.h"
#include "ofMain.h"

class Terrain {
   private:
    const static int kterrain_width = 600;
    const static int kterrain_length = 600;
    unsigned int terrain[kterrain_width][kterrain_length];
    ppm GenerateNoise(int seed);

   public:
    std::vector<std::vector<int>> GetTerrain();
    Terrain(int seed);
    std::vector<ofBoxPrimitive> InitializeTerrain();
};