/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:battle.h
Author:刘云笛、陈旭桐
Version:2.0
Description:战斗界面			

Function List：
	1.int battle(char* user, short save_num, short mode);
	1.int battle(char* user, int save_num);
		战斗界面主函数
	2.void battle_draw(void);
		战斗界面绘制函数	
	3.void initdraw(MAP map);
		地图初始化绘制
	4.void disp_geo_info(CELL cell);
		显示地形信息
	5.void icon(POS world_pos, int side, int kind);
		根据兵种画出兵种标志
	6.Arminfo search_info(int kind);
		检索兵种信息
	7.Arminfo disp_arm_info(CELL cell);
		显示兵种信息
	8.void disp_bat_info(Battleinfo batinfo);
		显示战役信息
	9.void act_buttons(COLO* co, int kind, int flag, int is_same_side, int is_stay, int is_base, int air_ok);
		绘制行为按钮
	10.void act_btn(MAP map, COLO* co, int* clccell, DBL_POS pos, Arminfo* arminfo, Battleinfo* batinfo);
		按钮整合函数，灰色状态不能点击
	11.void first_click(MAP map, DBL_POS* pos, int* clccell, int* msgflag, Arminfo* arminfo, Battleinfo* batinfo, COLO *co);
		第一次点击地图上一点，会改变clccell状态，记录pos，调用大本营相关函数
	12.int opt_btn(FILE* fp, int save_num, MAP map, Battleinfo* batinfo);
		右上角选项菜单区
**********************************************************/
#ifndef	_BATTLE_H_
#define	_BATTLE_H_

#include "struct.h"

#define msg_sec 1000
#define lev2_cost 12
#define lev3_cost 80
#define air_atk_cost 40

int battle(char* user, int save_num, int mode);

void battle_draw(void);

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
void act_buttons(COLO* co, int kind, int flag, int is_same_side, int is_stay, int is_base, int air_ok);
void act_btn(MAP map, COLO* co, int* clccell, DBL_POS pos, Arminfo* arminfo, Battleinfo* batinfo);
void first_click(MAP map, DBL_POS* pos, int* clccell, int* msgflag, Arminfo* arminfo, Battleinfo* batinfo, COLO *co);
int opt_btn(FILE* fp, int save_num, MAP map, Battleinfo* batinfo);
#endif