#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include "border.h"
#pragma comment(lib,"winmm.lib")
namespace game {
	Border* border;
	void welcome();
	void start(const int& w,const int& h,const int& mineNum);
	void selfDef();
	void printBoard(int situation = -1);
	int Vjudge();
	void victory();
	void defeat();
}
using namespace std;
using namespace game;

void game::welcome() {
	int choice = 0;
	cout << endl;
	cout << "\t\t\033[32m*************************************************\033[0m" << endl;
	cout << "\t\t\033[32m*\033[36m\t\t最简陋的扫雷\t\t\t\033[32m*" << endl;
	cout << "\t\t\033[32m*\033[33m\t\t\tv1.1\t\t\t\033[32m*" << endl;
	cout << "\t\t\033[32m*\033[34m\t\tby .宇宙王朝\t\t\t\033[32m*" << endl;
	cout << "\t\t\033[32m*************************************************\033[0m" << endl << endl;
	do
	{
		cout << endl << "开始一个新游戏" << endl;
		cout << "[1]初级：10个雷，9*9大小" << endl;
		cout << "[2]中级：40个雷，16*16大小" << endl;
		cout << "[3]高级：99个雷，16*30大小" << endl;
		cout << "[4]自定义..." << endl;
		cout << "[-1]退出" << endl;
		cin >> choice;
		switch (choice) {
		case 1:start(9, 9, 10); break;
		case 2:start(16,16,40); break;
		case 3:start(30,16,99); break;
		case 4:selfDef(); break;
		case -1:; break;
		default: {
			cout << "无效的指令" << endl;
			cin.clear();
			cin.ignore();
			}
			   break;
		}
	} while (choice!=-1);
	
}

void game::start(const int& w, const int& h, const int& mineNum)
{
	cin.clear();
	cin.ignore();
	system("cls");
	int x = 0, y = 0;
	border = new Border(w,h,mineNum);
	if (border == NULL) throw border;
	bool isFirstDig = true;
	int situation = 0;
	do {
		if (isFirstDig) {
			printBoard();
			cout << "Tips:输入两个数来点开方格\n如输入“3 4”指点开第3列第4行的方格，两数要用空格分隔" << endl;
		}
		else if (Vjudge() == 1) {
			situation = 1;
			sndPlaySound(L"victory.wav", SND_ASYNC);
			break;
		}
		int cinx = 0, ciny = 0;
		cin >> cinx >> ciny;
		if (cinx != 0 && ciny != 0) {
			x = cinx - 1;
			y = ciny - 1;
			if (isFirstDig) {
				border->setMine(x, y);
				isFirstDig = false;
			}
			situation = border->dig(x, y);
		}
		else {
			cout << "无效的输入" << endl;
			cin.clear();
			cin.ignore();
		}
		system("cls");
		printBoard();
		if(situation == -1)
			sndPlaySound(L"defeat.wav", SND_ASYNC);
	} while (situation != -1);
	border->showMine();
	printBoard(situation);
	switch (situation) {
	case 1:victory(); break;
	case -1:defeat(); break;
	}
	cin.clear();
	cin.ignore();
	
	delete border;
	system("cls");
}

void game::selfDef()
{
	cin.clear();
	cin.ignore();
	cout << endl << "进入自定义模式" << endl;
	int w, h, mN;
	cout << "输入行宽(9-30)：";
	cin >> w;
	cout << "输入列高(9-30)：";
	cin >> h;
	cout << "输入地雷数(9-668)：";
	cin >> mN;
	start(w, h, mN);
}

void game::printBoard(int situation)
{
	cout << endl;
	for (int j = 0; j <= border->high(); j++) {
		for (int i = 0; i < border->weight(); i++) {
			if (j == border->high()) {
				printf("%2d", i+1);
			}
			else {
				bool isMine, locked;
				int number;
				border->blockState(i, j, isMine, locked, number);
				if (locked) {
					cout << "\033[36m■\033[0m";
				}
				else if (isMine) {
					if(situation == 1)
						cout << "\033[42;30m *\033[0m";
					else
						cout << "\033[41;30m *\033[0m";
				}
				else if (number == 0) {
					cout << "\033[32m□\033[0m";
				}
				else {
					switch (number) {					
					case 1:
						cout << " \033[36m"; break;
					case 2:
						cout << " \033[32m"; break;
					case 3:
						cout << " \033[33m"; break;
					case 4:
						cout << " \033[34m"; break;
					case 5:
						cout << " \033[35m"; break;
					case 6:
						cout << " \033[33m"; break;
					case 7:
						cout << " \033[35m"; break;
					case 8:
						cout << " \033[31m"; break;
					}
					cout << number;
				}
			}
		}
		if (j != border->high()) {
			cout << "\033[0m||" << j+1;
		}
		cout << endl;
	}
}

int game::Vjudge()
{
	if (border->safeBlock() == 0) {
		return 1;
	}
	else
		return 0;
}

void game::victory()
{
	cout << endl;
	cout << "//////////////////////////////////////" << endl;
	cout << "//恭喜获得胜利，你就是“扫雷大师”！//" << endl;
	cout << "//////////////////////////////////////" << endl;
	system("pause");
}

void game::defeat()
{	
	cout << endl;
	cout << "//////////////////////////////" << endl;
	cout << "//不好意思你输了，下次加油！//" << endl;
	cout << "//////////////////////////////" << endl;
	system("pause");
}

int main(int argc, char** argv) {
	try {
		welcome();
	}
	catch (Border*) {
		cout << "出错！内存已满，无法进行游戏！" << endl;
		return -1;
	}

	return 0;
}