#include "IoToPPM.h"

#include <string>
#include <utility>

IoToPPM::IoToPPM(std::string filename, std::string pType, const int w, const int h,
                 const std::vector <std::vector <bool>>& cellStates)
{
	filename_ = std::move (filename);
	pType_    = std::move (pType);
	pxRes_.setXY ({w, h});

	pushCellState (cellStates);
}

IoToPPM::IoToPPM(std::string filename)
{
	filename_ = std::move (filename);
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

void IoToPPM::read()
{
	if (!inputFile_.is_open()) {
		inputFile_.open (filename_);
	}

	std::getline(inputFile_, pType_);

	std::string ds;
	std::getline(inputFile_, ds);
	
	std::string::size_type found = ds.find (' ');
	if (found!=std::string::npos) {
		pxRes_.x = stoi(ds.substr (0, found));
		pxRes_.y = stoi(ds.substr (found+1));
	}


	// Bug where non square grid size corrupts image.
	std::vector <std::vector <bool>> cellStates;
	std::vector <bool> tempCellArray;

	while (!inputFile_.eof()) {
		int number;
		if (inputFile_ >> number) {
			std::cout << number << " ";
			tempCellArray.push_back (number);
			if (tempCellArray.size() >= pxRes_.y) {
				cellStates.push_back (tempCellArray);
				tempCellArray.clear();
				std::cout << "\n";
			}
		} else {
			inputFile_.clear(); // Clear the fail bit.
			// Assumes perfect user
			break;
		}
	}
	inputFile_.close();
}


void IoToPPM::pushCellState(const std::vector <std::vector <bool>>& cellStates)
{
	for (int x = 0; x < pxRes_.y; ++x) {
		std::vector <bool> tempCellArray;
		tempCellArray.reserve (pxRes_.x);
		for (int y = 0; y < pxRes_.x; ++y) {
			tempCellArray.emplace_back (cellStates[y][x]);
		}
		cellStates_.push_back(tempCellArray);
	}
}


