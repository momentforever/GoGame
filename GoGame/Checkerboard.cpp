#include "Checkerboard.h"

Checkerboard::Checkerboard(uint8_t length, Type now_color) {
	grid_ = vector<vector<Point>>(length, vector<Point>(length, Point(position())));
	step_count_ = 0;
	now_color_ = now_color;
	length_ = length;

	float x_p = -(length_ / 2 * spacing_);
	float y_p = length_ / 2 * spacing_;

	for (int y = 0; y < length_; ++y) {
		y_p = length_ / 2 * spacing_;
		for (int x = 0; x < length_; ++x) {
			// 特别 : 需要转换 x y 坐标系
			grid_[y][x].setPos(position(x_p, y_p));
			y_p -= spacing_;
		}
		x_p += spacing_;
	}

}

Checkerboard::~Checkerboard() {

}

int Checkerboard::placePiece(uint8_t x, uint8_t y, Type type) {
	x--;
	y--;

	// 超出范围
	if (x > length_ - 1 || y > length_ - 1) {
		return ERROR_;
	}
	// 还没到回合
	if (type != now_color_) {
		return ERROR_;
	}

	// 这个地方已经有子
	if (grid_[x][y].getStep() != 0) {
		return ERROR_;
	}

	grid_[x][y].setStep(step_count_);
	grid_[x][y].setType(type);

	removePiece(x, y, type);

	// 不允许被放置
	if (notAllowToBePlaced(x, y, type) == FALSE_) {
		return ERROR_;
	}

	//更新状态
	now_color_ = switchColor(now_color_);
	++step_count_;
	chess.push(grid_);

	return SUCCESS_;
}

int Checkerboard::regretPiece(Type type) {
	if (chess.empty() == true) {
		return ERROR_;
	}
	int count;
	if (now_color_ == type) {
		count = 2;
	}
	else {
		count = 1;
	}
	while (count > 0 && chess.empty() == false) {
		chess.pop();
		--step_count_;
		--count;
	}
	if (chess.empty() == true) {
		grid_ = vector<vector<Point>>(length_, vector<Point>(length_, Point(position())));
	}
	else {
		grid_ = chess.top();
	}
	return SUCCESS_;
}

void Checkerboard::resetCheckerboard(uint8_t length, Type now_color) {
	grid_ = vector<vector<Point>>(length, vector<Point>(length, Point(position())));
	step_count_ = 0;
	now_color_ = now_color;
}

void Checkerboard::resetCheckerboard(uint8_t length, Type now_color, vector<vector<Point>> grid) {
	grid_ = grid;
	step_count_ = 0;
	now_color_ = now_color;
}

int Checkerboard::notAllowToBePlaced(int x, int y, Type type) {
	uint8_t life_value = 0;
	vector<vector<bool>> grid_memory(length_, vector<bool>(length_, false));

	recursion_judgeAliveOrDead(x, y, &grid_memory, &life_value);
	if (life_value == 0) {
		return FALSE_;
	}
	return TRUE_;
}

int Checkerboard::removePiece(int x, int y, Type type) {
	uint8_t life_value;
	vector<vector<bool>> *grid_memory;

	if (x > 0 &&
		grid_[x - 1][y].getType() != Type::empty &&
		grid_[x - 1][y].getType() != grid_[x][y].getType()) {
		life_value = 0;
		grid_memory = new vector<vector<bool>>(length_, vector<bool>(length_, false));
		recursion_judgeAliveOrDead(x - 1, y, grid_memory, &life_value);
		if (life_value == 0) {
			recursion_removePiece(x - 1, y, grid_[x - 1][y].getType());
		}
	}

	if (x < length_ - 1 &&
		grid_[x + 1][y].getType() != Type::empty &&
		grid_[x + 1][y].getType() != grid_[x][y].getType()) {
		life_value = 0;
		grid_memory = new vector<vector<bool>>(length_, vector<bool>(length_, false));
		recursion_judgeAliveOrDead(x + 1, y, grid_memory, &life_value);
		if (life_value == 0) {
			recursion_removePiece(x + 1, y, grid_[x + 1][y].getType());
		}
	}

	if (y > 0 &&
		grid_[x][y - 1].getType() != Type::empty &&
		grid_[x][y - 1].getType() != grid_[x][y].getType()) {
		life_value = 0;
		grid_memory = new vector<vector<bool>>(length_, vector<bool>(length_, false));
		recursion_judgeAliveOrDead(x, y - 1, grid_memory, &life_value);
		if (life_value == 0) {
			recursion_removePiece(x, y - 1, grid_[x][y - 1].getType());
		}
	}

	if (y < length_ - 1 &&
		grid_[x][y + 1].getType() != Type::empty &&
		grid_[x][y + 1].getType() != grid_[x][y].getType()) {
		life_value = 0;
		grid_memory = new vector<vector<bool>>(length_, vector<bool>(length_, false));
		recursion_judgeAliveOrDead(x, y + 1, grid_memory, &life_value);
		if (life_value == 0) {
			recursion_removePiece(x, y + 1, grid_[x][y + 1].getType());
		}
	}

	return SUCCESS_;
}

