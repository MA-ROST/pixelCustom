#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "point.h"

class IoToPPM {

	std::ofstream outputFile_;
	std::string filename_ = "pixelArt.ppm";
	std::string pType_ = "P1";

	Point <int> pxRes_;

	std::vector<std::vector <bool>> cellStates_;
public:
	IoToPPM(std::string filename, std::string pType, int w, int h, const std::vector<std::vector <bool>>
	        & cellStates);
	void write();

	void pushCellState(const std::vector<std::vector<bool>>& cellStates);
	
};
