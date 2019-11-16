#pragma once

#include <vector>

class Terrain {
   private:
    std::vector<std::vector<int>> terrain;

   public:
    std::vector<std::vector<int>> GetTerrain();
    void FillTerrain();
};