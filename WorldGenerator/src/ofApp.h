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
	   int posX = -6130;
	   int posY = -4290;
	   int posZ = -11020;
       int back_boundary = -15820;
       int front_boundary = -2320;
       int left_boundary = -3000;
       int right_boundary = -14000;
       int bottom_boundary = -2000;
	   
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

	   //initialize texture
       ofTexture mTex;
       ofImage tex_img;

	   //water
       ofxMesh waterMesh;
       int waves[Terrain::kterrain_width][Terrain::kterrain_length];
       int sea_level;
   public:
	   //sets the terrain with a random seed
	   ofApp() : terrain(rand() % num_worlds + 1) {}

	   void setSeaLevel();

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
