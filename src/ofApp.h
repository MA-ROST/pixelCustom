#pragma once

#include "gridManager.h"
#include "ofMain.h"

/**
 * initialize at a specific size
 */
class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);

	GridManager manager;
};
