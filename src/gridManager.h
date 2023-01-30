#pragma once
#include <array>
#include <vector>

#include "cell.h"

class GridManager {
	std::vector<std::vector<Cell>> cells_;
	int updateInterval_ = 15;
	bool wasClickTrue_ = false;
public:
	void setupCells();

	void draw();
	void drawCells();
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

	void push();
	void pop();
};
