#include "cell.h"

Point<int> Cell::gridSize_{ 16, 16 };
int Cell::cellSize_ {50};

void Cell::setupPixel(const int& x, const int& y)
{
	const Point<float> pixelSize = {static_cast<float>(cellSize_), static_cast<float>(cellSize_)};
	setStyle();
	collider_ = { pixelSize.x * x, pixelSize.y * y, pixelSize.x, pixelSize.y};
	collider_.drawRect();
}

void Cell::updateCell()
{
	if (markedForUpdate_) {
		isLive_          = isLive_ ? false : true;
		markedForUpdate_ = false;
	}
}

bool Cell::wasClickInside(int x, int y)
{
	return collider_.checkBounds(static_cast<float>(x),static_cast<float>(y));
}

void Cell::setStyle() const
{
	ofFill();
	if (isLive_) ofSetColor (active); 
	else {
		ofNoFill();
		ofSetColor (inactive);
	}
}
