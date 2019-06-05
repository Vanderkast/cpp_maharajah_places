#include <exception>
#include "Solver.h"

static const char* ILLEGAL_FIGURES_QUANTITY_EXCEPTION_MESSAGE = "Figures quantity must not be negative or zero.";

bool potentiallySolvable(int deskHeight, int deskWidth, int figuresQuantity);
void checkFiguresQuantityLegal(int quantity);

void placeMaharajah(Desk& desk, int y, int x);
void placeAsHorse(Desk& desk, int y, int x);
void placeAsRook(Desk& desk, int y, int x);
void placeAsOficcer(Desk& desk, int y, int x);

void setPointFalseIfPossible(Desk& desk, int y, int x);
bool pointInsideDesk(Desk& desk, int y, int x);

void Solver::storm(Desk& desk, int currentRow, int figuresQuantity) {
	if (figuresQuantity == 0) {
		++(this->_result);
		return;
	}

	if (currentRow < desk.height()) {
		stormWithPlace(desk, currentRow, figuresQuantity);
		stormWithSkipPlace(desk, currentRow, figuresQuantity);
	}
}

void Solver::stormWithPlace(Desk& desk, int currentRow, int figuresQuantity) {
	for (int i = 0; i < desk.width(); i++) {
		if (desk.value(currentRow, i)) {
			Desk copy = desk.copy();
			placeMaharajah(copy, currentRow, i);
			storm(copy, currentRow + 1, figuresQuantity - 1);
		}
	}
}

void placeMaharajah(Desk& desk, int y, int x) {
    placeAsRook(desk, y, x);
    placeAsOficcer(desk, y, x);
    placeAsHorse(desk, y, x);
}

void placeAsRook(Desk& desk, int y, int x){
    desk.fillColumn(x, false);
    desk.fillRow(y, false);
}

void placeAsOficcer(Desk& desk, int y, int x){
    desk.fillMainDiagonal(y, x, false);
    desk.fillAdditionalDiagonal(y, x, false);
}

void placeAsHorse(Desk& desk, int y, int x){
    setPointFalseIfPossible(desk, y-2, x-1);
    setPointFalseIfPossible(desk, y-2, x+1);
    setPointFalseIfPossible(desk, y-1, x-2);
    setPointFalseIfPossible(desk, y-1, x+2);
    setPointFalseIfPossible(desk, y+1, x-2);
    setPointFalseIfPossible(desk, y+1, x+2);
    setPointFalseIfPossible(desk, y+2, x-1);
    setPointFalseIfPossible(desk, y+2, x+1);
}

void setPointFalseIfPossible(Desk& desk, int y, int x){
    if(pointInsideDesk(desk, y, x))
        desk.set(y, x, false);
}

bool pointInsideDesk(Desk& desk, int y, int x){
    return y >= 0 && y < desk.height() && x >= 0 && x < desk.width();
}

void Solver::stormWithSkipPlace(Desk & desk, int currentRow, int figuresQuantity) {
	if (desk.height() - currentRow > figuresQuantity) {
		Desk copy = desk.copy();
		storm(copy, currentRow + 1, figuresQuantity);
	}
}

void Solver::calculateCombinations(Desk desk, int figuresQuantity) {
	checkFiguresQuantityLegal(figuresQuantity);

	if (potentiallySolvable(desk.height(), desk.width(), figuresQuantity))
		this->storm(desk, 0, figuresQuantity);
}

void checkFiguresQuantityLegal(int quantity) {
	if (quantity <= 0)
		throw ILLEGAL_FIGURES_QUANTITY_EXCEPTION_MESSAGE;
}

int Solver::combinationsAmount() {
	return this->_result;
}

bool potentiallySolvable(int deskHeight, int deskWidth, int figuresQuantity) {
	return (deskHeight >= figuresQuantity) && (deskWidth >= figuresQuantity);
}
