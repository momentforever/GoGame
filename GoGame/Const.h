#pragma once
#include <iostream>
#include "Const.h"

#define ERROR 1
#define SUCCESS 0


#define TRUE 0
#define FALSE 1

enum class Type
{
	empty,
	white,
	black,
};

struct position
{
	uint8_t x = 0;
	uint8_t y = 0;
};