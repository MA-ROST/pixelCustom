#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetBackgroundColor(ofColor::white);
    manager.setupCells();

    manager.writeToFile();
}

//--------------------------------------------------------------
void ofApp::draw() {
    manager.draw();
}

void ofApp::mouseDragged(int x, int y, int button)
{
    manager.mouseDragged (x,y);
    manager.mouseDragged (ofGetPreviousMouseX(),ofGetPreviousMouseY());
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    manager.mousePressed (x,y);
    manager.mousePressed (ofGetPreviousMouseX(),ofGetPreviousMouseY());
}

void ofApp::keyPressed(int key)
{
    if (key == 's') {
        manager.writeToFile();
    }
}
