/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:2.0
Description:各种难以分类的功能性函数					修改未完成
				

Function List：
	1.void show_error(char* msg, int mode);
		显示错误信息函数，msg为错误信息，mode 1为巨大错误关闭程序，0为小错误、仅返回
	2.int Sharp_button(int y0, char* s, char* s_change, int color, int color2);
		mainmenu界面按钮功能函数，可以实现所有按钮功能，被点击时返回1
**********************************************************/
#ifndef	_FUNCITONS_H_
#define	_FUNCITONS_H_

extern FILE* FBMP;//动画用
void show_error(char* msg, int mode);
void show_msg(char* msg, char* msg2);
short msgbar(char* btn1, char* btn2, char* s1, char* s2);

#endif