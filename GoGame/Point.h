#pragma once

#include "Const.h"
class Point
{
public:
	Point(uint8_t x, uint8_t y);
	Point(uint8_t x, uint8_t y, Type type, uint8_t step);

	~Point();

	void setBelong(Type belong);
	Type getBelong();

	void setType(Type type);
	Type getType();

	void setStep(uint8_t step);
	uint8_t getStep();

	void resetPiece();

private:
	Type belong_ = Type::empty;
	Type type_ = Type::empty;
	uint8_t step_ = 0;

	uint8_t x_ = 0;
	uint8_t y_ = 0;
};