int Checkerboard::settlement() {
	situationJudgment(2, 1, 2, 1);
	return SUCCESS_;
}

int Checkerboard::situationJudgment(uint8_t distance, uint8_t different,
	uint8_t straight_proportion, uint8_t slash_proportion) {

	int black_weight = 0;
	int white_weight = 0;

	uint8_t life_value = 0;
	vector<vector<bool>> grid_memory(length_, vector<bool>(length_, false));

	for (int i_y = 0; i_y <= length_ - 1; ++i_y) {
		for (int i_x = 0; i_x <= length_ - 1; ++i_x) {
			if (grid_[i_x][i_y].getType() == Type::empty) {
				black_weight = 0;
				white_weight = 0;
				//左上
				for (int deep = 1; deep <= distance; ++deep) {
					if (i_y - deep < 0 || i_x - deep < 0) {
						break;
					}
					else if (grid_[i_x - deep][i_y - deep].getType() == Type::black) {
						black_weight = slash_proportion * (distance - deep + 1);
						break;
					}
					else if (grid_[i_x - deep][i_y - deep].getType() == Type::white) {
						white_weight += slash_proportion * (distance - deep + 1);
						break;
					}
				}
				//上
				for (int deep = 1; deep <= distance; ++deep) {
					if (i_y - deep < 0) {
						break;
					}
					else if (grid_[i_x][i_y - deep].getType() == Type::black) {
						black_weight = straight_proportion * (distance - deep + 1);
						break;
					}
					else if (grid_[i_x][i_y - deep].getType() == Type::white) {
						white_weight += straight_proportion * (distance - deep + 1);
						break;
					}
				}
				//右上
				for (int deep = 1; deep <= distance; ++deep) {
					if (i_x + deep > length_ - 1 || i_y - deep < 0) {
						break;
					}
					else if (grid_[i_x + deep][i_y - deep].getType() == Type::black) {
						black_weight = slash_proportion * (distance - deep + 1);
						break;
					}
					else if (grid_[i_x + deep][i_y - deep].getType() == Type::white) {
						white_weight += slash_proportion * (distance - deep + 1);
						break;
					}
				}

				//左
				for (int deep = 1; deep <= distance; ++deep) {
					if (i_x - deep < 0) {
						break;
					}
					else if (grid_[i_x - deep][i_y].getType() == Type::black) {
						black_weight = straight_proportion * (distance - deep + 1);
						break;
					}
					else if (grid_[i_x - deep][i_y].getType() == Type::white) {
						white_weight += straight_proportion * (distance - deep + 1);
						break;
					}
				}

				//右
				for (int deep = 1; deep <= distance; ++deep) {
					if (i_x + deep > length_ - 1) {
						break;
					}
					else if (grid_[i_x + deep][i_y].getType() == Type::black) {
						black_weight = straight_proportion * (distance - deep + 1);
						break;
					}
					else if (grid_[i_x + deep][i_y].getType() == Type::white) {
						white_weight += straight_proportion * (distance - deep + 1);
						break;
					}
				}

				//左下
				for (int deep = 1; deep <= distance; ++deep) {
					if (i_x - deep < 0 || i_y + deep > length_ - 1) {
						break;
					}
					else if (grid_[i_x - deep][i_y + deep].getType() == Type::black) {
						black_weight = slash_proportion * (distance - deep + 1);
						break;
					}
					else if (grid_[i_x - deep][i_y + deep].getType() == Type::white) {
						white_weight += slash_proportion * (distance - deep + 1);
						break;
					}
				}

				//下
				for (int deep = 1; deep <= distance; ++deep) {
					if (i_y + deep > length_ - 1) {
						break;
					}
					else if (grid_[i_x][i_y + deep].getType() == Type::black) {
						black_weight = straight_proportion * (distance - deep + 1);
						break;
					}
					else if (grid_[i_x][i_y + deep].getType() == Type::white) {
						white_weight += straight_proportion * (distance - deep + 1);
						break;
					}
				}

				//右下
				for (int deep = 1; deep <= distance; ++deep) {
					if (i_x + deep > length_ - 1 || i_y + deep > length_ - 1) {
						break;
					}
					else if (grid_[i_x + deep][i_y + deep].getType() == Type::black) {
						black_weight = slash_proportion * (distance - deep + 1);
						break;
					}
					else if (grid_[i_x + deep][i_y + deep].getType() == Type::white) {
						white_weight += slash_proportion * (distance - deep + 1);
						break;
					}
				}

				if (abs(black_weight - white_weight) > different) {
					if (black_weight > white_weight) {
						grid_[i_x][i_y].setBelong(Type::black);
					}
					else {
						grid_[i_x][i_y].setBelong(Type::white);
					}
				}
				else {
					grid_[i_x][i_y].setBelong(Type::empty);
				}

			}
			else {
				life_value = 0;
				recursion_judgeAliveOrDead(i_x, i_y, &grid_memory, &life_value);
				if (life_value == 0) {
					recursion_setBelong(i_x, i_y, switchColor(grid_[i_x][i_y].getType()));
				}
				else {
					recursion_setBelong(i_x, i_y, grid_[i_x][i_y].getType());
				}
			}
		}
	}

	return SUCCESS_;
}

