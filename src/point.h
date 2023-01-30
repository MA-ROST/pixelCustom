#pragma once

template <typename T>
struct Point {
	T x{ 0 }, y{ 0 };

	void setXY(Point <T> input)
	{
		x = input.x;
		y = input.y;
	}

	void printXY() const
	{
		std::cout << "x:" << x << " y:" << y << "\n";
	}
};


template <typename T>
struct Rect {
	T x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 };

	Point <T> getXY()
	{
		return { x,y };
	}

	Point <T> getWH()
	{
		return { w,h };
	}

	void setXY(Point <T> input)
	{
		x = input.x;
		y = input.y;
	}

	void setWH(Point <T> input)
	{
		w = input.x;
		h = input.y;
	}

	T addXW()
	{
		return x + w;
	}

	T addYH()
	{
		return y + h;
	}

	void printXY() const
	{
		std::cout << "x:" << x << " y:" << y << "\n";
	}

	void printRect() const
	{
		std::cout << "x:" << x << " y:" << y << " w:" << w << " h:" << h << "\n";
	}

	void printRectAdd() const
	{
		std::cout << "x:" << x << " y:" << y << " w:" << x + w << " h:" << y + h << "\n";
	}

	void drawRect() const
	{
		ofDrawRectangle(x, y, w, h);
	}

	void drawRect(int w, int h) const
	{
		ofDrawRectangle(x, y, w, h);
	}

	void drawCircle(int radius) const
	{
		ofDrawCircle(x, y, radius);
	}

	bool checkBounds(T xOut, T yOut)
	{
		if (xOut >= x && xOut <= addXW() && 
			yOut >= y && yOut <= addYH()) 
		{
			return true;
		}
		return false;
	}

	bool checkBounds(Rect<T>& rect)
	{
		if (x >= rect.x && addXW() < rect.addXW()) {
			if (addYH() >= rect.y && y <= rect.y) return true;
		}
		return false;
	}
};
