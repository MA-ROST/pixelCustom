#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "ofSystemUtils.h"
#include "ofFileUtils.h"
#include "ofUtils.h"
#include "point.h"

#define BOOL_MATRIX std::vector<std::vector <bool>>

struct ReadPPM {
	Point <int> location_;
	BOOL_MATRIX states_;
};

class IoToPPM {
	
	std::string filename_ = "pixelArt.ppm";
	std::string pType_ = "P1";

	Point <int> pxRes_;

	BOOL_MATRIX cellStates_;
public:
	IoToPPM(std::string filename, std::string pType, int w, int h, const BOOL_MATRIX
	        & cellStates);
	IoToPPM(std::string filename);
	
	void write();
	ReadPPM read();

	void pushCellState(const BOOL_MATRIX& cellStates);
};


