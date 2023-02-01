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

IoToPPM::IoToPPM(std::string filename) { filename_ = std::move (filename); }

void IoToPPM::write()
{
	std::ofstream outputFile {filename_};

	outputFile << pType_ << "\n";
	outputFile << pxRes_.x << " " << pxRes_.y << "\n";

	for (const auto& stateRow : cellStates_) {
		for (const auto state : stateRow) outputFile << state << " ";
		outputFile << "\n";
	}

	outputFile.close();
}

ReadPPM IoToPPM::read()
{
	std::ifstream inputFile {filename_};

	std::getline (inputFile, pType_);

	std::string res;
	std::getline (inputFile, res);

	std::string::size_type found = res.find (' ');
	if (found != std::string::npos) {
		pxRes_.x = stoi (res.substr (0, found));
		pxRes_.y = stoi (res.substr (found + 1));
	}

	// Bug where non square grid size corrupts image.
	std::vector <std::vector <bool>> cellStates;
	std::vector <bool> tempCellArray;

	while (!inputFile.eof()) {
		int number;
		if (inputFile >> number) {
			std::cout << number << " ";
			tempCellArray.push_back (number);
			if (tempCellArray.size() >= pxRes_.y) {
				cellStates.push_back (tempCellArray);
				tempCellArray.clear();
				std::cout << "\n";
			}
		}
		else {
			inputFile.clear(); // Clear the fail bit.
			break; // Assumes perfect user
		}
	}
	inputFile.close();

	return {pxRes_, cellStates};
}


void IoToPPM::pushCellState(const std::vector <std::vector <bool>>& cellStates)
{
	for (int x = 0; x < pxRes_.y; ++x) {
		std::vector <bool> tempCellArray;
		tempCellArray.reserve (pxRes_.x);
		for (int y = 0; y < pxRes_.x; ++y) {
			tempCellArray.emplace_back (cellStates[y][x]);
		}
		cellStates_.push_back (tempCellArray);
	}
}
