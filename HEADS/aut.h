/**********************************************************
Copyright(c)  2020 ���Ƶѡ�����ͩ 	WARCHESSս��
file_name:aut.h
Author:���Ƶѡ�����ͩ
Version:1.0
Description:ս������

Function List��
	1.void aut(MAP map, Battleinfo* batinfo);
		�Զ���ս����
	2.void aut_move(MAP map, OFF_POS opos, int visit[7][7]);
		�Զ��ƶ�ʵ��
	3.int aut_attack(MAP map, OFF_POS opos, int visit[7][7], Arminfo info);
		�Զ�����ʵ��
	4.void ATTACK(OFF_POS to, Arminfo info, int Stay_pos, MAP map);
		������ֵ�������
	5.void aut_base(MAP map, unsigned* source);
		�Զ�ģʽ��Ӫ��ع���
	6.void aut_buildarm(MAP map, unsigned* source);
		�Զ����
**********************************************************/
#ifndef  _AUT_H_
#define  _AUT_H_

#include "struct.h"
void aut(MAP map, Battleinfo* batinfo);
void aut_move(MAP map, OFF_POS opos, int visit[7][7]);
int aut_attack(MAP map, OFF_POS opos, int visit[7][7], Arminfo info);
void ATTACK(OFF_POS to, Arminfo info, int Stay_pos, MAP map);
void aut_base(MAP map, unsigned* source);
void aut_buildarm(MAP map, unsigned* source);
#endif