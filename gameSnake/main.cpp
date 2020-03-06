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
	//�ⲿ��ͼ
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
	settextstyle(30, 15, _T("����"));
	//snake��Ϣ��body��Ϣ��������Ϣ��ͷβ����
	vector<vector<int>> snake(50, vector<int>(50, 0));
	snake[0][0] = 1; snake[0][1] = 1; snake[0][2] = 1;
	vector<vector<int>> next(50, vector<int>(50, 0));
	next[0][0] = RIGHT; next[0][1] = RIGHT;
	int headi = 0, headj = 2;
	int taili = 0, tailj = 0;
	//������Ϣ
	char moveDirection = 77;	//current direction
	int foodi = 0, foodj = 0;	//food index
	int speed = 9;
	bool highSpeed = false;
	int len = 3;
	while (1)
	{
		//��ͼ
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
		outtextxy(530, 20, _T("���ȣ�")); outtextxy(650, 20, s);
		if (highSpeed)
		{
			_stprintf_s(s, _T("%d"), speed * 2);
		}
		else
		{
			_stprintf_s(s, _T("%d"), speed);
		}
		outtextxy(530, 80, _T("�ٶȣ�")); outtextxy(650, 80, s);
		_stprintf_s(s, _T("%d"), len - 3);
		outtextxy(530, 140, _T("������")); outtextxy(650, 140, s);
		outtextxy(530, 200, _T("~��z�Կ��ؼ���~"));
		//speed
		if (highSpeed)
		{
			Sleep(500 / speed);
		}
		else
		{
			Sleep(1000 / speed);
		}
		//������food
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
		//�ȴ��������� or ���򲻱�
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
			if (input + moveDirection != 152)	//Ŀ�귽��͵�ǰ�������෴
			{
				moveDirection = input;
			}
		}
		switch (moveDirection)
		{
		case 72:
			//���·����ϵ��ͷ����
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
		//game over�ж�
		if (headj > 49 || headj < 0 || headi > 49 || headi < 0 || 1 == snake[headi][headj])
		{
			break;
		}
		//�Ե�food��ɾ��β��ֱ�Ӹ���len��speed
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
			//ɾ��β�����·����ϵ��β����
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
		//�����ͷ(++len)
		snake[headi][headj] = 1;
		//����
		setfillcolor(BLACK); setlinecolor(BLACK);
		fillrectangle(10, 10, 510, 510);
		fillrectangle(530, 20, 800, 520);
	}
	if (2500 == len)
	{
		outtextxy(530, 260, _T("���Ȼͨ����!"));
	}
	else
	{
		outtextxy(530, 260, _T("Game over!"));
	}
	outtextxy(530, 320, _T("��������˳���"));
	outtextxy(530, 380, _T("r�����¿�ʼ~"));
	fflush(stdin);
	char ch = _getch();
	if ('r' == ch || 'R' == ch)
	{
		goto BEGIN;
	}

	closegraph();
	return 0;
}