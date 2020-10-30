/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:
Description:战斗界面

Function List：
	1.int homepage(void);
		主页核心函数
	2.void draw_h_page(void);
		主页界面绘制
	3.void homepg_button(int x1, int y1, int x2, int y2, char* s, int color);
		主页面按钮绘制
	4.int homepg_btn_fun(int x1, int y1, int x2, int y2, char* s);
		按钮功能函数（这里内容少就不放进buttons.c了）
	5.int guest_btn_fun(void);
		游客登录按钮功能函数
	6.int about_page(void);
		关于页
**********************************************************/
#ifndef __HOMEPAGE
#define __HOMEPAGE

int homepage(void);			//主页核心函数

void draw_h_page(void);		//主页界面绘制

void homepg_button(int x1, int y1, int x2, int y2, char* s, int color);	//主页面按钮绘制

int homepg_btn_fun(int x1, int y1, int x2, int y2, char* s);	//按钮功能函数（这里内容少就不放进buttons.c了）

int guest_btn_fun(void);//游客登录按钮功能函数

int about_page(void);//关于页
#endif