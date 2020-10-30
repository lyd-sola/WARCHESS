/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:mainmenu.h
Author:刘云笛、陈旭桐
Version:2.0
Description:主菜单

Function List：
	1.int mainmenu(char* user, int* save_num, int* mode);
		主菜单核心函数
	2.void mmenu_draw(char *user);
		绘制主菜单界面
**********************************************************/
#ifndef _mmenu_h_
#define _mmenu_h_

int mainmenu(char* user, int* save_num, int* mode);			//主菜单核心函数

void mmenu_draw(char *user);		//绘制主菜单界面

#endif