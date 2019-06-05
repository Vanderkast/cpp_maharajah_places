#include "Desk.h"
#include <cassert>
#include <new>

const char* MEMORY_ALLOCATION_EXCEPTION_MESSAGE;
const char* ILLEGAL_MATRIX_INPUT_DATA_EXCEPTION_MESSAGE;

std::vector<std::vector<bool>> createDesk(int height, int width);
void checkInputOnLegal(int height, int width);

Desk::Desk(int height, int width, std::vector<std::vector<bool>> desk) {
	this->_height = height;
	this->_width = width;
	this->_desk = desk;
}

Desk::Desk(int height, int width) {
	checkInputOnLegal(height, width);

	this->_height = height;
	this->_width = width;
	this->_desk = createDesk(this->_height, this->_width);
}

void checkInputOnLegal(int height, int width) {
	if (height <= 0 || width <= 0)
		throw ILLEGAL_MATRIX_INPUT_DATA_EXCEPTION_MESSAGE;
}

std::vector<std::vector<bool>> createDesk(int height, int width) {
	std::vector<std::vector<bool>> desk;
	for (int i = 0; i < height; i++) {
		std::vector<bool> line;
		for (int j = 0; j < width; j++) {
			line.push_back(true);
		}
		desk.push_back(line);
	}
	return desk;
}

Desk Desk::copy() {
	std::vector<std::vector<bool>> desk;
	for (int i = 0; i < this->_height; i++) {
		std::vector<bool> line;
		for (int j = 0; j < this->_width; j++) {
			line.push_back(this->_desk[i][j]);
		}
		desk.push_back(line);
	}

	return Desk(this->_height, this->_width, desk);
}

void Desk::set(int y, int x, bool value) {
	this->_desk[y][x] = value;
}

void Desk::fillRow(int y, bool value) {
	for (int i = 0; i < this->_width; i++) {
		this->_desk[y][i] = value;
	}
}

void Desk::fillColumn(int x, bool value) {
	for (int i = 0; i < this->_height; i++) {
		this->_desk[i][x] = value;
	}
}

void Desk::fillMainDiagonal(int y, int x, bool value) {
	int yPoint = x > _width - y - 1 ? 0 : y - x;
	int xPoint = x > _width - y - 1 ? x - y : 0;
	while (xPoint < _width && yPoint < _height) {
		_desk[yPoint++][xPoint++] = value;
	}
}

void Desk::fillAdditionalDiagonal(int y, int x, bool value) {
    int yPoint = x > y ? _width - x - 1 - y : 0;
    int xPoint = x > y ? _width - 1 : 0;
    while (xPoint >= 0 && yPoint < _height) {
        _desk[yPoint++][xPoint--] = value;
    }
}

bool Desk::value(int y, int x) {
	return this->_desk[y][x];
}

int Desk::width() {
	return this->_width;
}

int Desk::height() {
	return this->_height;
}
