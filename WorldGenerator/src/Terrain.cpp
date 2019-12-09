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
        terrain[i / kterrain_width][i % kterrain_length] = perlin_noise.r[i] / hill_index;
    }

    // generate texture
    GenerateTexture(perlin_noise);
}

/**
* Generates a texture image to cover the generated surface
* 
* @param noise the original black and white perlin noise to color
*/
void Terrain::GenerateTexture(ppm noise) {
    // landscape colors
    int grass[3] = {96, 128, 56};
    int mountain[3] = {151, 124, 83};
    int snow[3] = {255, 255, 255};
    int mountaintop[3] = {108, 96, 83};

    // thresholds
    int slope_threshold = 5;
    int sea_level_threshold = 6;
    int mountain_cap_threshold = 175;
    int below_cap_threshold = 20;

    // slope transform
    // partials in the x and z direction
    int dx; 
    int dz;
    int max_slope;
    for (int kk = 0; kk < noise.r.size(); kk++) {
		//compute dx and dz by taking neighboring points in that direction and getting the height difference
        if (kk % kterrain_length != 0) {
            dx = abs(noise.r[kk] - noise.r[kk - 1])/hill_index;
        } else {
            dx = abs(noise.r[kk] - noise.r[kk + 1])/hill_index;
        }

        if (kk / kterrain_width != 0) {
            dz = abs(noise.r[kk] - noise.r[kk - kterrain_width])/hill_index;
        } else {
            dz = abs(noise.r[kk] - noise.r[kk + kterrain_width])/hill_index;
        }

		//use whichever slope is bigger and cap at the maximum threshold
        max_slope = std::max(dx, dz);
        if (max_slope > slope_threshold) {
            max_slope = slope_threshold;
        }

		//fade colors based on this maximum slope
        noise.r[kk] = grass[0] + int((mountain[0] - grass[0]) * max_slope/double(slope_threshold));
        noise.g[kk] = grass[1] + int((mountain[1] - grass[1]) * max_slope/double(slope_threshold));
        noise.b[kk] = grass[2] + int((mountain[2] - grass[2]) * max_slope/double(slope_threshold));
    }

	//mountaintop transform
    double height_ratio;
    for (int kk = 0; kk < noise.r.size(); kk++) {
		//check if height is in range to be a mountaintop color
        if (terrain[kk / kterrain_length][kk % kterrain_length] * hill_index >= mountain_cap_threshold - below_cap_threshold &&
            terrain[kk / kterrain_length][kk % kterrain_length] * hill_index < mountain_cap_threshold) {
			//compute how high as a ratio this height is in that range
            height_ratio = (mountain_cap_threshold - terrain[kk / kterrain_length][kk % kterrain_length] * hill_index) 
				/ double(below_cap_threshold);
            
			//cap this ratio at 1.0
			if (height_ratio > 1.0) {
                height_ratio = 1.0;
            }
			
			//fade colors based on this ratio
			noise.r[kk] = noise.r[kk] + int((mountaintop[0] - noise.r[kk]) * height_ratio);
            noise.g[kk] = noise.r[kk] + int((mountaintop[1] - noise.g[kk]) * height_ratio);
            noise.b[kk] = noise.b[kk] + int((mountaintop[2] - noise.r[kk]) * height_ratio);
		}
    }

	//snow transform
    for (int kk = 0; kk < noise.r.size(); kk++) {
		//check if this height is in the snow region
        if (terrain[kk / kterrain_length][kk % kterrain_length] * hill_index >= mountain_cap_threshold) {
			//check how far in this region this height is
            height_ratio = (snow[0] - terrain[kk / kterrain_length][kk % kterrain_length] * hill_index) 
				/ double(snow[0] - mountain_cap_threshold);
            
			//cap this ratio at 1.0
            if (height_ratio > 1.0) {
                height_ratio = 1.0;
			}

			//fade colors to white based on this ratio
            noise.r[kk] = noise.r[kk] + int((snow[0] - noise.r[kk]) * height_ratio);
            noise.g[kk] = noise.g[kk] + int((snow[0] - noise.g[kk]) * height_ratio);
            noise.b[kk] = noise.b[kk] + int((snow[0] - noise.b[kk]) * height_ratio);
        }
    }

	//write this into a texture image stored in Assets
    noise.write("data/Assets/texture.ppm");
}
