#include "ofApp.h"
#include "Terrain.h"

// sets up the initial parameters of the world
void ofApp::setup() {
    // set up background
    // ofBackground(ofFloatColor::lightSkyBlue);

    // orient the camera
    cam.tilt(-45);

    // set up lighting
    light.setup();
    light.setPosition(100, 200, 0);

    // Sets up shading and framerate
    ofEnableDepthTest();

    // set up texturing
    ofDisableArbTex();
    ofEnableNormalizedTexCoords();
    ofLoadImage(mTex, "Assets/texture.ppm");
}

// repeats this function each frame
void ofApp::draw() {
    ofBackgroundGradient(ofFloatColor::lightSkyBlue, ofFloatColor::orangeRed,
                         OF_GRADIENT_LINEAR);
    // initialize camera and material
    cam.begin();
    material.begin();
    mTex.bind();

    // shapes the base surface
    y = 0;
    for (int row = 0; row < terrain.kterrain_length - 1; row++) {
        x = 0;
        for (int col = 0; col < terrain.kterrain_width - 1; col++) {
            // create faces
            mesh.addFace(
                ofPoint(ofGetWidth() * .2 + posX + x,
                        posY + (terrain.terrain[row][col] * boxSize),
                        ofGetHeight() * .75 + posZ + y),
                ofPoint(ofGetWidth() * .2 + posX + x + boxSize,
                        posY + (terrain.terrain[row][col + 1] * boxSize),
                        ofGetHeight() * .75 + posZ + y),
                ofPoint(ofGetWidth() * .2 + posX + x + boxSize,
                        posY + (terrain.terrain[row + 1][col + 1] * boxSize),
                        ofGetHeight() * .75 + posZ + y + boxSize));

            // mapping coordinates to texture
            mesh.addTexCoord(ofVec2f(col / (150.0), row / (150.0)));
            mesh.addTexCoord(ofVec2f((col + 1) / (150.0), row / (150.0)));
            mesh.addTexCoord(ofVec2f((col + 1) / (150.0), (row + 1) / (150.0)));

            // repeat for adjacent triangles
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

            mesh.addTexCoord(ofVec2f(col / (150.0), row / (150.0)));
            mesh.addTexCoord(ofVec2f((col + 1) / (150.0), (row + 1) / (150.0)));
            mesh.addTexCoord(ofVec2f((col + 1) / (150.0), row / (150.0)));
            x += boxSize;
        }
        y += boxSize;
    }

    // fills the surface with the material and texture
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // draws the surface
    mesh.draw();

    // resets surface conditions
    material.end();
    mTex.unbind();

    // reset remaining conditions
    cam.end();
    mesh.clear();
}

void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == OF_KEY_LEFT) {
        if (posX < left_boundary) {
            posX += 100;
        }
    }

    if (key == OF_KEY_RIGHT) {
        if (posX > right_boundary) {
            posX -= 100;
        }
    }

    if (key == OF_KEY_UP) {
        if (posZ < front_boundary) {
            posZ += 100;
        }
    }

    if (key == OF_KEY_DOWN) {
        if (posZ > back_boundary) {
            posZ -= 100;
        }
    }

    if (key == ' ') {
        posY -= 100;
    }

    if (key == OF_KEY_SHIFT) {
        if (posY < bottom_boundary) {
            posY += 100;
        }
    }
}

void ofApp::setSeaLevel() {
    double percentage_range = 0.75;
    int min_height;
    int max_height;
    for (int row = 0; row < terrain.kterrain_length; row++) {
        for (int col = 0; col < terrain.kterrain_width; col++) {
            if (terrain.terrain[row][col] > max_height) {
                max_height = terrain.terrain[row][col];
            }

            if (terrain.terrain[row][col] < min_height) {
                min_height = terrain.terrain[row][col];
            }
        }
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
