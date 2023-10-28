#include "mine.h"
#ifndef _BORDER_H_
#define _BORDER_H_

#define MAX 30			//界面长宽的上限
#define MIN 9			//界面长宽和雷数的下限
#define MINE_MAX 668	//雷数上限

class Border
{
private:
	//长，高，雷的数量
	int w, h, mineNum;
	//“场地”
	Mine erea[MAX][MAX];
public:
	//初始化“场地”
	Border(int wet, int high, int mN);
	
	//设置界面长宽的上下限，并防止玩家点开越界的方格
	int limit(const int& x, const int& max, const int& min);
	//设置雷数的上下限
	int mineLimit(const int& mN);
	
	//布雷器，调用了srand()和rand()函数，x和y指第一个点开的方格（毕竟扫雷是不会让你上来就点到雷的）
	void setMine(const int& x, const int& y);
	
	//得到一个方格周围雷的数量
	int surround(const int& x, const int& y);
	//点开相应方格，如果是雷返回-1，不是则标记此方格周围的雷数并返回0
	int dig(const int& x, const int& y);
	//若方格周围没有地雷，则自动点开其周边的方格
	void digSide(const int& x, const int& y);
	
	//得到一个方格的三个状态("isMine" and "locked" and "number")
	void blockState(const int& x, const int& y, bool& M, bool& L, int& N);
	//得到界面长宽
	inline int weight() { return w; }
	inline int high() { return h; }
	
	//得到场上剩余的安全方格数
	int safeBlock();

	//显示场上所有地雷
	void showMine();
};
#endif // !_BORDER_H_



