#include "Point.h"

Point::Point(position pos, Type type, uint8_t step) {
	pos_ = pos;
	type_ = type;
	step_ = step;
	belong_ = Type::empty;
}

Point::Point(position pos) {
	pos_ = pos;
}

Point::~Point() {

}

void Point::setBelong(Type belong) {
	belong_ = belong;
}

Type Point::getBelong() {
	return belong_;
}

void Point::setType(Type type) {
	type_ = type;
}

Type Point::getType() {
	return type_;
}


void Point::setStep(uint8_t step) {
	step_ = step;
}

uint8_t Point::getStep() {
	return step_;
}

position Point::get_pos() {
	return pos_;
}

void Point::resetPiece() {
	belong_ = Type::empty;
	type_ = Type::empty;
	step_ = 0;
	pos_.x = 0;
	pos_.y = 0;
}


