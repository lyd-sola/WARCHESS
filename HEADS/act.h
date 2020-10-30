/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:battle.h
Author:���Ƶѡ�����ͩ
Version:1.0
Description:��ս��Ϊ����


Function List��
	1.void move(DBL_POS From, MAP map, int able);
		�ƶ�����
	2.int move_(DBL_POS From, DBL_POS dbto, MAP map, int visit[7][7]);
		�Ƿ�����ƶ��ж�
	3.void stay(DBL_POS dpos, MAP map);
		פ������
	4.void attack(DBL_POS dpos, MAP map);
		��������
	5.int attack_(Arminfo info, MAP map, DBL_POS dpos, DBL_POS dbto);
		������ֵ��غ���
	6.void delarm(DBL_POS dpos, MAP map);
		ɾ�����ֺ���
	7.void builder_build(DBL_POS dpos, MAP map, Battleinfo* batinfo);
		����������ʩ����
	8.void nxt_round(MAP map, Battleinfo* info, int* pside);
		��һ�غϺ���
	9.void next_r_banner(int side);
		������һ�غϽ���
	10.void base_func(MAP map, unsigned* source, int is_same_side, DBL_POS pos);
		��Ӫ��Ϊ����
	11.void levelup(DBL_POS dpos, MAP map, unsigned* source);
		��Ӫ����
	12.void buildarm(MAP map, unsigned* source, int side);
		�������
	13.void armbuild_draw(POS pos, int side);
		�������½������ť
	14.void air_attack(DBL_POS pos, MAP map, unsigned *source);
		��Ӫ��������
	15.void air_boom(MAP map, OFF_POS oto, OFF_POS from);
		��Ӫ��Ϯ����
**********************************************************/

#ifndef  _ACT_H_
#define  _ACT_H_

void move(DBL_POS From, MAP map, int able);
int move_(DBL_POS From, DBL_POS dbto, MAP map, int visit[7][7]);
void stay(DBL_POS dpos, MAP map);
void attack(DBL_POS dpos, MAP map);
int attack_(Arminfo info, MAP map, DBL_POS dpos, DBL_POS dbto);
void delarm(DBL_POS dpos, MAP map);
void builder_build(DBL_POS dpos, MAP map, Battleinfo* batinfo);

void nxt_round(MAP map, Battleinfo* info, int* pside);
void next_r_banner(int side);

void base_func(MAP map, unsigned* source, int is_same_side, DBL_POS pos);
void levelup(DBL_POS dpos, MAP map, unsigned* source);
void buildarm(MAP map, unsigned* source, int side);
void armbuild_draw(POS pos, int side);
void air_attack(DBL_POS pos, MAP map, unsigned *source);
void air_boom(MAP map, OFF_POS oto, OFF_POS from);
#endif