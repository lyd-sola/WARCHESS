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
	3.Battleinfo Battle_init(char* user, CELL map[][13], short save_num);
		战斗信息初始化（文件读取）
**********************************************************/
#ifndef	_BATTLE_H_
#define	_BATTLE_H_

#include "struct.h"

int battle(char* user, short save_num);
void battle_draw(void);
Battleinfo Battle_init(char* user, CELL map[][13], short save_num);

#endif