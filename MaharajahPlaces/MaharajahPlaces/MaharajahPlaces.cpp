// MaharajahPlaces.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// 
// Найти количество расстановок K фигур магарадж на доске N x N так, что бы они не били друг друга
// прим.: магараджа сочетает в себе свойства ферзя и коня.

#include <iostream>
#include "Desk.h"
#include "Solver.h"

using namespace std;

void inputMetrix(int& height, int& width, int& quantity);
void showResult(int result);
Desk* buildDesk(int height, int width);
void runSolver(Desk& desk, int figuresQuantity);
void complete(int height, int width, int figuresQuantity);

int main() {
	int width, height, quantity;
	inputMetrix(height, width, quantity);
	complete(height, width, quantity);
}

void inputMetrix(int& height, int& width, int& quantity) {
	cout << "write height of desk: ";
	cin >> height;
	cout << "\nwrite width of desk: ";
	cin >> width;
	cout << "\nwrite quantity of figures: ";
	cin >> quantity;
}

void complete(int height, int width, int figuresQuantity) {
	Desk* desk = buildDesk(height, width);

	if (desk != NULL) {
		runSolver(*desk, figuresQuantity);
		delete desk;
	}
}

void showResult(int result) {
	cout << "\nAmount of combinations: " << result << endl;
}

Desk* buildDesk(int height, int width) {
	try {
		return new Desk(height, width);
	}
	catch (exception e) {
		cout << e.what() << "\nContinuation of program is not possible.\n";
	}
	return NULL;
}

void runSolver(Desk & desk, int figuresQuantity) {
	try {
		Solver solver = Solver();
		solver.calculateCombinations(desk, figuresQuantity);
		showResult(solver.combinationsAmount());
	}
	catch (exception e) {
		cout << e.what() << "\nContinuation of program is not possible.\n";
	}
}
