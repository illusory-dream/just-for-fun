#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <ctime>
#pragma comment(lib,"WinMM.lib")
using namespace std;

/*
*��Ȩ����������ΪCSDN������Icy_Ybk����ԭ�����£���ѭCC 4.0 by - sa��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
*ԭ�����ӣ�https://blog.csdn.net/icy_ybk/article/details/79285245
*/
void clearScreen()
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO bufInfo;
	SMALL_RECT scroll;
	COORD newCursorPointer;
	CHAR_INFO ciFill;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStdOut, &bufInfo))
		return;

	scroll.Left = 0;
	scroll.Top = 0;
	scroll.Right = bufInfo.dwSize.X;
	scroll.Bottom = bufInfo.dwSize.Y;
	newCursorPointer.X = 0;
	newCursorPointer.Y = -bufInfo.dwSize.Y;
	ciFill.Char.UnicodeChar = L' ';
	ciFill.Attributes = bufInfo.wAttributes;
	ScrollConsoleScreenBufferW(hStdOut, &scroll, NULL, newCursorPointer, &ciFill);
	newCursorPointer.Y = 0;
	SetConsoleCursorPosition(hStdOut, newCursorPointer);
}

void play30fps()
{
	unsigned i = 0;	//���ŵ�i֡
	ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);	//ָ��ȫ����ʾ
	long long begTime = GetTickCount64(), nowTime;	//���ſ�ʼʱ�䣬��ǰʱ��
	int fps = 0, count = 0;	//֡Ƶ����ÿ���ڣ�����
	long long thisSecTime = begTime;	//��¼ÿһ�����ʼ��ʱ��
	int iLast = -1;
	while (i < 6572)
	{
		ifstream is("ascii\\" + to_string(i) + ".txt");
		string line, content;
		while (getline(is, line))
		{
			content += line;
			content += "\n";
		}
		if (i != iLast)	//���i����һ�������Ϊ�ظ�֡��������
		{
			iLast = i;
			clearScreen();
			cout << content << endl;
			++count;
			cout << "��ǰfps��" << fps - 1 << endl;	//ͳ�Ƶ���>1000msʱ�Ĳ��Ŵ���������-1���޹ؽ�Ҫ��
			cout << "��ǰ��ȡ�ļ���ascii\\" << i << ".txt" << endl;
		}

		//���㵱ǰʱ��ڵ�Ӧ���ŵ�.txt�ļ�
		nowTime = GetTickCount64();
		i = unsigned((nowTime - begTime) / 1000 * 30 + (nowTime - begTime) % 1000 / 33);

		//ͳ��1s�ڵ�ˢ�´���
		if (nowTime - thisSecTime - 30 > 1000)
		{
			thisSecTime = nowTime;
			fps = count;
			count = 0;
		}
	}
}
void play20fps()
{
	unsigned i = 0;	//���ŵ�i֡
	ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);	//ָ��ȫ����ʾ
	long long begTime = GetTickCount64(), nowTime;	//���ſ�ʼʱ�䣬��ǰʱ��
	int fps = 0, count = 0;	//֡Ƶ����ÿ���ڣ�����
	long long thisSecTime = begTime;	//��¼ÿһ�����ʼ��ʱ��
	while (i < 6572)
	{
		ifstream is("ascii\\" + to_string(i) + ".txt");
		string line, content;
		while (getline(is, line))
		{
			content += line;
			content += "\n";
		}
		clearScreen();
		cout << content << endl;
		cout << "��ǰfps��" << fps - 1 << endl;	//ͳ�Ƶ���>1000msʱ�Ĳ��Ŵ���������-1���޹ؽ�Ҫ��
		cout << "��ǰ��ȡ�ļ���ascii\\" << i << ".txt" << endl;
		Sleep(40);	//�趨Sleep�Լ�����˸

		//���㵱ǰʱ��ڵ�Ӧ���ŵ�.txt�ļ�
		nowTime = GetTickCount64();
		i = unsigned((nowTime - begTime) / 1000 * 30 + (nowTime - begTime) % 1000 / 33);

		//ͳ��1s�ڵ�ˢ�´���
		if (nowTime - thisSecTime - 30 > 1000)
		{
			thisSecTime = nowTime;
			fps = count;
			count = 0;
		}
		++count;
	}
}

int main()
{
	cout << "��ѡ��汾��1.20fps����\t\t2.30fps���������п���������" << endl;
	int opt;
	cin >> opt;
	//����bgm
	PlaySound("ascii\\audio.wav", NULL, SND_FILENAME | SND_ASYNC);
	Sleep(200);
	if (1 == opt)
	{
		play20fps();
	}
	else if (2 == opt)
	{
		play30fps();
	}
	system("pause");
	return 0;
}