#pragma once

#include "../addons/ofxMesh/src/ofxMesh.h"
#include "Terrain.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {
   private:
    // initialize position and size variables
    float boxSize = 100;
    int back_boundary = 780 - (boxSize * Terrain::kterrain_width);
    int front_boundary = -1000;
    int left_boundary = -200;
    int right_boundary = 1000 - (boxSize * Terrain::kterrain_length);
    int bottom_boundary = -2000;
    int posX = (left_boundary + right_boundary)/2;
    int posY = -2500;
    int posZ = (front_boundary + back_boundary) / 2;

    int x = 0;
    int y = 0;
    int z = 0;

    // number of worlds possible
    int num_worlds = 1000;

    // initialize drawing variables
    ofxMesh mesh;
    ofMaterial material;

    // initialize terrain map
    Terrain terrain;

    // initialize camera and light
    ofEasyCam cam;
    ofLight light;

    // initialize texture
    ofTexture mTex;
    ofImage tex_img;

    // water
    ofxMesh water_mesh;
    ofMaterial water_material;
    int waves[Terrain::kterrain_width][Terrain::kterrain_length];
    int wave_rates[Terrain::kterrain_width][Terrain::kterrain_length];
    int sea_level;
    void setSeaLevel();
    void fillWater();
    void initRates();
    void wave();
   public:
    // sets the terrain with a random seed
    ofApp() : terrain(rand() % num_worlds + 1) {}

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
