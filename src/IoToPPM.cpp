#include "IoToPPM.h"

#include <string>
#include <utility>

IoToPPM::IoToPPM(std::string filename, std::string pType, const int w, const int h,
                 const BOOL_MATRIX& cellStates)
{
	filename_ = std::move (filename);
	pType_    = std::move (pType);
	pxRes_.setXY ({w, h});

	pushCellState (cellStates);
}

IoToPPM::IoToPPM(std::string filename) { filename_ = std::move (filename); }

void IoToPPM::write()
{
	ofFileDialogResult result = ofSystemSaveDialog ("pixelArt.ppm", "save to:");
	const std::string ext     = ofFilePath::getFileExt (result.getName());

	if (ext == "png") { ofSaveScreen ("yama.png"); }
	else if (ext == "ppm") {
		std::ofstream outputFile {filename_};

		outputFile << pType_ << "\n" << pxRes_.x << " " << pxRes_.y << "\n";

		for (const auto& stateRow : cellStates_) {
			for (const auto state : stateRow) outputFile << state << " ";
			outputFile << "\n";
		}

		outputFile.close();
	}
	else {
		ofSystemAlertDialog ("PLEASE USE EITHER .ppm OR .PNG");
		ofDirectory file (result.getPath());
		std::cout << file.remove (false);
	}
}

ReadPPM IoToPPM::read()
{
	ofFileDialogResult result = ofSystemLoadDialog ("fuck", false,
	                                                ofFilePath::getCurrentExeDir() +
	                                                "\\data");

	if (result.bSuccess) { filename_ = result.getPath(); }

	std::ifstream inputFile {filename_};

	// Get canvas type
	std::getline (inputFile, pType_);

	// Get canvas resolution
	std::string res;
	std::getline (inputFile, res);

	const std::string::size_type found = res.find (' ');
	if (found != std::string::npos) {
		pxRes_.x = stoi (res.substr (0, found));
		pxRes_.y = stoi (res.substr (found + 1));
	}

	// Bug where non square grid size corrupts image.
	BOOL_MATRIX cellStates;
	std::vector <bool> tempCellArray;

	while (!inputFile.eof()) {
		int number;
		if (inputFile >> number) {
			std::cout << number << " ";
			tempCellArray.push_back (number);
			if (tempCellArray.size() >= pxRes_.y) {
				cellStates.push_back (tempCellArray);
				tempCellArray.clear(); // Allows temp cell array to be reused
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


void IoToPPM::pushCellState(const BOOL_MATRIX& cellStates)
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
