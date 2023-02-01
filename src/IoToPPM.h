#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "point.h"

class IoToPPM {

class IoToPPM {
	
	std::string filename_ = "pixelArt.ppm";
	std::string pType_ = "P1";

	Point <int> pxRes_;

	std::vector<std::vector <bool>> cellStates_;
public:
	IoToPPM(std::string filename, std::string pType, int w, int h, const std::vector<std::vector <bool>>
	        & cellStates);
	IoToPPM(std::string filename);
	void write();
	void read();

	void pushCellState(const std::vector<std::vector<bool>>& cellStates);

	friend std::istream &operator>>(std::istream &in, bool &money) {
		int a, b;
		char c;

		// Parses input in the form: $m.n (where m and n are integers)
		in >> a >> c;

		money = a;
		std::cout << "hit\n";
		std::cout << a << "\n";

		return in;
	}
	
};
