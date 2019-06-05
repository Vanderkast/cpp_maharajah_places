#include <exception>
#include "Solver.h"

static const char* ILLEGAL_FIGURES_QUANTITY_EXCEPTION_MESSAGE = "Figures quantity must not be negative or zero.";

bool potentiallySolvable(int deskHeight, int deskWidth, int figuresQuantity);
void checkFiguresQuantityLegal(int quantity);

void placeFigure(Desk& desk, int y, int x) {
	desk.fillColumn(x, false);
	desk.fillRow(y, false);
}

void Solver::storm(Desk& const desk, int currentRow, int figuresQuantity) {
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
			placeFigure(copy, currentRow, i);
			storm(copy, currentRow + 1, figuresQuantity - 1);
		}
	}
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
		throw std::exception(ILLEGAL_FIGURES_QUANTITY_EXCEPTION_MESSAGE);
}

int Solver::combinationsAmount() {
	return this->_result;
}

bool potentiallySolvable(int deskHeight, int deskWidth, int figuresQuantity) {
	return (deskHeight >= figuresQuantity) && (deskWidth >= figuresQuantity);
}