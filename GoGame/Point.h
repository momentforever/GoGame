#pragma once

#include "Const.h"
class Point
{
public:
	Point(position pos);
	Point(position pos, Type type, uint8_t step);

	~Point();

	void setBelong(Type belong);
	Type getBelong();

	void setType(Type type);
	Type getType();

	void setStep(uint8_t step);
	uint8_t getStep();

	position get_pos();

	void resetPiece();


private:
	Type belong_ = Type::empty;
	Type type_ = Type::empty;
	uint8_t step_ = 0;

	position pos_;
};

