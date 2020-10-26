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
#define msg_sec 1000

int battle(const char* user, short save_num, short mode);

void battle_draw(void);

void draw_cell(DBL_POS pos, MAP map);

void initdraw(MAP map);

void disp_geo_info(CELL cell);

void icon(POS world_pos, int side, int kind);
Arminfo search_info(int kind);
Arminfo disp_arm_info(CELL cell);
void disp_bat_info(Battleinfo batinfo);

typedef struct COLR {
	int atk, mov, stay, del;
}COLO;
#define OK_co 65370
#define CANT_co 44373
void act_buttons(COLO* co, int kind, int flag, int is_same_side);
void act_btn(MAP map, COLO* co, int* clccell, DBL_POS pos, Arminfo* arminfo);
void first_click(MAP map, DBL_POS* pos, int* clccell, int* msgflag, Arminfo* arminfo, Battleinfo* batinfo, COLO *co);
int opt_btn(FILE* fp, int save_num, MAP map, Battleinfo* batinfo);
#endif