void Checkerboard::recursion_setBelong(uint8_t x, uint8_t y, Type belong) {
	//递归终点
	if (grid_[x][y].getBelong() == belong) {
		return;
	}
	else {
		grid_[x][y].setBelong(belong);
	}
	// 上
	if (y > 0 && grid_[x][y - 1].getType() == grid_[x][y].getType()) {
		recursion_setBelong(x, y - 1, belong);
	}
	// 下
	if (y < length_ - 1 && grid_[x][y + 1].getType() == grid_[x][y].getType()) {
		recursion_setBelong(x, y + 1, belong);
	}
	// 左
	if (x > 0 && grid_[x - 1][y].getType() == grid_[x][y].getType()) {
		recursion_setBelong(x - 1, y, belong);
	}
	// 右
	if (x < length_ - 1 && grid_[x + 1][y].getType() == grid_[x][y].getType()) {
		recursion_setBelong(x + 1, y, belong);
	}
	return;
}

void Checkerboard::recursion_removePiece(uint8_t x, uint8_t y, Type type) {
	grid_[x][y].resetPiece();
	// 上
	if (y > 0 && grid_[x][y - 1].getType() == type) {
		recursion_removePiece(x, y - 1, type);
	}
	// 下
	if (y < length_ - 1 && grid_[x][y + 1].getType() == type) {
		recursion_removePiece(x, y + 1, type);
	}
	// 左
	if (x > 0 && grid_[x - 1][y].getType() == type) {
		recursion_removePiece(x - 1, y, type);
	}
	// 右
	if (x < length_ - 1 && grid_[x + 1][y].getType() == type) {
		recursion_removePiece(x + 1, y, type);
	}
	return;
}

void Checkerboard::recursion_judgeAliveOrDead(uint8_t x, uint8_t y, vector<vector<bool>>* grid_memory, uint8_t* life_value) {

	if ((*grid_memory)[x][y] == true) {
		return;
	}
	else {
		// 设置为已查询
		(*grid_memory)[x][y] = true;
	}

	// 上
	if (y == 0) {
		// 没气
	}
	else if (grid_[x][y - 1].getType() == Type::empty) {
		++(*life_value);
	}
	else if (grid_[x][y - 1].getType() == grid_[x][y].getType()) {
		recursion_judgeAliveOrDead(x, y - 1, grid_memory, life_value);
	}
	else if (grid_[x][y - 1].getType() != grid_[x][y].getType()) {
		// 没气
	}
	else {
		cout << "something ERROR_" << endl;
	};

	// 下
	if (y == length_ - 1) {
		// 没气
	}
	else if (grid_[x][y + 1].getType() == Type::empty) {
		++(*life_value);
	}
	else if (grid_[x][y + 1].getType() == grid_[x][y].getType()) {
		recursion_judgeAliveOrDead(x, y + 1, grid_memory, life_value);
	}
	else if (grid_[x][y + 1].getType() != grid_[x][y].getType()) {
		// 没气
	}
	else {
		cout << "something ERROR_" << endl;
	};

	// 左
	if (x == 0) {
		// 没气
	}
	else if (grid_[x - 1][y].getType() == Type::empty) {
		++(*life_value);
	}
	else if (grid_[x - 1][y].getType() == grid_[x][y].getType()) {
		recursion_judgeAliveOrDead(x - 1, y, grid_memory, life_value);
	}
	else if (grid_[x - 1][y].getType() != grid_[x][y].getType()) {
		// 没气
	}
	else {
		cout << "something ERROR_" << endl;
	};

	// 右
	if (x == length_ - 1) {
		// 没气
	}
	else if (grid_[x + 1][y].getType() == Type::empty) {
		++(*life_value);
	}
	else if (grid_[x + 1][y].getType() == grid_[x][y].getType()) {
		recursion_judgeAliveOrDead(x + 1, y, grid_memory, life_value);
	}
	else if (grid_[x + 1][y].getType() != grid_[x][y].getType()) {
		// 没气
	}
	else {
		cout << "something ERROR_" << endl;
	};
	return;
}

Type Checkerboard::switchColor(Type color) {
	if (color == Type::black) {
		return Type::white;
	}
	else if (color == Type::white) {
		return Type::black;
	}
	else {
		cout << "something ERROR_" << endl;
		return Type::empty;
	}
}

uint8_t Checkerboard::getLength() {
	return length_;
}

uint8_t Checkerboard::getStepCount() {
	return step_count_;
}

Type Checkerboard::getNowColor() {
	return now_color_;
}

vector<vector<Point>> Checkerboard::getGrid() {
	return grid_;
}

void Checkerboard::setGridPoint(int x,int y,position pos) {
	// TODO : 判断越界
	grid_[x][y].setPos(pos);
}