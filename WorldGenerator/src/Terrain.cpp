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
            // n = 20 * pn.noise(x, y, 0.8);
            // n = n - floor(n);

            roughness = (rand() % (2 * roughness_coeff)) - roughness_coeff;

            // Map the values to the [0, 255] interval, for simplicity we use
            // tones of grey
            image.r[kk] = floor(255 * n) + roughness;
            image.g[kk] = floor(255 * n) + roughness;
            image.b[kk] = floor(255 * n) + roughness;
            kk++;
        }
    }

    return image;
}

/**
 * Constructs the terrain map from a seed
 */
Terrain::Terrain(int seed) {
    // set seed
    terrain_seed = seed;

    // generate perlin noise
    ppm perlin_noise = GenerateNoise(seed);

    // structure into 2D array
    for (int i = 0; i < perlin_noise.r.size(); i++) {
        terrain[i / kterrain_width][i % kterrain_length] =
            perlin_noise.r[i] / hill_index;
    }

    // generate texture
    GenerateTexture(perlin_noise);
}

void Terrain::GenerateTexture(ppm noise) {
    // landscape colors
    int grass[3] = {96, 128, 56};
    int mountain[3] = {151, 124, 83};
    int snow[3] = {255, 255, 255};
    int sand[3] = {194, 178, 128};
    int mountaintop[3] = {108, 96, 83};

    // thresholds
    int slope_threshold = 5;
    int sea_level_threshold = 6;
    int mountain_cap_threshold = 175;
    int below_cap_threshold = 20;

    // slope transform
    int slope_x;
    int slope_z;
    int max_slope;
    for (int kk = 0; kk < noise.r.size(); kk++) {
        if (kk % kterrain_length != 0) {
            slope_x = abs(noise.r[kk] - noise.r[kk - 1])/hill_index;
        } else {
            slope_x = abs(noise.r[kk] - noise.r[kk + 1])/hill_index;
        }

        if (kk / kterrain_width != 0) {
            slope_z = abs(noise.r[kk] - noise.r[kk - kterrain_width])/hill_index;
        } else {
            slope_z = abs(noise.r[kk] - noise.r[kk + kterrain_width])/hill_index;
        }

        max_slope = std::max(slope_x, slope_z);

        if (max_slope > slope_threshold) {
            max_slope = slope_threshold;
        }
        noise.r[kk] = grass[0] + int((mountain[0] - grass[0]) * max_slope/double(slope_threshold));
        noise.g[kk] = grass[1] + int((mountain[1] - grass[1]) * max_slope/double(slope_threshold));
        noise.b[kk] = grass[2] + int((mountain[2] - grass[2]) * max_slope/double(slope_threshold));
    }

	//mountaintop transform
    double height_ratio;
    for (int kk = 0; kk < noise.r.size(); kk++) {
        if (terrain[kk / kterrain_length][kk % kterrain_length] * hill_index >= mountain_cap_threshold - below_cap_threshold &&
            terrain[kk / kterrain_length][kk % kterrain_length] * hill_index < mountain_cap_threshold) {
            height_ratio = (mountain_cap_threshold - terrain[kk / kterrain_length][kk % kterrain_length] * hill_index) / double(below_cap_threshold);
            
			if (height_ratio > 1.0) {
                height_ratio = 1.0;
            }
			
			noise.r[kk] = noise.r[kk] + int((mountaintop[0] - noise.r[kk]) * height_ratio);
            noise.g[kk] = noise.r[kk] + int((mountaintop[1] - noise.g[kk]) * height_ratio);
            noise.b[kk] = noise.b[kk] + int((mountaintop[2] - noise.r[kk]) * height_ratio);
		}
    }

	//snow transform
    for (int kk = 0; kk < noise.r.size(); kk++) {
        if (terrain[kk / kterrain_length][kk % kterrain_length] * hill_index >= mountain_cap_threshold) {
            height_ratio = (255 - terrain[kk / kterrain_length][kk % kterrain_length] * hill_index) / double(255 - mountain_cap_threshold);
            
            noise.r[kk] = noise.r[kk] + int((snow[0] - noise.r[kk]) * height_ratio);
            noise.g[kk] = noise.g[kk] + int((snow[0] - noise.g[kk]) * height_ratio);
            noise.b[kk] = noise.b[kk] + int((snow[0] - noise.b[kk]) * height_ratio);

			if (noise.r[kk] > 255) {
                noise.r[kk] = 255;
			}

			if (noise.g[kk] > 255) {
                noise.g[kk] = 255;
            }

			if (noise.b[kk] > 255) {
                noise.b[kk] = 255;
            }
        }
    }

	

    noise.write("texture.ppm");
}
