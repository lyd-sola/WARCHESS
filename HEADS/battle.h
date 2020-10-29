/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:battle.h
Author:���Ƶѡ�����ͩ
Version:
Description:ս������
				

Function List��
	1.int battle(char* user, short save_num);
		ս������������
	2.void battle_draw(void);
		ս��������ƺ���
	3.void Battle_init(FILE* fp, Battleinfo* info, CELL map[][13]);
		ս����Ϣ��ʼ�����ļ���ȡ��
	4.void save_battle(FILE *fp, Battleinfo *batinfo, CELL map[][13]);
		ս����Ϣ�浵
**********************************************************/
#ifndef	_BATTLE_H_
#define	_BATTLE_H_

#include "struct.h"

#define msg_sec 1000
#define lev2_cost 20
#define lev3_cost 100
#define air_atk_cost 40

int battle(char* user, short save_num, short mode);

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