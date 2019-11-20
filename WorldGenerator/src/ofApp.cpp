#include "ofApp.h"
#include "Terrain.h"


float boxSize = 30;
int posX = 0;
int posY = 0;
int posZ = 0;
int x = 0;

Terrain terrain(250);
std::vector<ofBoxPrimitive> terrain_data = terrain.InitializeTerrain();

ofBoxPrimitive box;
//[terrain.kterrain_width];

void ofApp::setup() {
    
    for (ofBoxPrimitive& block : terrain_data) {
        block.set(boxSize);
    }
    /*for (int i = 0; i < terrain.kterrain_width; i++) {
        box[i].set(boxSize);
	}*/
    // or
    // box.set( boxHeight, boxWidth, boxDepth );
}

void ofApp::draw() {
    
    
    
    int index = 0;
    int z = 0;
    
    for (int row = 0; row < terrain.kterrain_length; row++) {
        
        int x = 0;
        for (int col = 0; col < terrain.kterrain_width; col++) {
            
            int y = 0;
            for (int dep = 0; dep < terrain.terrain[row][col]; dep++) {
				
                ofBoxPrimitive& box = terrain_data.at(index);
                box.setPosition(ofGetWidth() * .2 + posX + x,
                                                   ofGetHeight() * .75 + posY + y,
                                                   posZ + z);

                // get all the faces from the icoSphere, handy when you want to
                // copy individual vertices or tweak them a little ;)
                vector<ofMeshFace> triangles = box.getMesh().getUniqueFaces();

				/*box.setSideColor(ofBoxPrimitive::BoxSides::SIDES_TOTAL,
                                 ofColor::sandyBrown);
                box.setSideColor(ofBoxPrimitive::BoxSides::SIDE_FRONT,
                                    ofColor::forestGreen);
                                //box.getMesh().*/
                // now draw
                ofSetColor(0xffffff);
                box.draw();
                ofSetLineWidth(.5);
                ofSetColor(0x000000);
                box.drawWireframe();

				y -= boxSize;
				
                index++;
            }

			x += boxSize;
		}

		z += boxSize;
    }
    
	//box.setPosition(ofGetWidth() * .2 + posX, ofGetHeight() * .75,
 //               posZ);
 //   vector<ofMeshFace> triangles = box.getMesh().getUniqueFaces();
	//// now draw
 //   ofSetColor(0xffffff);
 //   box.draw();
 //   ofSetLineWidth(0.05);
 //   ofSetColor(0x000000);
 //   box.drawWireframe();
    /*for (ofBoxPrimitive& block: box) {
            block.setPosition(ofGetWidth() * .2 + posX + x, ofGetHeight() * .75,
            posZ);
			ofSetColor(0xffffff);
			block.draw();
			ofSetLineWidth(0.05);
			ofSetColor(0x000000);
			block.drawWireframe();
			x += boxSize;
	}
    x = 0;*/
}

void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == OF_KEY_LEFT) {
        posX+=10;
    }

	if (key == OF_KEY_RIGHT) {
        posX -= 10;
    }

    if (key == OF_KEY_UP) {
        posZ+=10;
    }

	if (key == OF_KEY_DOWN) {
        posZ-=100;
    }

	if (key == OF_KEY_TAB) {
        posY -= 10;
    }

	if (key == OF_KEY_SHIFT) {
        posY += 10;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
