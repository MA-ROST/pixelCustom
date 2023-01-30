#pragma once
#include "ofMain.h"
#include "point.h"

class Cell {
public:
	bool isLive_ {false}, markedForUpdate_ {false};
	Rect <float> collider_;

	enum stateColor {
		inactive = 255,
		active = 0
	};

	static Point<int> gridSize_;

	/**
	 * @brief sets up the pixel for drawing, and then draws it
	 *
	 * @param x The x index of the vector
	 * @param y The y index of the vector
	 */
	void setupPixel(const int& x, const int& y);

	/**
	 * @brief toggles the status of isLive_ based on if markedForUpdate_ is true
	 */
	void updateCell();
	/**
	 * @brief Checks to see if the click event was inside of this cell.
	 * @param x Where the mouse was clicked on a horizontal axis
	 * @param y Where the mouse was clicked on a vertical axis
	 * @return If the click was inside of this cell.
	 */
	bool wasClickInside(int x, int y);

private:
	/**
	 * @brief Determines the visual look of a pixel based on a given number
	 */
	void setStyle() const;

	/**
	 * @brief through the amount of pixels and size of the window,
	 * the height and width of a pixel is determined
	 *
	 * @return The calculated height and width for each pixel
	 */
	static Point<float> calculatePixelSize();
};
