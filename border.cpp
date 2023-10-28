#include "border.h"
#include <cstdlib>
#include <ctime>
Border::Border(int wet, int high, int mN)
{
	w = limit(wet,MAX,MIN);
	h = limit(high,MAX,MIN);
	mineNum = mineLimit(mN);
}

int Border::limit(const int& x, const int& max, const int& min)
{
	if (x > max) {
		return max;
	}
	else if (x < min) {
		return min;
	}
	else {
		return x;
	}
}

int Border::mineLimit(const int& mN)
{
	if (mN < w * h) {
		if (mN > MINE_MAX) {
			return MINE_MAX;
		}
		else if (mN < MIN) {
			return MIN;
		}
		else {
			return mN;
		}
	}
	else
		return w * h * 4/5;
}

void Border::setMine(const int& x, const int& y)
{
	srand((int)time(0));
	for (int cishu = 1; cishu <= mineNum; cishu++) {
		int rx = rand() % w;
		int ry = rand() % h;
		Mine& block = erea[rx][ry];
		if (block.isA_Mine() || rx == x && ry == y) {
			cishu--;
		}
		else {
			block = true;
		}
	}
}

int Border::surround(const int& x, const int& y)
{
	int mines = 0;
	for (int i = x - 1; i <= x + 1 && i < w; i++) {
		for (int j = y - 1; j <= y + 1 && j < h; j++) {
			if (!(i == x && j == y) && i >= 0 && j >= 0) {
				if (erea[i][j].isA_Mine()) {
					mines++;
				}
			}
		}
	}
	return mines;
}

int Border::dig(const int& x, const int& y)
{
	const int &sx = limit(x, w - 1, 0), &sy = limit(y, h - 1, 0);
	erea[sx][sy].digged();
	if (erea[sx][sy].isA_Mine()) {
		return -1;
	}
	else {
		int i = surround(sx, sy);
		erea[sx][sy] = i;
		if (i == 0) {
			digSide(sx, sy);
		}
		return 0;
	}	
}

void Border::blockState(const int& x, const int& y, bool& M, bool& L, int& N)
{
	M = erea[x][y].isA_Mine();
	L = erea[x][y].isLocked();
	N = erea[x][y].num();
}

void Border::digSide(const int& x, const int& y)
{
	for (int i = x - 1; i <= x + 1 && i < w; i++) {
		for (int j = y - 1; j <= y + 1 && j < h; j++) {
			if (erea[i][j].isLocked() && (!(i == x && j == y) && i >= 0 && j >= 0)) {
				dig(i, j);
			}
		}
	}
}

void Border::showMine()
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (erea[i][j].isLocked() && erea[i][j].isA_Mine()) {
				erea[i][j].digged();
			}
		}
	}
}

int Border::safeBlock()
{
	int blocks = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (erea[i][j].isA_Mine() == false && erea[i][j].isLocked() == true) {
				blocks++;
			}
		}
	}
	return blocks;
}
