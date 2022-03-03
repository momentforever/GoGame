// GoGame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include "Checkerboard.h"
#include "Const.h"
#include "Point.h"
#include <GL/glut.h>
#include <windows.h>

using namespace std;

void DrawCricle(position pos, Type type, GLfloat R) {
	if (type == Type::empty) {
		return;
	}
	int n = 90;
	if (type == Type::white) {
		glBegin(GL_POLYGON);
	}
	else if (type == Type::black) {
		glBegin(GL_LINE_STRIP);
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < n; ++i)
		glVertex2f(R * cos(2 * PI / n * i) + pos.x_, R * sin(2 * PI / n * i) + pos.y_);
	glEnd();
}

void DrawSquare(position pos, Type type, GLfloat R) {
	if (type == Type::empty) {
		return;
	}
	int n = 4;
	if (type == Type::white) {
		glBegin(GL_POLYGON);
	}
	else if (type == Type::black) {
		glBegin(GL_LINE_LOOP);
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < n; ++i)
		glVertex2f(R * cos(2 * PI / n * i) + pos.x_, R * sin(2 * PI / n * i) + pos.y_);
	glEnd();
}

void updateCheckerboard(Checkerboard *checkerboard) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	int lenght = checkerboard->getLength();
	for (int x = 0; x < lenght; ++x) {
		for (int y = 0; y < lenght; ++y) {
			if (y < lenght - 1) {
				glVertex2f(checkerboard->getGrid()[x][y].getPos().x_,
					checkerboard->getGrid()[x][y].getPos().y_);
				glVertex2f(checkerboard->getGrid()[x][y + 1].getPos().x_
					, checkerboard->getGrid()[x][y + 1].getPos().y_);
			}
			if (x < lenght - 1) {
				glVertex2f(checkerboard->getGrid()[x][y].getPos().x_,
					checkerboard->getGrid()[x][y].getPos().y_);
				glVertex2f(checkerboard->getGrid()[x + 1][y].getPos().x_
					, checkerboard->getGrid()[x + 1][y].getPos().y_);
			}
		}
	}
	glEnd();

	DrawCricle(checkerboard->getGrid()[3][3].getPos(), Type::white, 0.015f);
	DrawCricle(checkerboard->getGrid()[15][15].getPos(), Type::white, 0.015f);
	DrawCricle(checkerboard->getGrid()[3][15].getPos(), Type::white, 0.015f);
	DrawCricle(checkerboard->getGrid()[15][3].getPos(), Type::white, 0.015f);
	DrawCricle(checkerboard->getGrid()[9][15].getPos(), Type::white, 0.015f);
	DrawCricle(checkerboard->getGrid()[9][3].getPos(), Type::white, 0.015f);
	DrawCricle(checkerboard->getGrid()[3][9].getPos(), Type::white, 0.015f);
	DrawCricle(checkerboard->getGrid()[15][9].getPos(), Type::white, 0.015f);
	DrawCricle(checkerboard->getGrid()[9][9].getPos(), Type::white, 0.015f);

	for (int x = 0; x < lenght; ++x) {
		for (int y = 0; y < lenght; ++y) {
			if (checkerboard->getGrid()[x][y].getType() == Type::empty) {

			}
			else {
				DrawCricle(checkerboard->getGrid()[x][y].getPos(),
					checkerboard->getGrid()[x][y].getType(), 0.04f);
			}
		}
	}
	glFlush();
}

void myDisplay(void) {
	vector<string> chess = {"qd", "dc", "pq", "qo", "oc", "qj", "eq", "do", "cp", "co", "bp", "np", "po", "pp", "op", "qp", "oq", "oo", "no", "pn", "on", "qq", "po", "pm", "mp", "ck", "ce", "cg", "cc", "cb", "dd", "ec", "bc", "bb", "ef", "gc", "eh", "fg", "ch", "bh", "dh", "bi", "lc", "kq", "kp", "jp", "ko", "bo", "gq", "fp", "ep", "fq", "fr", "eo", "fo", "gp", "hp", "go", "ho", "gn", "hr", "hn", "in", "im", "jm", "jn", "io", "ee", "bg", "bf", "cf", "ag", "ff", "gf", "fe", "ed", "ge", "dg", "eg", "df", "il", "hm", "hl", "fm", "fk", "qf", "mk", "of", "oj", "rd", "rc", "pd", "qc", "od", "pc", "fi", "ej", "hj", "jk", "hf", "de", "bg", "hc", "hb", "ic", "ie", "cj", "bj", "ib", "md", "ke", "jj", "kj", "ji", "fh", "ki", "lj", "le", "je", "kg", "mc", "nl", "ml", "dp", "dq", "cq", "cr", "bq", "br", "ap", "lf", "mi", "pk", "qk", "pi", "mf", "ld", "me", "li", "lh", "qi", "qr", "ql", "om", "rl", "km", "jl", "mm", "kn", "ns", "nr", "qm", "rm", "rn", "pg", "qe", "lm", "gb", "kf", "mg", "nh", "ig", "os", "ln", "kl", "ps", "or", "oh", "ni", "jf", "id", "he", "dk", "ci", "gi", "gj", "hi", "gh", "hh", "gg", "fj", "ii", "fl", "dl", "pr", "qs", "mh", "lg", "rh", "pl", "rj", "ia", "ja", "ha", "jb", "mn", "el", "dm", "re", "rf", "sd", "oo", "nn", "mo", "nq", "nm", "np", "og", "em", "en", "ar", "nk", "nj", "dj", "pf", "pe", "nd", "ne", "nc", "sf", "qg", "se", "rd", "sh", "si", "sg", "ph", "sm", "rk", "ih", "ei", "lo", "lp", "fd", "sl", "sn", "ok", "po", "ek", "di", "ng"};

	Checkerboard checkerboard(19, Type::black);
	updateCheckerboard(&checkerboard);
	Sleep(1000);

	for (auto chess_count = chess.begin(); chess_count < chess.end(); chess_count++) {

		//cout << "(";
		//cout << (*chess_count)[0] - 96;
		//cout << ",";
		//cout << (*chess_count)[1] - 96;
		//cout << ")" << endl;

		if (checkerboard.placePiece((*chess_count)[0] - 96, (*chess_count)[1] - 96, checkerboard.getNowColor()) == ERROR_) {
			cout << "!!!" << endl;
			return;
		};

		updateCheckerboard(&checkerboard);
		//Sleep(500);
	}
	
	//checkerboard.placePiece(1, 7, Type::black);
	//updateCheckerboard(&checkerboard);
	//Sleep(1000);
}


int main(int argc, char* argv[])
{


	glutInit(&argc, argv);//初始化glut  （可不写默认）
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//显示模式初始化 RGB显示模式，单缓冲模式
	glutInitWindowPosition(1000, 600);//窗口窗口位置  （可不写默认）
	glutInitWindowSize(400, 400);//窗口大小  （可不写默认）
	glutCreateWindow("第一个OpenGl程序");//窗口名称
	glutDisplayFunc(&myDisplay);//自定义函数绘图
	glutMainLoop();//消息循环相应
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
