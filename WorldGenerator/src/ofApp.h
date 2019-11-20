#pragma once

#include "Terrain.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {
   private:
    float boxSize = 30;
    int posX = -830;
    int posY = -890;
    int posZ = -1020;
    int x = 0;

    ofMaterial material;

    Terrain terrain;
    std::vector<ofBoxPrimitive> terrain_data;

    ofBoxPrimitive box;
    ofEasyCam cam;
    ofLight light;

   public:
    ofApp() : terrain(250) {
        terrain_data = terrain.InitializeTerrain();
    }
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
