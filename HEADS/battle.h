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
	3.Battleinfo Battle_init(char* user, CELL map[][13], short save_num);
		ս����Ϣ��ʼ�����ļ���ȡ��
**********************************************************/
#ifndef	_BATTLE_H_
#define	_BATTLE_H_

#include "struct.h"

int battle(char* user, short save_num);
void battle_draw(void);
Battleinfo Battle_init(char* user, CELL map[][13], short save_num);

#endif