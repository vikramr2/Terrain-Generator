#include "ofApp.h"
#include "Terrain.h"

// sets up the initial parameters of the world
void ofApp::setup() {
    // set up lighting
    light.setup();
    light.setPosition(100, 200, 0);

    // Sets up shading, coloring, and framerate
    ofEnableDepthTest();
    material.setDiffuseColor(ofFloatColor::beige);
    ofSetFrameRate(30);

    // set up skybox
    skybox.loadImages(
        "Assets/Daylight Box_Right.bmp", "Assets/Daylight Box_Left.bmp",
        "Assets/Daylight Box_Top.bmp", "Assets/Daylight Box_Bottom.bmp",
        "Assets/Daylight Box_Front.bmp", "Assets/Daylight_Box_Back.bmp");

    skybox.bind();
    skybox.drawSkybox(800);
    water.set(terrain.kterrain_length * boxSize, sea_level,
              terrain.kterrain_width * boxSize);
}

// repeats this function each frame
void ofApp::draw() {
    // initialize camera and material
    cam.begin();
    material.begin();

    // skybox.drawSkybox(800);

    // shapes the base surface
    y = 0;
    for (int row = 0; row < terrain.kterrain_length - 1; row++) {
        x = 0;
        for (int col = 0; col < terrain.kterrain_width - 1; col++) {
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

    // fills the surface with the material
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // draws the surface
    mesh.draw();

    // resets conditions
    material.end();

    // draw water
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 250, 127);
    water.setPosition(
        ofGetWidth() * .2 + posX + (terrain.kterrain_length * boxSize) / 2,
        posY,
        ofGetHeight() * .75 + posZ + (terrain.kterrain_length * boxSize) / 2);
    water.draw();
    ofDisableAlphaBlending();

    cam.end();
    mesh.clear();

    // skybox.unbind();
    //std::cout << cam.getX() << ", " << cam.getY() << ", " << cam.getZ()
      //        << std::endl;
}

void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == OF_KEY_LEFT) {
        posX += 100;
        //cam.move(-100, 0, 0);
    }

    if (key == OF_KEY_RIGHT) {
        posX -= 100;
        //cam.move(100, 0, 0);
    }

    if (key == OF_KEY_UP) {
        posZ += 100;
        //cam.move(0, 0, -100);
    }

    if (key == OF_KEY_DOWN) {
        posZ -= 100;
        //cam.move(0, 0, 100);
    }

    if (key == OF_KEY_TAB) {
        cam.move(0, 100, 0);
    }

    if (key == OF_KEY_SHIFT) {
        cam.move(0, -100, 0);
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
