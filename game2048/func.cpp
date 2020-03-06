#include "func.h"

int execute(View& view, int& score, int direction)
{
	View nView = { 0 };
	int rest = 0;
	int ret = 0;
	bool flag = false;	//判断数据是否出现合并或移动
	if (direction == LEFT)
	{
		for (int i = 0; i != 4; ++i)
		{
			int tmp = 0, k = 0;
			for (int j = 0; j != 4; ++j)
			{
				if (view[i][j] != 0)
				{
					if (0==tmp)
					{
						tmp = view[i][j];
						if (j != 0)
						{
							flag = true;
						}
					}
					else
					{
						if (tmp == view[i][j])	//两数合并
						{
							flag = true;
							score += tmp * 2;
							nView[i][k++] = tmp * 2;
							if (2048 == tmp * 2)
							{
								ret = 2;
							}
							tmp = 0;
						}
						else
						{
							nView[i][k++] = tmp;
							tmp = view[i][j];
							if (k != j)
							{
								flag = true;
							}
						}
					}
				}
			}
			if (tmp != 0)
			{
				nView[i][k++] = tmp;
			}
			rest += 4 - k;
		}
	}
	else if (direction == RIGHT)
	{
		for (int i = 0; i != 4; ++i)
		{
			int tmp = 0, k = 3;
			for (int j = 3; j != -1; --j)
			{
				if (view[i][j] != 0)
				{
					if (0 == tmp)
					{
						tmp = view[i][j];
						if (j != 3)
						{
							flag = true;
						}
					}
					else
					{
						if (tmp == view[i][j])	//两数合并
						{
							flag = true;
							score += tmp * 2;
							nView[i][k--] = tmp * 2;
							if (2048 == tmp * 2)
							{
								ret = 2;
							}
							tmp = 0;
						}
						else
						{
							nView[i][k--] = tmp;
							tmp = view[i][j];
							if (k != j)
							{
								flag = true;
							}
						}
					}
				}
			}
			if (tmp != 0)
			{
				nView[i][k--] = tmp;
			}
			rest += k + 1;
		}
	}
	else if (direction == UP)
	{
		for (int i = 0; i != 4; ++i)
		{
			int tmp = 0, k = 0;
			for (int j = 0; j != 4; ++j)
			{
				if (view[j][i] != 0)
				{
					if (0 == tmp)
					{
						tmp = view[j][i];
						if (j != 0)
						{
							flag = true;
						}
					}
					else
					{
						if (tmp == view[j][i])	//两数合并
						{
							flag = true;
							score += tmp * 2;
							nView[k++][i] = tmp * 2;
							if (2048 == tmp * 2)
							{
								ret = 2;
							}
							tmp = 0;
						}
						else
						{
							nView[k++][i] = tmp;
							tmp = view[j][i];
							if (k != j)
							{
								flag = true;
							}
						}
					}
				}
			}
			if (tmp != 0)
			{
				nView[k++][i] = tmp;
			}
			rest += 4 - k;
		}
	}
	else
	{
		for (int i = 0; i != 4; ++i)
		{
			int tmp = 0, k = 3;
			for (int j = 3; j != -1; --j)
			{
				if (view[j][i] != 0)
				{
					if (0 == tmp)
					{
						tmp = view[j][i];
						if (j != 3)
						{
							flag = true;
						}
					}
					else
					{
						if (tmp == view[j][i])	//两数合并
						{
							flag = true;
							score += tmp * 2;
							nView[k--][i] = tmp * 2;
							if (2048 == tmp * 2)
							{
								ret = 2;
							}
							tmp = 0;
						}
						else
						{
							nView[k--][i] = tmp;
							tmp = view[j][i];
							if (k != j)
							{
								flag = true;
							}
						}
					}
				}
			}
			if (tmp != 0)
			{
				nView[k--][i] = tmp;
			}
			rest += k + 1;
		}
	}
	if (0 == ret)
	{
		if (0 == rest)
		{
			ret = 1;
			return ret;
		}
		if (flag)
		{
			//生成新数字
			srand((unsigned)time(NULL));
			rest = rand() % rest + 1;
			for (int i = 0; i != 4; ++i)
			{
				for (int j = 0; j != 4; ++j)
				{
					if (0 == nView[i][j])
					{
						--rest;
						if (0 == rest)
						{
							nView[i][j] = 2;
							break;
						}
					}
				}
			}
		}
	}
	memcpy(view, nView, sizeof(int) * 16);
	return ret;
}

