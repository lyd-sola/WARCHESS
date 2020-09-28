/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:2.0
Description:键盘输入函数
				

Function List：
	1.void kbinput(int x1, int y1, int x2, int y2, char *s, int mode);
			键盘输入函数，前四个坐标为输入框坐标，s为接收内容数组，mode取1输出原文、取0输出‘*’
**********************************************************/
#ifndef _KB_INPUT_
#define _KB_INPUT_

void kbinput(int x1, int y1, int x2, int y2, char *s, int mode);
#endif

