#include "IoToPPM.h"

#include <utility>

IoToPPM::IoToPPM(std::string filename, std::string pType, const int w, const int h,
                 const std::vector <std::vector <bool>>& cellStates)
{
	filename_ = std::move (filename);
	pType_    = std::move (pType);
	pxRes_.setXY ({w, h});

	pushCellState (cellStates);
}

void IoToPPM::write()
{
	if (!outputFile_.is_open()) outputFile_.open (filename_);

	outputFile_ << pType_ << "\n";
	outputFile_ << pxRes_.x << " " << pxRes_.y << "\n";

	for (const auto& stateRow : cellStates_) {
		for (const auto state : stateRow) outputFile_ << state << " ";
		outputFile_ << "\n";
	}

	outputFile_.close();
}

void IoToPPM::pushCellState(const std::vector <std::vector <bool>>& cellStates)
{
	for (int x = 0; x < pxRes_.x; ++x) {
		std::vector <bool> tempCellArray;
		tempCellArray.reserve (pxRes_.y);
		for (int y = 0; y < pxRes_.y; ++y) {
			tempCellArray.emplace_back (cellStates[y][x]);
		}
		cellStates_.push_back (tempCellArray);
	}
}
