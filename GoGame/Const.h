#pragma once
#include <iostream>
#include "Const.h"

#define ERROR_ 0
#define SUCCESS_ 1  


#define TRUE_ 0
#define FALSE_ 1

#define PI 3.1415926

enum class Type
{
	empty,
	white,
	black,
};

struct position
{
	position() {}
	position(float x, float y) {
		x_ = x;
		y_ = y;
	}
	float x_ = 0;
	float y_ = 0;
};
