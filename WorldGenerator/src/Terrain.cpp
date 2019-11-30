#include "Terrain.h"
#include "../Perlin_Noise/PerlinNoise.h"
#include "../Perlin_Noise/ppm.h"
#include "ofMain.h"

/**
* @param seed the seed to generate this random terrain from
* @return a ppm height map
* 
* @note this code was referenced from:
* https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
*/
ppm Terrain::GenerateNoise(int seed) {
    // Define the size of the image
    unsigned int width = kterrain_width, height = kterrain_length;

    // Create an empty PPM image
    ppm image(width, height);

    // Create a PerlinNoise object with a random permutation vector generated
    // with seed
    PerlinNoise pn(seed);

    unsigned int kk = 0;
    // Visit every pixel of the image and assign a color generated with Perlin
    // noise
    for (unsigned int i = 0; i < height; ++i) {     // y
        for (unsigned int j = 0; j < width; ++j) {  // x
            double x = (double)j / ((double)width);
            double y = (double)i / ((double)height);

            // Typical Perlin noise
            double n = pn.noise(10 * x, 10 * y, 0.8);

            // Wood like structure
            //n = 20 * pn.noise(x, y, 0.8);
            //n = n - floor(n);

            // Map the values to the [0, 255] interval, for simplicity we use
            // tones of grey
            image.r[kk] = floor(255 * n);
            image.g[kk] = floor(255 * n);
            image.b[kk] = floor(255 * n);
            kk++;
        }
    }

    return image;
}

/**
* Constructs the terrain map from a seed
*/
Terrain::Terrain(int seed) {
	//generate perlin noise
    ppm perlin_noise = GenerateNoise(seed);

	//structure into 2D array
    for (int i = 0; i < perlin_noise.r.size(); i++) {
        terrain[i / kterrain_width][i % kterrain_length] = perlin_noise.r[i]/10;
    }
}
