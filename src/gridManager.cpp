#include "gridManager.h"


void GridManager::setup()
{
	determineGridSize();
	determineWindowRes();
	setupCells();
}

void GridManager::determineGridSize()
{
	std::cout << "How many Rows?: ";
	std::cin >> Cell::gridSize_.x; // assumes perfect user

	std::cout << "How many Columns?: ";
	std::cin >> Cell::gridSize_.y; // assumes perfect user
}

void GridManager::determineWindowRes()
{
	constexpr double resizeFactor = 0.75;

	const int cellX = ofGetScreenWidth() * resizeFactor / static_cast<double>(Cell::gridSize_.x);
	const int cellY = ofGetScreenHeight() * resizeFactor / static_cast<double>(Cell::gridSize_.y);

	Cell::cellSize_ = cellX > cellY ? cellY : cellX;

	const int resX = Cell::gridSize_.x * Cell::cellSize_;
	const int resY = Cell::gridSize_.y * Cell::cellSize_;

	ofSetWindowShape (resX, resY);
}

void GridManager::setupCells()
{
	for (int x = 0; x < Cell::gridSize_.x; ++x) {
		std::vector<Cell> tempCellArray;
		for (int y = 0; y < Cell::gridSize_.y; ++y) {
			Cell tempCell;
			tempCell.setupPixel(x, y);
			tempCellArray.emplace_back(tempCell);
		}
		cells_.push_back(tempCellArray);
	}
}

void GridManager::draw()
{
	for (int x = 0; x < Cell::gridSize_.x; ++x) {
		for (int y = 0; y < Cell::gridSize_.y; ++y) {
			cells_[x][y].setupPixel(x, y);
		}
	}

	if (ofGetFrameNum() % updateInterval_ == 0) {
		updateCells();
	}
}

void GridManager::updateCells()
{
	for (auto& cellRow : cells_) {
		for (auto& cell : cellRow) {
			if (cell.markedForUpdate_) {
				cell.updateCell();
			}
		}
	}
}

bool GridManager::rowInBound(const int row)
{
	if (row < 0) return false;					// Before first row
	if (row >= Cell::gridSize_.x) return false;	// After last row
	return true; // Valid row
}

bool GridManager::colInBound(const int col)
{
	if (col < 0) return false;					// Before first column
	if (col >= Cell::gridSize_.y) return false;   // After last column
	return true;                                // Valid row
}

bool GridManager::cellInBound(const int row, const int col)
{
	if (rowInBound(row) && colInBound(col)) return true;
	return false;
}

void GridManager::toggleCell(Point<int> mouseCoord)
{
	cells_[mouseCoord.x][mouseCoord.y].isLive_ = !wasClickTrue_ ? true : false;
}

void GridManager::mouseDragged(int x, int y)
{
	const Point<int> mouseCoord = getClicked(x, y);
	
	if (cellInBound(mouseCoord.x, mouseCoord.y))
	{
		toggleCell(mouseCoord);
	}
}

void GridManager::mousePressed(const int x, const int y)
{
	const Point<int> mouseCoord = getClicked(x, y);
	if (cellInBound(mouseCoord.x, mouseCoord.y))
	{
		// Check if the clicked cell was true or not, and reflect it onto wasClickTrue_
		wasClickTrue_ = cells_[mouseCoord.x][mouseCoord.y].isLive_;
	}
}

Point<int> GridManager::getClicked(const int x, const int y)
{
	for (int a = 0; a < Cell::gridSize_.x; ++a) {
		for (int b = 0; b < Cell::gridSize_.y; ++b) {
			if (cells_[a][b].wasClickInside(x, y)) {
				return { a,b };
			}
		}
	}
}

void GridManager::writeToFile()
{
	BOOL_MATRIX cellStates;

	for (int x = 0; x < Cell::gridSize_.x; ++x) {
		std::vector<bool> tempCellArray;
		tempCellArray.reserve (Cell::gridSize_.y);
		for (int y = 0; y < Cell::gridSize_.y; ++y) {
			tempCellArray.emplace_back(cells_[x][y].isLive_);
		}
		cellStates.push_back(tempCellArray);
	}

	IoToPPM ppm {
		"data\\pixelArt.ppm", "P1",
		Cell::gridSize_.x, Cell::gridSize_.y,
		cellStates
	};

	ppm.write();
}

void GridManager::readFromFile()
{
	IoToPPM ppm {"data\\pixelArt.ppm"};

	readToGrid (ppm.read());
}

void GridManager::readToGrid(const ReadPPM& ppm)
{
	cells_.clear();

	Cell::gridSize_ = ppm.location_;

	// X and Y must be flipped, or the canvas will be rotated
	for (int x = 0; x < Cell::gridSize_.y; ++x) {
		std::vector<Cell> tempCellArray;
		for (int y = 0; y < Cell::gridSize_.x; ++y) {
			Cell tempCell;
			tempCell.isLive_ = ppm.states_[y][x];
			tempCell.setupPixel(x, y);
			tempCellArray.emplace_back(tempCell);
		}
		cells_.push_back(tempCellArray);
	}
}

void GridManager::push()
{
	// Push onto Rows
	for (int x = 0; x < Cell::gridSize_.x; ++x) {
		Cell tempCell;
		for (int y = 0; y < Cell::gridSize_.y; ++y) {
			tempCell.setupPixel(x, y);
		}
		cells_[x].push_back(tempCell);
	}

	// Push a new column
	vector<Cell> tempCellArray;
	for (int x = 0; x < Cell::gridSize_.x; ++x) {
		for (int y = 0; y < Cell::gridSize_.y; ++y) {
			Cell tempCell;
			tempCell.setupPixel(x, y);
			tempCellArray.emplace_back(tempCell);
		}
	}
	cells_.push_back(tempCellArray);

	Cell::gridSize_.x++;
	Cell::gridSize_.y++;
}

void GridManager::pop()
{
	Cell::gridSize_.x--;
	Cell::gridSize_.y--;
	for (int y = 0; y < Cell::gridSize_.y; ++y) {
		cells_[y].pop_back();
	}
	cells_.pop_back();
}