void init(View& view)
{
	//初始化GUI
	//画布
	initgraph(600, 400);
	setbkcolor(RGB(187, 173, 160));
	//数字框样式
	setfillcolor(RGB(205, 193, 180));
	//数字样式
	setbkmode(TRANSPARENT);
	settextcolor(RGB(119, 110, 101));
	if (nToW.empty())	//如果是纯数字版，则设置为以下字体格式
	{
		settextstyle(40, 0, _T("Consolas"));
	}
	else	//如果是自定义版，则设置为以下字体格式
	{
		settextstyle(35, 0, _T("宋体"));
	}
	//初始化数据
	srand((unsigned)time(NULL));
	int n1 = rand() % 15;
	int n2 = rand() % 14;
	view[n1 / 4][n1 % 4] = 2;
	if (n2 >= n1)
	{
		++n2;
	}
	view[n2 / 4][n2 % 4] = 2;
}

void doGame()
{
	setMode();
	View view = { 0 };
	init(view);
	int score = 0;
	display(view, score);
	int flag = 0;
	while (!flag)
	{
		if (_kbhit())
		{
			char ch = _getch();
			switch (ch)
			{
			case 72:
				flag = execute(view, score, UP);
				display(view, score);
				break;
			case 80:
				flag = execute(view, score, DOWN);
				display(view, score);
				break;
			case 75:
				flag = execute(view, score, LEFT);
				display(view, score);
				break;
			case 77:
				flag = execute(view, score, RIGHT);
				display(view, score);
				break;
			default:
				break;
			}
		}
	}
	settextstyle(40, 0, _T("Consolas"));
	setfillcolor(RGB(237, 224, 200));
	solidroundrect(100, 100, 500, 300, 10, 10);
	if (1 == flag)
	{
		outtextxy(210, 120, "游戏结束！");
	}
	else
	{
		outtextxy(210, 120, "2 0 4 8 ！");
	}
	std::string str;
	str = "最终分数：" + std::to_string(score);
	outtextxy(130, 170, str.c_str());
	int max = 0;
	for (int i = 0; i != 4; ++i)
	{
		for (int j = 0; j != 4; ++j)
		{
			if (max < view[i][j])
			{
				max = view[i][j];
			}
		}
	}
	if (nToW.empty())
	{
		str = "最高等级：" + std::to_string(max);
	}
	else
	{
		str = "最高等级：" + nToW[max];
	}
	outtextxy(130, 220, str.c_str());
	settextstyle(25, 0, _T("Consolas"));
	outtextxy(130, 270, "按任意键退出游戏");
	_getch();
	closegraph();
}

void display(const View& view, int score)
{
	//重新绘制一遍
	cleardevice();
	solidroundrect(10, 10, 95, 95, 3, 3);
	solidroundrect(105, 10, 195, 95, 3, 3);
	solidroundrect(205, 10, 295, 95, 3, 3);
	solidroundrect(305, 10, 390, 95, 3, 3);
	solidroundrect(10, 105, 95, 195, 3, 3);
	solidroundrect(105, 105, 195, 195, 3, 3);
	solidroundrect(205, 105, 295, 195, 3, 3);
	solidroundrect(305, 105, 390, 195, 3, 3);
	solidroundrect(10, 205, 95, 295, 3, 3);
	solidroundrect(105, 205, 195, 295, 3, 3);
	solidroundrect(205, 205, 295, 295, 3, 3);
	solidroundrect(305, 205, 390, 295, 3, 3);
	solidroundrect(10, 305, 95, 390, 3, 3);
	solidroundrect(105, 305, 195, 390, 3, 3);
	solidroundrect(205, 305, 295, 390, 3, 3);
	solidroundrect(305, 305, 390, 390, 3, 3);
	//分数栏
	outtextxy(420, 150, "当前分数：");
	for (int i = 0, y = 35; i != 4; ++i)
	{
		for (int j = 0, x = 40; j != 4; ++j)
		{
			int tmp = view[i][j];
			if (tmp != 0)
			{
				if (nToW.empty())
				{
					//以下为输出数字时的效果
					int aclX = x;
					if (tmp > 1000)
					{
						aclX -= 30;
					}
					else if (tmp > 100)
					{
						aclX -= 20;
					}
					else if (tmp > 10)
					{
						aclX -= 10;
					}
					outtextxy(aclX, y, std::to_string(tmp).c_str());
				}
				else
				{
					//输出文字，文字长度不固定，所以没有很好地控制坐标
					int aclX = x - 25;
					outtextxy(aclX, y, nToW[tmp].c_str());
				}
			}
			x += 100;
		}
		y += 100;
	}
	outtextxy(480, 200, std::to_string(score).c_str());
}

void setMode()
{
	int option = 0;
	while (0 == option)
	{
		std::cout << "请选择游戏版本：" << std::endl;
		std::cout << "1.经典数字版\t\t2.诡秘之主版" << std::endl;
		std::cin >> option;
		if (1 == option)
		{
			nToW.clear();
			break;
		}
		if (2 == option)
		{
			break;
		}
		option = 0;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "输入有误，请重新选择！\n" << std::endl;
	}
}
