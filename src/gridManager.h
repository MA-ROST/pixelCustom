#pragma once
#include <array>
#include <vector>

#include "IoToPPM.h"
#include "cell.h"

class GridManager {
	std::vector<std::vector<Cell>> cells_;
	int updateInterval_ = 15;
	bool wasClickTrue_ = false;
public:
	void setup();
	static void determineGridSize();
	static void determineWindowRes();
	void setupCells();

	void draw();
	void updateCells();
	bool rowInBound(int row);
	bool colInBound(int col);
	bool cellInBound(int row, int col);
	void toggleCell(Point<int> mouseCoord);

	void mouseDragged(int x, int y);
	void mousePressed(int x, int y);
	Point<int> getClicked(int x, int y);

	void writeToFile();
	void readFromFile();

	void readToGrid(const ReadPPM& ppm);

	void push();
	void pop();
};
