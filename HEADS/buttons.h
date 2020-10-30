/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:buttons.h
Author:刘云笛、陈旭桐
Version:1.0
Description:按钮函数
				
Function List：
	1、void Button(int y1, char* s, int color, int color2);
		绘制尖按钮
	2、int Sharp_button(int y0, char* s, char* s_change, int color, int color2);
		尖按钮功能函数
	3、void attack_button(char* s, int color);
		攻击按钮绘制
	4、void stay_button(char* s, int color);
		驻扎按钮绘制
	5、void move_button(char *s, int color);
		移动按钮绘制
	6、void del_button(int color);
		删除按钮绘制
	7、void nextr_button(int color);
		下一回合按钮绘制
	8、int atk_btn_fun(char* s, int color, int color_c);
		攻击按钮功能函数
	9、int stay_btn_fun(char* s, int color, int color_c);
		驻扎按钮功能函数
	10、int nxt_btn_fun(int color, int color_c);
		下一回合按钮功能函数
	11、int move_btn_fun(int color, int color_c, char *s);
		移动按钮功能函数
	12、int del_btn_fun(int color, int color_c);
		删除按钮功能函数
	13、void rect_circle(int x1, int y1, int x2, int y2, int color);
		绘制圆角方框
	14、void rect_button(int x1, int y1, int x2, int y2, char* s, int color); 
		方形按钮绘制
	15、void rect_btn_frame(int x1, int y1, int x2, int y2, int color);
		方形按钮加框
	16、int rec_btn_fun(int x1, int y1, int x2, int y2, int color);
		方形按钮功能函数
	17、void battle_exit(int x, int y);
		绘制退出战斗按钮
	18、void save_btn(int color);
		绘制保存按钮
	19、void exit_btn(int color);
		绘制退出战斗按钮
	20、void option_btn(int color);
		选项菜单按钮绘制
	21、void draw_opts(void);
		选项菜单绘制
	22、int opts_fun(void);
		选项菜单功能函数
**********************************************************/
#ifndef	_BUTTONS_H_
#define	_BUTTONS_H_

#include "struct.h"

void Button(int y1, char* s, int color, int color2);

int Sharp_button(int y0, char* s, char* s_change, int color, int color2);

void attack_button(char* s, int color);//攻击按钮

void stay_button(char* s, int color);//驻扎按钮

void move_button(char *s, int color);//移动按钮

void del_button(int color);//删除按钮

void nextr_button(int color);//下一回合按钮

int atk_btn_fun(char* s, int color, int color_c);

int stay_btn_fun(char* s, int color, int color_c);

int nxt_btn_fun(int color, int color_c);

int move_btn_fun(int color, int color_c, char *s);
int del_btn_fun(int color, int color_c);

void rect_circle(int x1, int y1, int x2, int y2, int color);

void rect_button(int x1, int y1, int x2, int y2, char* s, int color); //方形按钮

void rect_btn_frame(int x1, int y1, int x2, int y2, int color);

int rec_btn_fun(int x1, int y1, int x2, int y2, int color);

void battle_exit(int x, int y);

void save_btn(int color);

void exit_btn(int color);

void option_btn(int color);

void draw_opts(void);

int opts_fun(void);

#endif