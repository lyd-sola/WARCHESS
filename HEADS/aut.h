/**********************************************************
Copyright(c)  2020 刘云笛、陈旭桐 	WARCHESS战棋
file_name:aut.h
Author:刘云笛、陈旭桐
Version:1.0
Description:战斗界面

Function List：
	1.void aut(MAP map, Battleinfo* batinfo);
		自动对战函数
	2.void aut_move(MAP map, OFF_POS opos, int visit[7][7]);
		自动移动实现
	3.int aut_attack(MAP map, OFF_POS opos, int visit[7][7], Arminfo info);
		自动攻击实现
	4.void ATTACK(OFF_POS to, Arminfo info, int Stay_pos, MAP map);
		攻击数值处理相关
	5.void aut_base(MAP map, unsigned* source);
		自动模式大本营相关功能
	6.void aut_buildarm(MAP map, unsigned* source);
		自动造兵
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