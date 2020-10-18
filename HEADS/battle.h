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

int battle(char* user, short save_num, short mode);

void battle_draw(void);

void Battle_init(FILE* fp, Battleinfo* info, MAP map);

void save_battle(FILE* fp, Battleinfo batinfo, MAP map);

void draw_cell(DBL_POS pos, MAP map);

void initdraw(MAP map);

void icon(POS world_pos, int side, int kind);

Arminfo search_info(int kind, DBL_POS dpos);
Arminfo disp_arm_info(CELL cell, DBL_POS dpos);

#endif