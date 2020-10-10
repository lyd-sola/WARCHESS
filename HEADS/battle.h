/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:
Description:战斗界面
				

Function List：
	1.int battle(char* user, short save_num);
		战斗界面主函数
	2.void battle_draw(void);
		战斗界面绘制函数
	3.void Battle_init(FILE* fp, Battleinfo* info, CELL map[][13]);
		战斗信息初始化（文件读取）
	4.void save_battle(FILE *fp, Battleinfo *batinfo, CELL map[][13]);
		战斗信息存档
**********************************************************/
#ifndef	_BATTLE_H_
#define	_BATTLE_H_

#include "struct.h"

int battle(char* user, short save_num, short mode);

void battle_draw(void);

void Battle_init(FILE* fp, Battleinfo* info, MAP map);

void save_battle(FILE* fp, Battleinfo* batinfo, MAP map);

void save_btn(int color);
void exit_btn(int color);
void option_btn(int color);

#endif