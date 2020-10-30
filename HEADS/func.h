/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:2.0
Description:各种难以分类的功能性函数					修改未完成
				

Function List：
	1.void draw_show_error(void);
		绘制报错界面
	2.void show_error(char* msg, int mode);
		显示错误信息函数，msg为错误信息，mode 1为巨大错误关闭程序，0为小错误、仅返回
	3.void show_msg(char* msg, char* msg2);
		显示对战界面下方信息
	4.int msgbar(char* btn1, char* btn2, char* s1, char* s2);
		弹窗询问
**********************************************************/
#ifndef	_FUNCITONS_H_
#define	_FUNCITONS_H_

void draw_show_error(void);

void show_error(char* msg, int mode);

void show_msg(char* msg, char* msg2);

int msgbar(char* btn1, char* btn2, char* s1, char* s2);

#endif