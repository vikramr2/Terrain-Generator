#define CATCH_CONFIG_MAIN

#include "catch.hpp"

//setup works
TEST_CASE("tests even work") { REQUIRE(1 == 1); }

//scratchwork for calculating slopes
TEST_CASE("dx/dz algorithm is valid") { 
	int test_grid[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int dx = abs(test_grid[1][1] - test_grid[1][2]);
    int dz = abs(test_grid[1][1] - test_grid[2][1]);
    REQUIRE(std::max(dx, dz) == 3);
}

//scratchwork for getting fade colors
TEST_CASE("Vector interpolation algo is valid") { 
	int color1[3] = { 0, 0, 0 };
    int color2[3] = {255, 255, 255};
    int interpolated_color[3];
    int fade_percent = .75;
    interpolated_color[0] = color1[0] + int((color2[0] - color1[0]) * fade_percent);
    interpolated_color[1] = color1[1] + int((color2[1] - color1[1]) * fade_percent);
    interpolated_color[2] = color1[2] + int((color2[2] - color1[2]) * fade_percent);

	REQUIRE(interpolated_color[0] == int(fade_percent * 255));
}