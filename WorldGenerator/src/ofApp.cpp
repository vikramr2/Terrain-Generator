#include "ofApp.h"
#include "Terrain.h"

//sets up the initial parameters of the world
void ofApp::setup() {
	//set up lighting
    light.setup();
    light.setPosition(100, 200, 0);

	//Sets up shading, coloring, and framerate
    ofEnableDepthTest();
    material.setDiffuseColor(ofFloatColor::forestGreen);
    ofSetFrameRate(30);
}

//repeats this function each frame
void ofApp::draw() {
	//initialize camera and material
    cam.begin();
    material.begin();

	//shapes the base surface
	y = 0;
    for (int row = 0; row < terrain.kterrain_length - 1; row++) {
        x = 0;
        for (int col = 0; col < terrain.kterrain_width - 1; col++) {
            mesh.addFace(ofPoint(ofGetWidth() * .2 + posX + x,
                                   posY + (terrain.terrain[row][col] * boxSize),
                                   ofGetHeight() * .75 + posZ + y), 
						 ofPoint(ofGetWidth() * .2 + posX + x + boxSize,
                                   posY + (terrain.terrain[row][col + 1] * boxSize),
                                   ofGetHeight() * .75 + posZ + y),
						 ofPoint(ofGetWidth() * .2 + posX + x + boxSize,
								 posY + (terrain.terrain[row + 1][col + 1] * boxSize),
								 ofGetHeight() * .75 + posZ + y + boxSize));
            mesh.addFace(
                ofPoint(ofGetWidth() * .2 + posX + x,
                        posY + (terrain.terrain[row][col] * boxSize),
                        ofGetHeight() * .75 + posZ + y),
                ofPoint(ofGetWidth() * .2 + posX + x + boxSize,
                        posY + (terrain.terrain[row + 1][col + 1] * boxSize),
                        ofGetHeight() * .75 + posZ + y + boxSize),
                ofPoint(ofGetWidth() * .2 + posX + x,
                        posY + (terrain.terrain[row + 1][col] * boxSize),
                        ofGetHeight() * .75 + posZ + y + boxSize));
            x += boxSize;
        }
        y += boxSize;
    }

	//fills the surface with the material
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	//draws the surface
    mesh.draw();

	//resets conditions
    material.end();
    cam.end();
    mesh.clear();
}

void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == OF_KEY_LEFT) {
        cam.move(-10, 0, 0);
    }

    if (key == OF_KEY_RIGHT) {
        cam.move(10, 0, 0);
    }

    if (key == OF_KEY_UP) {
        cam.move(0, 0, -10);
    }

    if (key == OF_KEY_DOWN) {
        cam.move(0, 0, 10);
    }

    if (key == OF_KEY_TAB) {
        cam.move(0, 10, 0);
    }

    if (key == OF_KEY_SHIFT) {
        cam.move(0, -10, 0);
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
