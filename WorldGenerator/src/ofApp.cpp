#include "ofApp.h"

ofBoxPrimitive box;
float boxSize = 30;
int posX = 0;
int posZ = 0;

void ofApp::setup() {
    box.set(boxSize);
    // or
    // box.set( boxHeight, boxWidth, boxDepth );
}

void ofApp::draw() {
    box.setPosition(ofGetWidth() * .2 + posX, ofGetHeight() * .75, posZ);

    // get all the faces from the icoSphere, handy when you want to copy
    // individual vertices or tweak them a little ;)
    vector<ofMeshFace> triangles = box.getMesh().getUniqueFaces();

    // now draw
    ofSetColor(0xffffff);
    box.draw();
    ofSetLineWidth(0.05);
    ofSetColor(0x000000);
    box.drawWireframe();
}

void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == OF_KEY_LEFT) {
        posX++;
    }

	if (key == OF_KEY_UP) {
        posZ++;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

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
