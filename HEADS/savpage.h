/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:
Description:战斗界面

Function List：
	1.int savpage(char *user, int* save_num, int* mode);
		存档界面主函数
	2.void savpage_draw(FILE* fp);
		存档界面绘制函数
	3.void draw_saves(int x, int y, int color, FILE* fp, int save_num);
		显示存档信息
	4.void savpage_btns(int i);
		存档界面按钮绘制
**********************************************************/
#ifndef  _SAVPAGE_H_
#define  _SAVPAGE_H_

int savpage(char *user, int* save_num, int* mode);
void savpage_draw(FILE* fp);
void draw_saves(int x, int y, int color, FILE* fp, int save_num);
void savpage_btns(int i);
int save1(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save2(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save3(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save4(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save5(FILE* fp, int* flag, int tot, int* mode, int* save_num);
int save6(FILE* fp, int* flag, int tot, int* mode, int* save_num);
#endif