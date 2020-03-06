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
//数字文字对应表,可自定义修改
static std::unordered_map<int, std::string> nToW{
	{2,"占卜"},
	{4,"小丑"},
	{8,"魔术"},
	{16,"无面"},
	{32,"秘偶"},
	{64,"诡法"},
	{128,"学者"},
	{256,"奇迹"},
	{512,"侍者"},
	{1024,"愚者"},
	{2048,"诡秘"},
};
//执行操作（上下左右移动合并，生成新数字）
int execute(View& view, int& score, int direction);
//初始化
void init(View& view);
//程序主体
void doGame();
//显示在屏幕上
void display(const View& view, int score);
//选择模式，数字or诡秘版
void setMode();