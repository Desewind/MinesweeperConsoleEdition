#ifndef _MINE_H_
#define _MINE_H_
class Mine
{
private:
	//判断此方格是否为雷
	bool isMine;
	//判断此方格是否被点开
	bool locked;
	//判断此方格周边方格的雷数
	int number;
public:
	Mine();
	//"isMine = false or true"
	Mine& operator=(const bool& isMine);
	//set "number"
	Mine& operator=(const int& number);
	//使外界能访问"isMine"
	inline bool isA_Mine() { return isMine; }
	//使外界能访问"locked"
	inline bool isLocked() { return locked; }
	//使外界能访问"number"
	inline int num() { return number; }
	//指该方格已被点开
	void digged();

};
#endif // !_MINE_H_



