#pragma once

#include <vector>

class Desk {
private:
	int _width;
	int _height;
	std::vector<std::vector<bool>> _desk;

	Desk(int height, int width, std::vector<std::vector<bool>> desk);

public:
	Desk(int height, int width);

	Desk copy();

	void set(int y, int x, bool value);
	void fillRow(int y, bool value);
	void fillColumn(int x, bool value);
	void fillMainDiagonal(int y, int x, bool value);
	void fillAdditionalDiagonal(int y, int x, bool value);

	bool value(int x, int y);

	int width();
	int height();
};
