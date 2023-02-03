#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetBackgroundColor(ofColor::white);
    manager.setup();
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

void ofApp::keyPressed(const int key)
{
    if (key == 's') manager.writeToFile(); 
    if (key == 'r') manager.readFromFile(); 
}
