#include "IoToPPM.h"

#include <utility>

IoToPPM::IoToPPM(std::string filename, std::string pType, int w, int h,
	std::vector<std::vector<bool>> cellStates)
{
	filename_ = std::move (filename);
	pType_    = std::move (pType);
	pxRes_.setXY ({w, h});
}

void IoToPPM::write()
{
	if(!outputFile_.is_open()) {
		outputFile_.open(filename_);
	}

	outputFile_ << pType_ << "\n";
	outputFile_ << pxRes_.x << " " << pxRes_.y << "\n";


	outputFile_.close();
}
