#pragma once

#include "../addons/ofxMeshUtils/src/ofxMeshUtils.h"
#include "Terrain.h"
#include "ofMain.h"
#include "../addons/ofxMesh/src/ofxMesh.h"
#include "../addons/ofxCubemap/src/ofxCubemap.h"


class ofApp : public ofBaseApp {
   private:
	   //initialize position and size variables
	   float boxSize = 100;
	   int posX = -1530;
	   int posY = -2590;
	   int posZ = -1020;
	   
	   int x = 0;
	   int y = 0;
	   int z = 0;
	   
	   //number of worlds possible
       int num_worlds = 1000;

	   //initialize drawing variables
	   ofxMesh mesh;
	   ofMaterial material;
	   
	   //initialize terrain map
	   Terrain terrain;
	   
	   //initialize camera and light
	   ofEasyCam cam;
	   ofLight light;

	   //initialize water
	   ofBoxPrimitive water;

	   //initialize texture
       ofTexture mTex;
	   ofImage tex_img;

       ofxCubeMap cubemap;
	   
   public:
	   //sets the terrain with a random seed
	   ofApp() : terrain(rand() % num_worlds + 1) {}

	   int sea_level = boxSize * (rand() % (256 / terrain.hill_index));

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
