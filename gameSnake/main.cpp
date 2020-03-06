#include <easyx.h>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <string>
using namespace std;
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

int main()
{
	initgraph(800, 520);
	srand(time(NULL));
BEGIN:
	//外部绘图
	setfillcolor(WHITE); setlinecolor(WHITE);
	fillrectangle(0, 0, 10, 10);
	for (int i = 0; i < 52; ++i)
	{
		fillrectangle(i * 10 + 1, 1, i * 10 + 9, 9);
		fillrectangle(i * 10 + 1, 511, i * 10 + 9, 519);
		fillrectangle(1, i * 10 + 1, 9, i * 10 + 9);
		fillrectangle(511, i * 10 + 1, 519, i * 10 + 9);
	}
	settextcolor(LIGHTGRAY);
	settextstyle(30, 15, _T("宋体"));
	//snake信息：body信息，方向信息，头尾索引
	vector<vector<int>> snake(50, vector<int>(50, 0));
	snake[0][0] = 1; snake[0][1] = 1; snake[0][2] = 1;
	vector<vector<int>> next(50, vector<int>(50, 0));
	next[0][0] = RIGHT; next[0][1] = RIGHT;
	int headi = 0, headj = 2;
	int taili = 0, tailj = 0;
	//属性信息
	char moveDirection = 77;	//current direction
	int foodi = 0, foodj = 0;	//food index
	int speed = 9;
	bool highSpeed = false;
	int len = 3;
	while (1)
	{
		//绘图
		setfillcolor(LIGHTGRAY); setlinecolor(LIGHTGRAY);
		for (int i = 0; i < 50; ++i)
		{
			for (int j = 0; j < 50; ++j)
			{
				if (1 == snake[i][j])
				{
					fillrectangle(j * 10 + 10, i * 10 + 10, j * 10 + 20, i * 10 + 20);
				}
				else if (2 == snake[i][j])
				{
					setfillcolor(YELLOW); setlinecolor(YELLOW);
					fillcircle(j * 10 + 15, i * 10 + 15, 5);
					setfillcolor(LIGHTGRAY); setlinecolor(LIGHTGRAY);
				}
			}
		}
		TCHAR s[5];
		_stprintf_s(s, _T("%d"), len);
		outtextxy(530, 20, _T("长度：")); outtextxy(650, 20, s);
		if (highSpeed)
		{
			_stprintf_s(s, _T("%d"), speed * 2);
		}
		else
		{
			_stprintf_s(s, _T("%d"), speed);
		}
		outtextxy(530, 80, _T("速度：")); outtextxy(650, 80, s);
		_stprintf_s(s, _T("%d"), len - 3);
		outtextxy(530, 140, _T("分数：")); outtextxy(650, 140, s);
		outtextxy(530, 200, _T("~按z以开关加速~"));
		//speed
		if (highSpeed)
		{
			Sleep(500 / speed);
		}
		else
		{
			Sleep(1000 / speed);
		}
		//生成新food
		if (snake[foodi][foodj] != 2)
		{
			int foodIndex = (rand() % (2500 - len)) + 1;
			for (int i = 0; i < 2500; ++i)
			{
				if (0 == snake[i % 50][i / 50])
				{
					if (0 == --foodIndex)
					{
						foodi = i % 50;
						foodj = i / 50;
						break;
					}
				}
			}
			snake[foodi][foodj] = 2;
		}
		//等待键盘输入 or 方向不变
		char input = 0;
		while (_kbhit())
		{
			input = _getch();
		}
		if ('z' == input || 'Z' == input)
		{
			highSpeed = !highSpeed;
		}
		else if (72 == input || 80 == input || 75 == input || 77 == input)
		{
			if (input + moveDirection != 152)	//目标方向和当前方向不能相反
			{
				moveDirection = input;
			}
		}
		switch (moveDirection)
		{
		case 72:
			//更新方向关系，头索引
			next[headi][headj] = UP;
			--headi;
			break;
		case 80:
			next[headi][headj] = DOWN;
			++headi;
			break;
		case 75:
			next[headi][headj] = LEFT;
			--headj;
			break;
		case 77:
			next[headi][headj] = RIGHT;
			++headj;
			break;
		default:
			break;
		}
		//game over判断
		if (headj > 49 || headj < 0 || headi > 49 || headi < 0 || 1 == snake[headi][headj])
		{
			break;
		}
		//吃到food则不删除尾，直接更新len和speed
		if (2 == snake[headi][headj])
		{
			++len;
			if (len < 100)
			{
				speed = 8 + len / 12;
			}
		}
		else
		{
			//删除尾，更新方向关系，尾索引
			snake[taili][tailj] = 0;
			int direction = next[taili][tailj];
			next[taili][tailj] = 0;
			if (LEFT == direction)
			{
				--tailj;
			}
			else if (RIGHT == direction)
			{
				++tailj;
			}
			else if (UP == direction)
			{
				--taili;
			}
			else if (DOWN == direction)
			{
				++taili;
			}
		}
		//添加新头(++len)
		snake[headi][headj] = 1;
		//清屏
		setfillcolor(BLACK); setlinecolor(BLACK);
		fillrectangle(10, 10, 510, 510);
		fillrectangle(530, 20, 800, 520);
	}
	if (2500 == len)
	{
		outtextxy(530, 260, _T("你居然通关了!"));
	}
	else
	{
		outtextxy(530, 260, _T("Game over!"));
	}
	outtextxy(530, 320, _T("按任意键退出！"));
	outtextxy(530, 380, _T("r键重新开始~"));
	fflush(stdin);
	char ch = _getch();
	if ('r' == ch || 'R' == ch)
	{
		goto BEGIN;
	}

	closegraph();
	return 0;
}