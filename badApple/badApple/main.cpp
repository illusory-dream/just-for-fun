#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <ctime>
#pragma comment(lib,"WinMM.lib")
using namespace std;

/*
*版权声明：本文为CSDN博主「Icy_Ybk」的原创文章，遵循CC 4.0 by - sa版权协议，转载请附上原文出处链接及本声明。
*原文链接：https://blog.csdn.net/icy_ybk/article/details/79285245
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
	unsigned i = 0;	//播放第i帧
	ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);	//指定全屏显示
	long long begTime = GetTickCount64(), nowTime;	//播放开始时间，当前时间
	int fps = 0, count = 0;	//帧频，（每秒内）计数
	long long thisSecTime = begTime;	//记录每一秒的起始点时间
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
		if (i != iLast)	//如果i与上一次相等则为重复帧，不播放
		{
			iLast = i;
			clearScreen();
			cout << content << endl;
			++count;
			cout << "当前fps：" << fps - 1 << endl;	//统计的是>1000ms时的播放次数，所以-1（无关紧要）
			cout << "当前读取文件：ascii\\" << i << ".txt" << endl;
		}

		//计算当前时间节点应播放的.txt文件
		nowTime = GetTickCount64();
		i = unsigned((nowTime - begTime) / 1000 * 30 + (nowTime - begTime) % 1000 / 33);

		//统计1s内的刷新次数
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
	unsigned i = 0;	//播放第i帧
	ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);	//指定全屏显示
	long long begTime = GetTickCount64(), nowTime;	//播放开始时间，当前时间
	int fps = 0, count = 0;	//帧频，（每秒内）计数
	long long thisSecTime = begTime;	//记录每一秒的起始点时间
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
		cout << "当前fps：" << fps - 1 << endl;	//统计的是>1000ms时的播放次数，所以-1（无关紧要）
		cout << "当前读取文件：ascii\\" << i << ".txt" << endl;
		Sleep(40);	//设定Sleep以减少闪烁

		//计算当前时间节点应播放的.txt文件
		nowTime = GetTickCount64();
		i = unsigned((nowTime - begTime) / 1000 * 30 + (nowTime - begTime) % 1000 / 33);

		//统计1s内的刷新次数
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
	cout << "请选择版本：1.20fps不卡\t\t2.30fps流畅（但有可能闪屏）" << endl;
	int opt;
	cin >> opt;
	//播放bgm
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