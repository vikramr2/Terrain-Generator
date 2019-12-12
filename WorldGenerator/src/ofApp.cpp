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

    // set up water
    water_material.setShininess(100);
    water_material.setDiffuseColor(ofFloatColor::aqua);
    setSeaLevel();
    fillWater();
    initRates();
}

// repeats this function each frame
void ofApp::draw() {
	//set up background
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
            mesh.addTexCoord(ofVec2f(col / double(terrain.kterrain_width), row / double(terrain.kterrain_length)));
            mesh.addTexCoord(ofVec2f((col + 1) / double(terrain.kterrain_width), row / double(terrain.kterrain_length)));
            mesh.addTexCoord(ofVec2f((col + 1) / double(terrain.kterrain_width), (row + 1) / double(terrain.kterrain_length)));

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

            mesh.addTexCoord(ofVec2f(col / double(terrain.kterrain_width), row / double(terrain.kterrain_length)));
            mesh.addTexCoord(ofVec2f((col + 1) / double(terrain.kterrain_width), (row + 1) / double(terrain.kterrain_length)));
            mesh.addTexCoord(ofVec2f((col + 1) / double(terrain.kterrain_width), row / double(terrain.kterrain_length)));

            // create faces
            water_mesh.addFace(
                ofPoint(ofGetWidth() * .2 + posX + x, posY + waves[row][col],
                        ofGetHeight() * .75 + posZ + y),
                ofPoint(ofGetWidth() * .2 + posX + x + boxSize,
                        posY + waves[row][col + 1],
                        ofGetHeight() * .75 + posZ + y),
                ofPoint(ofGetWidth() * .2 + posX + x + boxSize,
                        posY + waves[row + 1][col + 1],
                        ofGetHeight() * .75 + posZ + y + boxSize));

            // repeat for adjacent triangles
            water_mesh.addFace(
                ofPoint(ofGetWidth() * .2 + posX + x, posY + waves[row][col],
                        ofGetHeight() * .75 + posZ + y),
                ofPoint(ofGetWidth() * .2 + posX + x + boxSize,
                        posY + waves[row + 1][col + 1],
                        ofGetHeight() * .75 + posZ + y + boxSize),
                ofPoint(ofGetWidth() * .2 + posX + x,
                        posY + waves[row + 1][col],
                        ofGetHeight() * .75 + posZ + y + boxSize));
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

	// water
    water_material.begin();
    water_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    water_mesh.draw();
    water_material.end();
    wave();

    // reset remaining conditions
    cam.end();
    water_mesh.clear();
    mesh.clear();

	//set boundaries
	if (posX > left_boundary) {
        posX = left_boundary;
	}
    if (posX < right_boundary) {
        posX = right_boundary;    
	}
    if (posZ > front_boundary) {
        posZ = front_boundary;
	}
    if (posZ < back_boundary) {
        posZ = back_boundary;
	}
}

void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//magnitudinal speed of motion
    int speed = 100;

	/*look at - unit vector of pointing direction of the camera*/

	//left/right - increment in perpendicular (negative reciprocal of look at)
    if (key == 'a') {
        posX -= speed * cam.getLookAtDir().z;
        posZ += speed * cam.getLookAtDir().x;
    }
    if (key == 'd') {
        posX += speed * cam.getLookAtDir().z;
        posZ -= speed * cam.getLookAtDir().x;
    }

	//forward/backward - increment in direction of look at
    if (key == 'w') {
	    posZ -= speed * cam.getLookAtDir().z;
        posX -= speed * cam.getLookAtDir().x;
    }
    if (key == 's') {
        posZ += speed * cam.getLookAtDir().z;
        posX += speed * cam.getLookAtDir().x;
    }

	//up/down - just in/decrement y by speed
    if (key == ' ') {
        posY -= speed;
    }
    if (key == OF_KEY_SHIFT) {
        if (posY < bottom_boundary) {
            posY += speed;
        }
    }
}

/**
 * sets the sea level
 */
void ofApp::setSeaLevel() {
    // set up ranges
    double percentage_range = 0.6;
    int min_height = 1000;
    int max_height = 0;
    int height_range;

    // calculate mins and maxs
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

    // compute the range
    height_range = int(percentage_range * (max_height - min_height));

    // set sea level
    sea_level = (rand() % height_range + min_height) * boxSize;
}

/**
 * sets the mesh of water
 */
void ofApp::fillWater() {
    int wave_range = 20;
    for (int row = 0; row < terrain.kterrain_width; row++) {
        for (int col = 0; col < terrain.kterrain_length; col++) {
            waves[row][col] = (rand() % wave_range) + sea_level;
        }
    }
}

/**
* initializes flow rates of the water
*/
void ofApp::initRates() {
	//set all rate scalars to be 1
    for (int row = 0; row < terrain.kterrain_width; row++) {
        for (int col = 0; col < terrain.kterrain_length; col++) {
            wave_rates[row][col] = 1;
        }
    }
}

/**
* animates the water
*/
void ofApp::wave() {
	//tide = wave speed, amplitude = wave height
    int tide = 5;
    int amplitude = 30;

	//moves each water particle up and down at this speed and amplitude
    for (int row = 0; row < terrain.kterrain_width; row++) {
        for (int col = 0; col < terrain.kterrain_length; col++) {
            if (waves[row][col] - sea_level > amplitude) {
                wave_rates[row][col] = -1;
            }

            if (waves[row][col] - sea_level < 0) {
                wave_rates[row][col] = 1;
            }

            waves[row][col] += wave_rates[row][col] * tide;
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
