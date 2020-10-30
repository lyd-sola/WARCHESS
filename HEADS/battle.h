/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:battle.h
Author:���Ƶѡ�����ͩ
Version:2.0
Description:ս������			

Function List��
	1.int battle(char* user, short save_num, short mode);
	1.int battle(char* user, int save_num);
		ս������������
	2.void battle_draw(void);
		ս��������ƺ���	
	3.void initdraw(MAP map);
		��ͼ��ʼ������
	4.void disp_geo_info(CELL cell);
		��ʾ������Ϣ
	5.void icon(POS world_pos, int side, int kind);
		���ݱ��ֻ������ֱ�־
	6.Arminfo search_info(int kind);
		����������Ϣ
	7.Arminfo disp_arm_info(CELL cell);
		��ʾ������Ϣ
	8.void disp_bat_info(Battleinfo batinfo);
		��ʾս����Ϣ
	9.void act_buttons(COLO* co, int kind, int flag, int is_same_side, int is_stay, int is_base, int air_ok);
		������Ϊ��ť
	10.void act_btn(MAP map, COLO* co, int* clccell, DBL_POS pos, Arminfo* arminfo, Battleinfo* batinfo);
		��ť���Ϻ�������ɫ״̬���ܵ��
	11.void first_click(MAP map, DBL_POS* pos, int* clccell, int* msgflag, Arminfo* arminfo, Battleinfo* batinfo, COLO *co);
		��һ�ε����ͼ��һ�㣬��ı�clccell״̬����¼pos�����ô�Ӫ��غ���
	12.int opt_btn(FILE* fp, int save_num, MAP map, Battleinfo* batinfo);
		���Ͻ�ѡ��˵���
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