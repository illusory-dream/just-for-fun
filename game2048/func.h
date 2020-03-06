#pragma once
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <unordered_map>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
using View = int[4][4];
//�������ֶ�Ӧ��,���Զ����޸�
static std::unordered_map<int, std::string> nToW{
	{2,"ռ��"},
	{4,"С��"},
	{8,"ħ��"},
	{16,"����"},
	{32,"��ż"},
	{64,"�"},
	{128,"ѧ��"},
	{256,"�漣"},
	{512,"����"},
	{1024,"����"},
	{2048,"����"},
};
//ִ�в��������������ƶ��ϲ������������֣�
int execute(View& view, int& score, int direction);
//��ʼ��
void init(View& view);
//��������
void doGame();
//��ʾ����Ļ��
void display(const View& view, int score);
//ѡ��ģʽ������or���ذ�
void setMode();