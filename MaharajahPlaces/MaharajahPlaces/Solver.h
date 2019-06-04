#pragma once

#include "Desk.h"

class Solver {
private:
	int _result;

	void stormWithPlace(Desk&, int, int);
	void stormWithSkipPlace(Desk&, int, int);
	void storm(Desk&, int, int);

public:
	void calculateCombinations(Desk desk, int figuresQuantity);

	int combinationsAmount();
};

