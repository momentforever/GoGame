#pragma once

#include <vector>
#include <stack>
#include "Const.h"
#include "Point.h"

using namespace std;

class Checkerboard
{
public:
	Checkerboard(uint8_t length, Type now_color);
	Checkerboard(uint8_t length, Type now_color, vector<vector<Point>> grid);
	~Checkerboard();

	uint8_t getLength();
	uint8_t getStepCount();
	Type getNowColor();
	vector<vector<Point>> getGrid();

	int removePiece(int x, int y, Type type);
	int notAllowToBePlaced(int x, int y, Type type);
	int placePiece(uint8_t x, uint8_t y, Type type);
	int regretPiece(Type type);
	void resetCheckerboard(uint8_t length, Type now_color);
	void resetCheckerboard(uint8_t length, Type now_color, vector<vector<Point>> grid);
	Type switchColor(Type color);
	int situationJudgment(uint8_t distance, uint8_t different, uint8_t straight_proportion, uint8_t slash_proportion);
	int settlement();
private:
	uint8_t length_;
	vector<vector<Point>> grid_;
	stack<vector<vector<Point>>> chess;
	Type now_color_;
	uint8_t step_count_;

	void recursion_judgeAliveOrDead(uint8_t x, uint8_t y, vector<vector<bool>>* grid_memory, uint8_t* life_value);
	void recursion_removePiece(uint8_t x, uint8_t y, Type type);
	void recursion_setBelong(uint8_t x, uint8_t y, Type belong);
};

